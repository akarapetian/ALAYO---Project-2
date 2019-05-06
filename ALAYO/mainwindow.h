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
#include "graph.h"

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

    void readFromFiles(bool readOriginal);

    void readExpansionFiles();

    void writeToFiles();

    void resetManageStadiumsInformation();

    void updateVectors();

    void createGraph();

    vector<vector<int>> createAdjacencyMatrix();

    bool isInteger(const QString &string);

    float getSubTotal();

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

    void on_capacityLineEdit_textEdited(const QString &arg1);

    void on_surfaceLineEdit_textEdited(const QString &arg1);

    void on_roofTypeLineEdit_textEdited(const QString &arg1);

    void on_typologyLineEdit_textEdited(const QString &arg1);

    void on_dateOpenedLineEdit_textEdited(const QString &arg1);

    void on_distToCenterLineEdit_textEdited(const QString &arg1);

    void on_actionLogout_triggered();

    void on_visitMultipleButton_clicked();

    void on_visitSingleButton_clicked();

    void on_takeTripButton_user_clicked();

    void on_takeTripPageBackButton_clicked();

    void on_singleSelectionPageBackButton_clicked();

    void on_optimizeButton_clicked();

    void on_multipleSelectionPageBackButton_clicked();

    void on_availibleStadiumsListWidget_itemChanged(QListWidgetItem *item);

    void on_AddTeamButton_clicked();

    void on_ReinitializeButton_clicked();

    void on_performdfsButton_clicked();

    void on_dfsPageBackButton_clicked();

    void on_dfsStadiumsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_dfsPushButton_clicked();

    void on_selectAllTeamsCheckBox_stateChanged(int arg1);

    void on_bfsStadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_bfsPushButton_clicked();

    void on_performbfsButton_clicked();

    void on_bfsPageBackButton_clicked();

    void on_performmstButton_clicked();

    void on_mstStadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_mstPushButton_clicked();

    void on_mstBackButton_clicked();

    void on_addSouvenirPushButton_clicked();

    void on_deleteSouvenirPushButton_clicked();

    void on_souvenirListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_changeSouvenirPriceLineEdit_textEdited(const QString &arg1);

    void on_changeSouvenirPushButton_clicked();

    void on_locationLineEdit_textEdited(const QString &arg1);

    void on_stadiumLineEdit_textEdited(const QString &arg1);

    void on_leagueLineEdit_textEdited(const QString &arg1);

    void on_goButton_clicked();

    void nextStadium();



    void on_tripSouvenirQuantityListWidget_itemDoubleClicked(QListWidgetItem *item);


    void on_tripSouvenirQuantityListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);



    void on_checkoutButton_clicked();

    void on_endTripButton_clicked();

private:
    Ui::MainWindow *ui;
    Map thisMap;
    HashMap encryptionTable;
    bool isAdmin;
    bool isAddedStadium;

    Graph graph;

    vector<string> orderedStadiumList;
    vector<int> orderedWeightsList;

    int currentLocationIndex;

    //int totalDistanceTraveled;
    float subTotal; //subtotal at current location

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
