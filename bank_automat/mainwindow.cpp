#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn0,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn1,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn2,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn3,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn4,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn5,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn6,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn7,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn8,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
    connect(ui->btn9,SIGNAL(clicked()), this,SLOT(on_btn_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn0_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "0";
    ui->LeUserId->setText(currentText);
}

void MainWindow::on_btn1_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "1";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn2_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "2";
    ui->LeUserId->setText(currentText);
}



void MainWindow::on_btn3_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "3";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn4_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "4";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn5_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "5";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn6_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "6";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn7_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "7";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn8_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "8";
    ui->LeUserId->setText(currentText);
}


void MainWindow::on_btn9_clicked()
{
    QString currentText = ui->LeUserId->text();
    currentText += "9";
    ui->LeUserId->setText(currentText);
}

