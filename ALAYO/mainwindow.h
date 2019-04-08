#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDebug>

#include "mlb.h"
#include "map.h"

#include <fstream>
#include <string>
#include <iostream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void reinitialize();

private slots:
    void on_loginPushButton_clicked();

    void on_manageStadiumsButton_clicked();

    void on_takeTripButton_admin_clicked();

    void on_manageStadiumsBackButton_clicked();

    void on_stadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_informationButton_user_clicked();

    void on_informationBackButton_clicked();

    void on_informationButton_admin_clicked();

    void on_viewStadiumsBackButton_clicked();

    void on_viewStadiumsButton_clicked();

    void on_stadiumListWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;
    Map thisMap;
    bool isAdmin;
};

#endif // MAINWINDOW_H
