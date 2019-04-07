#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mlb.h"
#include "map.h"
#include <QMainWindow>
#include <fstream>
#include <string>
#include <iostream>
#include <QDebug>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void reinitialize();
//    void loadDistances();
//    void loadNewMLBInformation();
//    void loadNewDistances();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Map thisMap;

};

#endif // MAINWINDOW_H
