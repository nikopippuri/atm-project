#include "withdrawal.h"
#include "ui_withdrawal.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

withdrawal::withdrawal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::withdrawal)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    connect(networkManager, &QNetworkAccessManager::finished, this, &withdrawal::onApiResponse);

    ui->btn1->setEnabled(false);
    ui->btn2->setEnabled(false);
    ui->btn3->setEnabled(false);
    ui->btn4->setEnabled(false);
    ui->btn5->setEnabled(false);
    ui->btn6->setEnabled(false);
    ui->btn7->setEnabled(false);
    ui->btn8->setEnabled(false);
    ui->btn9->setEnabled(false);
    ui->btn0->setEnabled(false);
}

withdrawal::~withdrawal()
{
    delete ui;
}

void withdrawal::sendWithdrawalRequest(int amount)
{
    QUrl url("http://localhost:3000/api/withdraw");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["account_id"] = 1;
    json["amount"] = amount;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    networkManager->post(request, data);
}
/*
void withdrawal::onApiResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {

        QByteArray responseData = reply->readAll();



        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonResponse.object();


        if (jsonObj.contains("message")) {
            QString message = jsonObj["message"].toString();
            ui->labelChosenSum->setText(message);
        }
    } else {

        ui->labelChosenSum->setText("Virhe nostossa: " + reply->errorString());
    }


    reply->deleteLater();
}

*/

void withdrawal::onApiResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Server response: " << responseData;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonResponse.object();

        if (jsonObj.contains("message")) {
            QString message = jsonObj["message"].toString();
            ui->labelChosenSum->setText(message);
        } else {
            ui->labelChosenSum->setText("Tuntematon virhe tapahtui.");
        }
    } else {
        ui->labelChosenSum->setText("Virhe nostossa: " + reply->errorString());
    }

    reply->deleteLater();
}


int amount = 0;

void withdrawal::on_btn20_clicked()
{
    amount = 20;
    ui->labelChosenSum->setText("Valittu summa = 20€ ");
}

void withdrawal::on_btn40_clicked()
{
    amount = 40;
    ui->labelChosenSum->setText("Valittu summa = 40€");
}

void withdrawal::on_btn50_clicked()
{
    amount = 50;
    ui->labelChosenSum->setText("Valittu summa = 50€ ");
}

void withdrawal::on_btn100_clicked()
{
    amount = 100;
    ui->labelChosenSum->setText("Valittu summa = 100€ ");
}

void withdrawal::on_btnOk_clicked()
{


    if (!customSum.isEmpty()) {
        amount = customSum.toInt();
        customSum.clear();
    } else if (selectedSum > 0) {
        amount = selectedSum;
    }

    if (amount > 19) {
        sendWithdrawalRequest(amount);
        ui->labelChosenSum->setText("Nosto käsitellään...");

    } else if  (amount < 20){
        ui->labelChosenSum->setText("Minimi nosto on 20€");

    } else {
        ui->labelChosenSum->setText("Valitse ensin nostettava summa!");
    }

}

void withdrawal::updateCustomSum()
{
    ui->labelChosenSum->setText("Valittu summa = " + customSum + "€");
}

void withdrawal::on_btnDifSum_clicked()
{
    ui->btn1->setEnabled(true);
    ui->btn2->setEnabled(true);
    ui->btn3->setEnabled(true);
    ui->btn4->setEnabled(true);
    ui->btn5->setEnabled(true);
    ui->btn6->setEnabled(true);
    ui->btn7->setEnabled(true);
    ui->btn8->setEnabled(true);
    ui->btn9->setEnabled(true);
    ui->btn0->setEnabled(true);

    customSum.clear();
    updateCustomSum();
}


void withdrawal::on_btnClear_clicked()
{
    customSum.clear();
    updateCustomSum();
}


void withdrawal::on_btn1_clicked()
{   customSum += "1";
    updateCustomSum();}

void withdrawal::on_btn2_clicked()
{   customSum += "2";
    updateCustomSum();}

void withdrawal::on_btn3_clicked()
{   customSum += "3";
    updateCustomSum();}

void withdrawal::on_btn4_clicked()
{   customSum += "4";
    updateCustomSum();}

void withdrawal::on_btn5_clicked()
{   customSum += "5";
    updateCustomSum();}

void withdrawal::on_btn6_clicked()
{   customSum += "6";
    updateCustomSum();}

void withdrawal::on_btn7_clicked()
{   customSum += "7";
    updateCustomSum();}

void withdrawal::on_btn8_clicked()
{   customSum += "8";
    updateCustomSum();}

void withdrawal::on_btn9_clicked()
{   customSum += "9";
    updateCustomSum();}

void withdrawal::on_btn0_clicked()
{   customSum += "0";
    updateCustomSum();}

void withdrawal::on_btnStop_clicked()
{
    this->close();
}

void withdrawal::on_btnArrow8_clicked() //takaisin nappi
{
    this->close();
}
