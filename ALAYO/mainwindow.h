#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    Map thisMap;
};

#endif // MAINWINDOW_H
