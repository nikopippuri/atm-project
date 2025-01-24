#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QString card_id, QString auth_token, QWidget *parent = nullptr);
    ~Dashboard();

private slots:


private:
    Ui::Dashboard *ui;
    QString card_id;
    QString auth_token;
};

#endif // DASHBOARD_H
