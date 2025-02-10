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

private slots:
    void on_btnFetchTransactions_clicked();

    void on_btnwithdraw_clicked();

private:
    Ui::paaikkuna *ui;
    QString card_id;
    QByteArray myToken;
    withdrawal *withdrawalWindow;
    QJsonArray accounts;
};

#endif // PAAIKKUNA_H
