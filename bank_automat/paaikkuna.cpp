#include "paaikkuna.h"
#include "qjsonobject.h"
#include "ui_paaikkuna.h"
#include <QMessageBox>

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

void paaikkuna::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
    qDebug()<<"paaikkuna";
    qDebug()<<myToken;
    qDebug() << "Token pääikkunassa: " << myToken;
}

void paaikkuna::on_btnFetchTransactions_clicked()
{
    qDebug()<<card_id;
    qDebug()<<myToken;
qDebug() << "Opening Transactions Window with Account ID: " << selectedAccountId;
    // Luo uusi tapahtumat -ikkuna
    TransactionsForm *transactionsForm = new TransactionsForm(QString::number(selectedAccountId), myToken, this);
    transactionsForm->show(); // Näytä lomake
}


void paaikkuna::on_btnwithdraw_clicked()
{
    withdrawal *withdrawalWindow = new withdrawal(this);

    withdrawalWindow->setAccount(selectedAccountId);

    withdrawalWindow->show();  // Näytetään noston ikkuna
}

void paaikkuna::setUserName(const QString &firstName, const QString &lastName)
{
    ui->labelUsername->setText("Tervetuloa " + firstName + " " + lastName + "!");
}
void paaikkuna::setAccounts(const QJsonArray &accountsArray)
{
    accounts = accountsArray;  // Tallennetaan kirjautumisessa saadut tilit

    qDebug() << "Accounts set in paaikkuna:" << accounts;
}

void paaikkuna::setSelectedAccountId(int accountId)
{
    selectedAccountId = accountId;  // Tallennetaan valittu tilin ID
    qDebug() << "Selected Account ID set to:" << selectedAccountId;
}

void paaikkuna::on_btnBalance_clicked()
{
    ui->label_balance->hide();
    ui->label_transactions->hide();
    ui->label_withdrawal->hide();
    showBalance();
    ui->labelUsername->hide();
}


void paaikkuna::setBalance(double balance) {
    currentBalance = balance;
}

// Metodi saldon näyttämiseen
void paaikkuna::showBalance() {
    ui->label_balance_2->setText("Tilisi saldo on: " + QString::number(currentBalance) + " €");
}

void paaikkuna::on_btnBack_clicked()
{
    ui->label_balance_2->hide();
    ui->label_withdrawal->show();
    ui->label_balance->show();
    ui->label_transactions->show();
}

