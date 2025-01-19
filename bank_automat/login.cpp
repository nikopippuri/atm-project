#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

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

    QString site_url="http://localhost:3000/Login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    postManager = new QNetworkAccessManager(this);
    connect(postManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(LoginSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());

}

void Login::LoginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}

void Login::on_btn0_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "0";
    ui->LeUserId->setText(currentText);
}

void Login::on_btn1_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "1";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn2_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "2";
    ui->LeUserId->setText(currentText);
}



void Login::on_btn3_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "3";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn4_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "4";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn5_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "5";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn6_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "6";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn7_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "7";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn8_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "8";
    ui->LeUserId->setText(currentText);
}


void Login::on_btn9_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "9";
    ui->LeUserId->setText(currentText);
}

