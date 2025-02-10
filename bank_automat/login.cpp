#include "enviroment.h"
#include "login.h"
#include "paaikkuna.h"
#include "ui_login.h"
#include <QMouseEvent>
#include <QKeyEvent>

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
/*
    connect(ui->btn0,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn1,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn2,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn3,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn4,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn5,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn6,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn7,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn8,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn9,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
*/
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

    QString site_url=Enviroment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    postManager = new QNetworkAccessManager(this);
    connect(postManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(LoginSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());

}

void Login::LoginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();


    qDebug() << "Login response data:" << response_data;


    if(response_data.length()<2){
        qDebug()<<"Palvelin ei vastaa";
        ui->labelInfo->setText("Palvelin ei vastaa!");
    }
    else{
        if(response_data=="-11"){
            ui->labelInfo->setText("Tietokanta virhe!");
        }
        else {
            if (response_data != "False" && response_data.length() > 20) {
                ui->labelInfo->setText("Kirjautuminen onnistui!");

                timeoutTimer->stop();

                // Puretaan JSON-vastaus
                QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
                QJsonObject jsonObject = jsonResponse.object();

                QString token = jsonObject["token"].toString();
                QString fname = jsonObject["fname"].toString();
                QString lname = jsonObject["lname"].toString();


                //int cardType = jsonObject["card_type"].toInt();



                QJsonArray accounts = jsonObject["accounts"].toArray();

                qDebug() << "Accounts from login:" << accounts;

                QByteArray myToken = "Bearer " + token.toUtf8();


/*
                if (cardType == 3) {  // Combo-kortti
                    // Avaa valintaikkuna käyttäjälle
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Valitse tili");
                    msgBox.setText("Valitse käytettävä tili:");
                    QPushButton *debitButton = msgBox.addButton(tr("Debit"), QMessageBox::AcceptRole);
                    QPushButton *creditButton = msgBox.addButton(tr("Credit"), QMessageBox::RejectRole);

                    msgBox.exec();

                    QString selectedAccountType;
                    if (msgBox.clickedButton() == debitButton) {
                        selectedAccountType = "debit";
                    } else if (msgBox.clickedButton() == creditButton) {
                        selectedAccountType = "credit";
                    }

                    // Etsi valitun tilin ID ja välitä se eteenpäin
                    int selectedAccountId = -1;
                    for (const QJsonValue &val : accounts) {
                        QJsonObject account = val.toObject();
                        if (account["account_type"].toString() == selectedAccountType) {
                            selectedAccountId = account["account_id"].toInt();
                            break;
                        }
                    }
                    */


                // Luo pääikkuna ja välitä nimi ja token
                paaikkuna *objpaaikkuna = new paaikkuna(this);
                objpaaikkuna->setMyToken(myToken);
                objpaaikkuna->setUserName(fname, lname);  // Välitetään nimi pääikkunaan
                objpaaikkuna->setAccounts(accounts);
                objpaaikkuna->open();
            }
            else{
                qDebug()<<response_data;
                ui->labelInfo->setText("Väärä ID tai PIN!");
            }

        }

    }
    reply->deleteLater();
    postManager->deleteLater();
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
    Q_UNUSED(event);  // 🔹 Estää käyttämättömän muuttujan varoituksen
    timeoutTimer->start(10000);  // 🔹 Nollataan ajastin hiiren liikkeellä
}


bool Login::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        timeoutTimer->start(10000);  // 🔹 Nollataan ajastin näppäinpainalluksella
    }
    return QDialog::eventFilter(obj, event); // 🔹 Palautetaan tapahtuma normaalisti
}


void Login::onTimeout()
{
    ui->labelInfo->setText("Aikakatkaisu!");
    QTimer::singleShot(2000, this, &QWidget::close); // Suljetaan ikkuna 2 sekunnin päästä
}
