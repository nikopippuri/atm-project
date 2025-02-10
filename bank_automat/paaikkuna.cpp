#include "paaikkuna.h"
#include "qjsonobject.h"
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
    withdrawal *withdrawalWindow = new withdrawal(this);

    // Oletetaan, että käyttäjällä on vain yksi tili (debit tai credit)
    if (accounts.size() == 1) {
        QJsonObject account = accounts[0].toObject();
        int accountId = account["account_id"].toInt();  // Otetaan tilin ID
        withdrawalWindow->setAccount(accountId);        // Välitetään nostoon
    }

    // Jos käyttäjällä on kombokortti, valittu tili on jo asetettu loginissa
    else if (accounts.size() > 1) {
        // Esimerkkinä valitaan ensimmäinen tili – oikeasti tämä valinta tapahtuu loginissa
        int selectedAccountId = accounts[0].toObject()["account_id"].toInt();
        withdrawalWindow->setAccount(selectedAccountId);
    }

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
