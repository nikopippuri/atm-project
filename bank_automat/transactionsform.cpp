#include "transactionsform.h"
#include "ui_transactionsform.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>


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
    QString url = QString("http://localhost:3000/transactions/%1").arg(accountId);
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

    // Parsitaan JSON-vastaus
    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);

    if (jsonDoc.isArray()) {
        QJsonArray transactions = jsonDoc.array();

        for (const QJsonValue &value : transactions) {
            QJsonObject obj = value.toObject();
            qDebug() << "Objekti:" << obj; // Tulostaa koko objektin

        }

        for (const QJsonValue &value : transactions) {
            QJsonObject obj = value.toObject();
            QString formattedText = QString(
                                            "Summa: %3 euroa.\n "
                                            "Päivämäärä: %1")
                                        .arg(obj["timestamp"].toString().replace("T", " ").replace("Z", ""))
                                        .arg(obj["sum"].toString());

            // Lisää muotoiltu teksti listaan
            ui->listWidgetTransactions->addItem(formattedText);

        }
    } else {
        QMessageBox::critical(this, "Virhe", "Virheellinen palvelinvastaus.");
    }

    reply->deleteLater();
}
