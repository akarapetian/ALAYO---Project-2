#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDesktopWidget"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginPushButton_clicked()
{
    if(ui->usernameLineEdit->text() == "admin" && ui->passwordLineEdit->text() == "admin")
    {
        ui->primaryPageStackedWidget->setCurrentIndex(1);
    }
    else if(ui->usernameLineEdit->text() == "user" && ui->passwordLineEdit->text() == "user")
    {
        ui->primaryPageStackedWidget->setCurrentIndex(2);
    }
    else
    {
        //error
        //QMessageBox::Warning(nmullptr, "error", "Wrong login information! Please try again.");
    }
}
