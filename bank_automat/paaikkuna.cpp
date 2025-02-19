#include "paaikkuna.h"
#include "qjsonobject.h"
#include "ui_paaikkuna.h"
#include <QMessageBox>

paaikkuna::paaikkuna(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::paaikkuna)
{
    ui->setupUi(this);
    ui->label_back->hide();

    balanceChecker = new Balance(this);
    connect(balanceChecker, &Balance::balanceUpdated, this, &paaikkuna::updateBalance);
    connect(balanceChecker, &Balance::errorOccurred, this, &paaikkuna::showBalanceError);
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
    ui->labelBalance->hide();
}


void paaikkuna::on_btnwithdraw_clicked()
{
    withdrawal *withdrawalWindow = new withdrawal(this);

    withdrawalWindow->setAccount(selectedAccountId);
    withdrawalWindow->setMyToken(myToken);

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

void paaikkuna::setBalance(double balance) {
    currentBalance = balance;
}

void paaikkuna::on_btnBalance_clicked()
{
    ui->label_balance->hide();
    ui->labelBalance->show();
    ui->label_transactions->hide();
    ui->label_withdrawal->hide();

    // Haetaan saldo palvelimelta
    if (balanceChecker && selectedAccountId != -1) {
        balanceChecker->fetchBalance(QString::number(selectedAccountId), myToken);
    } else {
        ui->labelBalance->setText("Tilin ID puuttuu tai virheellinen!");
    }
    ui->labelUsername->hide();
    ui->label_back->show();
}


void paaikkuna::updateBalance(double newBalance) {
    currentBalance = newBalance;
    showBalance(); // Päivittää käyttöliittymän, jos tarpeen
}

// Metodi saldon näyttämiseen
void paaikkuna::showBalance() {
    ui->labelBalance->setText("Tilisi saldo on: " + QString::number(currentBalance) + " €");
}

void paaikkuna::on_btnBack_clicked()
{
    ui->labelBalance->hide();
    ui->label_withdrawal->show();
    ui->label_balance->show();
    ui->label_transactions->show();
    ui->label_back->hide();
}

void paaikkuna::showBalanceError(const QString &errorMsg) {
    ui->labelBalance->setText("Virhe: " + errorMsg);
}

