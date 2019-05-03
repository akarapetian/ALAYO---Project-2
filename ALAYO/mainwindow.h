#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTableWidget>
#include <QDebug>
#include <QVector>
#include <random>

#include "mlb.h"
#include "map.h"
#include "hashmap.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>


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

    void readFromFiles(bool readOriginal);

    void writeToFiles();

    void updateVectors();

    bool isFloatNumber(const QString& Qstring);
    bool isInteger(const QString &mystring);

    vector<vector<int>> createAdjacencyMatrix();

private slots:
    void on_checkBox_showPW_stateChanged(int);

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

    void on_stadiumListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_souvenirListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_souvenirListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_souvenirPriceListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_souvenirPriceListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_capacityLineEdit_textEdited(const QString &arg1);

    void on_surfaceLineEdit_textEdited(const QString &arg1);

    void on_roofTypeLineEdit_textEdited(const QString &arg1);

    void on_typologyLineEdit_textEdited(const QString &arg1);

    void on_dateOpenedLineEdit_textEdited(const QString &arg1);

    void on_distToCenterLineEdit_textEdited(const QString &arg1);

    void on_newLocationLineEdit_textEdited(const QString &arg1);

    void on_actionLogout_triggered();

    void on_visitMultipleButton_clicked();

    void on_visitSingleButton_clicked();

    void on_takeTripButton_user_clicked();

    void on_takeTripPageBackButton_clicked();

    void on_singleSelectionPageBackButton_clicked();

    void on_optimizeButton_clicked();

    void on_multipleSelectionPageBackButton_clicked();

    void on_availibleTeamsStackedWidget_itemChanged(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Map thisMap;
    HashMap encryptionTable;
    bool isAdmin;

    QVector<MLB> allMLBTeamsAvailable;
    QVector<entry> v1;
    QVector<entry> v2;
    QVector<entry> v3;
    QVector<entry> v4;
    QVector<entry> v5;
    QVector<entry> v6;
    QVector<entry> v7;
    QVector<entry> v8;
    QVector<entry> v9;
    QVector<entry> v10;
};

#endif // MAINWINDOW_H
