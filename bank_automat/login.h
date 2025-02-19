#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer> // Aikakatkaisuun
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QTimer *timeoutTimer; // Aikakatkaisuun
    QByteArray myToken;

private slots:
    void on_btnClear_clicked();
    void on_btnLogin_2_clicked();
    void LoginSlot (QNetworkReply *reply);
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void onTimeout(); // Aikakatkaisu funktio
    void mouseMoveEvent(QMouseEvent *event); // Hiiren liikutus
    bool eventFilter(QObject *obj, QEvent *event);
    void selectAccountType(const QString &selectedAccountType, const QJsonArray &accounts, const QString &fname, const QString &lname);

    void fetchBalance(const QByteArray &token, int accountId, const QString &fname, const QString &lname);
};

#endif // LOGIN_H
