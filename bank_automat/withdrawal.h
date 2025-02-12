#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H
#include <QString>
#include <QDialog>

#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class withdrawal;
}

class withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit withdrawal(QWidget *parent = nullptr);
    void setAccount(int accountId);
    ~withdrawal();

private slots:

    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn50_clicked();
    void on_btn100_clicked();
    void on_btn1_clicked();
    void on_btnDifSum_clicked();
    void on_btnClear_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void on_btn0_clicked();
    void on_btnStop_clicked();
    void on_btnArrow8_clicked();// takaisin nappi
    void on_btnOk_clicked();

    void onApiResponse(QNetworkReply *reply);

private:
    Ui::withdrawal *ui;
    QNetworkAccessManager *networkManager;
    QString customSum;
    void updateCustomSum();
    int selectedSum = 0;
    void sendWithdrawalRequest(int amount);
    void sumOn();
    void sumOff();
    void numpadopen();
    void numpadlocked();
    int selected_account_id = -1;
    QByteArray myToken;

};

#endif // WITHDRAWAL_H
