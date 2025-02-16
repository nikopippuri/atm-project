#include "paaikkuna.h"
#include "ui_paaikkuna.h"
#include <QDebug>

paaikkuna::paaikkuna(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::paaikkuna)
{
    ui->setupUi(this);

    // Alustetaan Balance-olio
    balanceChecker = new Balance(this);
    connect(balanceChecker, &Balance::balanceUpdated, this, &paaikkuna::updateBalance);
    connect(balanceChecker, &Balance::errorOccurred, this, &paaikkuna::showBalanceError);
}

paaikkuna::~paaikkuna()
{
    delete ui;
}

QString paaikkuna::getCard_id() const {
    return card_id;
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

// Uusi slot, jota kutsutaan nappia painettaessa saldon hakemiseksi
void paaikkuna::on_btnCheckBalance_clicked() {
    // Käytetään card_idä ja myTokenia API-kutsussa
    balanceChecker->fetchBalance(card_id, myToken);
}

// Päivitetään UI:n saldo-label
void paaikkuna::updateBalance(double newBalance) {
    ui->labelBalance->setText("Saldo: " + QString::number(newBalance) + " euroa");
}

// Näytetään virheilmoitus, jos API-kutsu epäonnistuu
void paaikkuna::showBalanceError(const QString &errorMsg) {
    ui->labelBalance->setText("Virhe: " + errorMsg);
}
