#ifndef BALANCE_H
#define BALANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Balance : public QObject {
    Q_OBJECT
public:
    explicit Balance(QObject *parent = nullptr);
    void fetchBalance(const QString &accountId, const QByteArray &token);

signals:
    void balanceUpdated(double newBalance);
    void errorOccurred(const QString &errorMsg);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // BALANCE_H
