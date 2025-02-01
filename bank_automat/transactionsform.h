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

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

private:
    Ui::TransactionsForm *ui;
    QByteArray myToken; // Tokeni
    QString accountId; // Account
    QNetworkAccessManager *networkManager;

    QVector<QJsonObject> allTransactions; // Kaikki haetut tapahtumat
    int currentPage = 0; // Nykyinen sivu
    const int itemsPerPage = 7; // Montako tapahtumaa näytetään per sivu

    void updateTransactionList();
};

#endif // TRANSACTIONSFORM_H
