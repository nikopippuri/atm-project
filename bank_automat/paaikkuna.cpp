#include "paaikkuna.h"
#include "ui_paaikkuna.h"

paaikkuna::paaikkuna(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::paaikkuna)
{
    ui->setupUi(this);
}

paaikkuna::~paaikkuna()
{
    delete ui;
}

void paaikkuna::setCard_id(const QString &newCard_id)
{
    card_id = newCard_id;
    ui->labelUsername->setText(card_id);
}

void paaikkuna::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
    qDebug()<<"paaikkuna";
    qDebug()<<myToken;
}

void paaikkuna::on_btnFetchTransactions_clicked()
{
    qDebug()<<card_id;
    qDebug()<<myToken;

    // Luo uusi tapahtumat -ikkuna
    TransactionsForm *transactionsForm = new TransactionsForm(card_id, myToken, this);
    transactionsForm->show(); // Näytä lomake
}


void paaikkuna::on_btnwithdraw_clicked()
{
    withdrawalWindow = new withdrawal(this);
    withdrawalWindow->show();
}

