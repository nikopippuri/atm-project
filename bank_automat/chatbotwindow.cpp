#include "chatbotwindow.h"
#include "ui_chatbotwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>


ChatBotWindow::ChatBotWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatBotWindow)
{
    ui->setupUi(this); // Liittää Designerin UI:n

    networkManager = new QNetworkAccessManager(this);

    // Yhdistä painike lähetysfunktioon
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatBotWindow::sendMessage);



    ui->chatDisplay->append("<p style='color: orange; font-weight: bold;'>Asiakaspalvelija(Bot): " "Kuinka voin auttaa?");
}

ChatBotWindow::~ChatBotWindow()
{
    delete ui;
}

void ChatBotWindow::sendMessage()
{
    QString message = ui->inputField->text();
    if (message.isEmpty()) return;

    // Lisää viesti chat-näkymään
    ui->chatDisplay->append("<p style='color: green; font-weight: bold;'>Sinä: " + message);
    ui->inputField->clear();

    // Luo API-kutsu Node.js-palvelimelle
    QNetworkRequest request(QUrl("http://localhost:3000/chat"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["message"] = message;

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &ChatBotWindow::handleResponse);
}

void ChatBotWindow::handleResponse()
{
    // Hanki QNetworkReply signaalista
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        QString botResponse = jsonObject["response"].toString();
        ui->chatDisplay->append("<p style='color: orange; font-weight: bold;'>Asiakaspalvelija(Bot): </p>" + botResponse);


    } else {
        ui->chatDisplay->append("Virhe palvelimen kanssa.");
    }

    reply->deleteLater();
}
