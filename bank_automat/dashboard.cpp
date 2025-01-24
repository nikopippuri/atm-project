#include "dashboard.h"
#include "ui_dashboard.h"
#include <QDebug>

Dashboard::Dashboard(QString card_id, QString auth_token, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard),
    card_id(card_id),
    auth_token(auth_token)
{
    ui->setupUi(this);

    // Näytä käyttäjän nimi tervetulotoivotuksena
    ui->labelWelcome->setText("Welcome, tähän haetaan nimi tietokannasta!");

    // Näiden avulla pääsee tekemään historia tai saldo tai nosto toiminnot?
    ui->labelCardId->setText("card_id on: " + card_id);
    ui->labelAuthToken->setText("auth_token on: " + auth_token);


}

Dashboard::~Dashboard()
{
    delete ui;
}

