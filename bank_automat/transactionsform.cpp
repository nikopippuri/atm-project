#include "transactionsform.h"
#include "ui_transactionsform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include "enviroment.h"


TransactionsForm::TransactionsForm(const QString &accountId, const QByteArray &myToken, QWidget *parent) :

    QWidget(parent),
    ui(new Ui::TransactionsForm),
    accountId(accountId),
    myToken(myToken),
    networkManager(new QNetworkAccessManager(this))

{
    ui->setupUi(this);
    fetchTransactions();

}

TransactionsForm::~TransactionsForm()
{
    delete ui;
}

void TransactionsForm::fetchTransactions()
{

    QString url = QString("%1/api/transactions/%2").arg(Enviroment::base_url()).arg(accountId);

    QNetworkRequest request((QUrl(url)));

    request.setRawHeader("Authorization", myToken); // Lisätään tokeni

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkManager->get(request); // Lähetä GET-pyyntö

    connect(networkManager, &QNetworkAccessManager::finished, this, &TransactionsForm::onTransactionsFetched);
}

void TransactionsForm::onTransactionsFetched(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "Virhe", "Tapahtumien haku epäonnistui: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();


    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    reply->deleteLater();

    if (!jsonDoc.isArray()) {
        QMessageBox::critical(this, "Virhe", "Virheellinen palvelinvastaus.");
        return;
    }

    allTransactions.clear();
    for (const QJsonValue &value : jsonDoc.array()) {
        allTransactions.append(value.toObject());
    }

    currentPage = 0;
    updateTransactionList();
}



void TransactionsForm::on_btnStop_clicked()
{
    this->close();
}

void TransactionsForm::updateTransactionList()
{
    ui->listWidgetTransactions->clear(); // Tyhjennetään lista ennen päivitystä


    std::sort(allTransactions.begin(), allTransactions.end(), [](const QJsonObject &a, const QJsonObject &b) {
        return a["timestamp"].toString() > b["timestamp"].toString();
    });

    int startIdx = currentPage * itemsPerPage;
    int endIdx = qMin(startIdx + itemsPerPage, allTransactions.size());

    for (int i = startIdx; i < endIdx; ++i) {
        QJsonObject obj = allTransactions[i];

        QString timestamp = obj["timestamp"].toString().left(10);

        QString formattedText = QString(
                                    "Summa: %1 euroa.\nPäivämäärä: %2")
                                    .arg(obj["sum"].toString())
                                    .arg(timestamp); // Käytetään muokattua päivämäärää

        ui->listWidgetTransactions->addItem(formattedText);
    }

    // Päivitetään napit (estetään siirtyminen mahdottomiin suuntiin)
    ui->btnNext->setEnabled(endIdx < allTransactions.size());
    ui->btnPrevious->setEnabled(currentPage > 0);
}

void TransactionsForm::on_btnNext_clicked()
{
    if ((currentPage + 1) * itemsPerPage < allTransactions.size()) {
        currentPage++;
        updateTransactionList();
    }
}

void TransactionsForm::on_btnPrevious_clicked()
{
    if (currentPage > 0) {
        currentPage--;
        updateTransactionList();
    }
}
