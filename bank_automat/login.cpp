#include "enviroment.h"
#include "login.h"
#include "paaikkuna.h"
#include "qmessagebox.h"
#include "ui_login.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    // Aikakatkaisuun tarvittavat

    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &Login::onTimeout);

    timeoutTimer->start(10000); // 10 sekuntia

    setMouseTracking(true); // Hiiren seuraaminen

    installEventFilter(this); // Tarkkailee myös qline editin näppäimiä

    ui->LeUserId->installEventFilter(this);
    ui->LeUserPin->installEventFilter(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_2_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("card_id",ui->LeUserId->text());
    jsonObj.insert("pin",ui->LeUserPin->text());

    // Korjattu kirjautumisreitti takaisin oikeaksi
    QString site_url=Enviroment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    postManager = new QNetworkAccessManager(this);
    connect(postManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(LoginSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Login::LoginSlot(QNetworkReply *reply) {
    QByteArray response_data = reply->readAll();
    qDebug() << "Login response data:" << response_data;

    if (response_data.length() < 2) {
        ui->labelInfo->setText("Palvelin ei vastaa!");
        return;
    }


    QString responseStr = QString::fromUtf8(response_data).trimmed();


    if (responseStr == "False1") {
        ui->labelInfo->setText("Kortti lukittu.");
        return;
    } else if (responseStr == "False2") {
        ui->labelInfo->setText("Kortti lukitaan.");
        return;
    } else if (responseStr == "False3") {
        ui->labelInfo->setText("Väärä arvaus.");
        return;
    } else if (responseStr == "False4") {
        ui->labelInfo->setText("Käyttäjää ei löydy.");
        return;
    } else if (responseStr == "False5") {
        ui->labelInfo->setText("Tunnus tai PIN puuttuu.");
        return;
    } else if (responseStr == "-11") {
        ui->labelInfo->setText("Palvelinvirhe -11.");
        return;

    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObject = jsonResponse.object();

    QString token = jsonObject["token"].toString();
    QString fname = jsonObject["fname"].toString();
    QString lname = jsonObject["lname"].toString();
    int cardType = jsonObject["card_type"].toInt();
    QJsonArray accounts = jsonObject["accounts"].toArray();

    myToken = "Bearer " + token.toUtf8();

    int selectedAccountId = -1;

    if (cardType == 3) {  // Combo-kortti
        ui->labelInfo->setText("Valitse Debit tai Credit");
        ui->label_credit->setText("Credit");
        ui->label_debit->setText("Debit");
        connect(ui->btnDebit, &QPushButton::clicked, this, [=]() {
            selectAccountType("debit", accounts, fname, lname);
        });

        connect(ui->btnCredit, &QPushButton::clicked, this, [=]() {
            selectAccountType("credit", accounts, fname, lname);
        });

        return;  // Odotetaan käyttäjän valintaa
    } else {
        // Jos kortti on debit tai credit, valitaan ensimmäinen tili
        selectedAccountId = accounts[0].toObject()["account_id"].toInt();
    }

    if (selectedAccountId == -1) {
        ui->labelInfo->setText("Tilin valinta epäonnistui!");
        return;
    }

    // Haetaan saldo kirjautumisen jälkeen
    fetchBalance(myToken, selectedAccountId, fname, lname);
    timeoutTimer->stop();   // Poistetaan aikakatkaisun timeri käytöstä

    reply->deleteLater();
    postManager->deleteLater();
}


void Login::selectAccountType(const QString &selectedAccountType, const QJsonArray &accounts, const QString &fname, const QString &lname)
{
    int selectedAccountId = -1;

    for (const QJsonValue &val : accounts) {
        QJsonObject account = val.toObject();
        if (account["account_type"].toString() == selectedAccountType) {
            selectedAccountId = account["account_id"].toInt();
            break;
        }
    }

    if (selectedAccountId == -1) {
        ui->labelInfo->setText("Tilin valinta epäonnistui!");
        return;
    }

    // Haetaan saldo valinnan jälkeen
    fetchBalance(myToken, selectedAccountId, fname, lname);
}

void Login::fetchBalance(const QByteArray &token, int accountId, const QString &fname, const QString &lname)
{
    QString balanceUrl = Enviroment::base_url() + "/api/balance?account_id=" + QString::number(accountId);
    QNetworkRequest request(balanceUrl);
    request.setRawHeader("Authorization", token);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        QByteArray balanceData = reply->readAll();
        qDebug() << "Balance response data:" << balanceData;

        if (reply->error() != QNetworkReply::NoError) {
            ui->labelInfo->setText("Saldon hakeminen epäonnistui!");
            reply->deleteLater();
            return;
        }

        QJsonDocument balanceResponse = QJsonDocument::fromJson(balanceData);
        QJsonObject balanceObject = balanceResponse.object();

        // Muutetaan merkkijonosta doubleksi
        double balance = balanceObject["balance"].toString().toDouble();
        qDebug() << "Saldo asetettu arvoon: " << balance;

        // Avaa pääikkuna ja välitä tiedot
        paaikkuna *mainWindow = new paaikkuna(this);
        mainWindow->setMyToken(token);
        mainWindow->setUserName(fname, lname);
        mainWindow->setSelectedAccountId(accountId);
        mainWindow->setBalance(balance);
        mainWindow->open();

        reply->deleteLater();
    });

    balanceManager->get(request);
}
void Login::on_btn0_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "0";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "0";
        ui->LeUserPin->setText(pinText);
    }

    timeoutTimer->start(10000); // Aloitetaan ajastin alusta
}

void Login::on_btn1_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "1";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "1";
        ui->LeUserPin->setText(pinText);
    }

    timeoutTimer->start(10000); // Aloitetaan ajastin alusta
}


void Login::on_btn2_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "2";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "2";
        ui->LeUserPin->setText(pinText);
    }

    timeoutTimer->start(10000); // Aloitetaan ajastin alusta
}



void Login::on_btn3_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "3";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "3";
        ui->LeUserPin->setText(pinText);
    }
}


void Login::on_btn4_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "4";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "4";
        ui->LeUserPin->setText(pinText);
    }
}


void Login::on_btn5_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "5";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "5";
        ui->LeUserPin->setText(pinText);
    }

}


void Login::on_btn6_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "6";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "6";
        ui->LeUserPin->setText(pinText);
    }
}


void Login::on_btn7_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "7";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "7";
        ui->LeUserPin->setText(pinText);

    }
}


void Login::on_btn8_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "8";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "8";
        ui->LeUserPin->setText(pinText);
    }
}


void Login::on_btn9_clicked()
{
    QString currentText = ui->LeUserId->text();
    if (currentText.length() < 1) {
        currentText += "9";
        ui->LeUserId->setText(currentText);

        ui->LeUserPin->setFocus();
    }
    else {
        QString pinText = ui->LeUserPin->text();
        pinText += "9";
        ui->LeUserPin->setText(pinText);
    }
}

void Login::on_btnClear_clicked()
{
    QString pinText = ui->LeUserPin->text();
    if (!pinText.isEmpty()) {
        pinText.chop(1);
        ui->LeUserPin->setText(pinText);
    }
    else {
        QString userIdText = ui->LeUserId->text();
        if (!userIdText.isEmpty()) {
            userIdText.chop(1);
            ui->LeUserId->setText(userIdText);
        }
    }
}

void Login::mouseMoveEvent(QMouseEvent *event) {
    Q_UNUSED(event);  // Estää käyttämättömän muuttujan varoituksen
    timeoutTimer->start(10000);  // Nollataan ajastin hiiren liikkeellä
}


bool Login::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        timeoutTimer->start(10000);  // Nollataan ajastin näppäinpainalluksella
    }
    return QDialog::eventFilter(obj, event); // Palautetaan tapahtuma normaalisti
}


void Login::onTimeout()
{
    ui->labelInfo->setText("Aikakatkaisu!");
    QTimer::singleShot(2000, this, &QWidget::close); // Suljetaan ikkuna 2 sekunnin päästä
}

