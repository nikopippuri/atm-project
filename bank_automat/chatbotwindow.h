#ifndef CHATBOTWINDOW_H
#define CHATBOTWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {
class ChatBotWindow;
}
QT_END_NAMESPACE

class ChatBotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBotWindow(QWidget *parent = nullptr);
    ~ChatBotWindow();

private slots:
private slots:
    void sendMessage();
    void handleResponse();  // Ei parametreja

private:
    Ui::ChatBotWindow *ui;
    QNetworkAccessManager *networkManager;
};

#endif // CHATBOTWINDOW_H
