#ifndef TRANSACTIONSFORM_H
#define TRANSACTIONSFORM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class TransactionsForm;
}

class TransactionsForm : public QWidget
{
    Q_OBJECT

public:
    TransactionsForm(const QString &accountId, const QByteArray &myToken, QWidget *parent = nullptr);
    ~TransactionsForm();

private slots:
    void fetchTransactions(); // Hakee tapahtumat
    void onTransactionsFetched(QNetworkReply *reply); // Muokkaa tapahtumia

    void on_btnStop_clicked();

private:
    Ui::TransactionsForm *ui;
    QByteArray myToken; // Tokeni
    QString accountId; // Account
    QNetworkAccessManager *networkManager;
};

#endif // TRANSACTIONSFORM_H
