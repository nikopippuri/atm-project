#include "balance.h"
#include "enviroment.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Balance::Balance(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Balance::onReplyFinished);
}

void Balance::fetchBalance(const QString &accountId, const QByteArray &token) {
    // Rakennetaan URL esim. "http://localhost:3000/balance?account_id=<accountId>"
    QString urlString = Enviroment::base_url() + "/balance?account_id=" + accountId;
    QUrl url(urlString);
    QNetworkRequest request(url);
    // Asetetaan token Authorization-headeriin
    request.setRawHeader("Authorization", token);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager->get(request);
}

void Balance::onReplyFinished(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    if(!jsonDoc.isObject()) {
        emit errorOccurred("Virheellinen JSON-vastaus");
        reply->deleteLater();
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    if(jsonObj.contains("balance")) {
        double balance = jsonObj["balance"].toDouble();
        emit balanceUpdated(balance);
    } else {
        emit errorOccurred("Saldoa ei löytynyt vastauksesta");
    }
    reply->deleteLater();
}
