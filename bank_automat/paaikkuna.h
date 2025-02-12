#ifndef PAAIKKUNA_H
#define PAAIKKUNA_H

#include <QDialog>
#include "qjsonarray.h"
#include "transactionsform.h"
#include "withdrawal.h"

namespace Ui {
class paaikkuna;
}

class paaikkuna : public QDialog
{
    Q_OBJECT

public:
    explicit paaikkuna(QWidget *parent = nullptr);
    ~paaikkuna();

    QString getCard_id() const;

    void setCard_id(const QString &newCard_id);

    void setMyToken(const QByteArray &newMyToken);
    void setUserName(const QString &firstName, const QString &lastName);
    void setAccounts(const QJsonArray &accountsArray);
    void setSelectedAccountId(int accountId);
    void setBalance(double balance);  // Metodi saldon asettamiseksi
    void showBalance();               // Metodi saldon näyttämiseksi


private slots:
    void on_btnFetchTransactions_clicked();

    void on_btnwithdraw_clicked();

    void on_btnBalance_clicked();

    void on_btnBack_clicked();

private:
    Ui::paaikkuna *ui;
    QString card_id;
    QByteArray myToken;
    withdrawal *withdrawalWindow;
    QJsonArray accounts;
    int selectedAccountId = -1;
    double currentBalance;  // Muuttuja saldolle
};

#endif // PAAIKKUNA_H
