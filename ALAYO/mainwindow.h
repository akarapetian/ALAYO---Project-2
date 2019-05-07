/*
 *  Baseball Trip Project
 *  Spring 2019
 *
 *  Oscar Lopez <olopez23@saddleback.edu>
 *  Anthony Karapetian <akarapetian1@saddleback.edu>
 *  Alek Peratoner <aperatoner0@saddleback.edu>
 *  Luke Schrezenmeier <lschrezenmeier0@saddleback.edu>
 *  Yuchen Yao <yyao7@ivc.edu>
 *
 *  Descr: Baseball Project for Spring 2019 CS1D
 *  Professor: Jerry Lebowitz
 *
 *  This program is an application in which a baseball
 *  can view information regarding any major league
 *  baseball team as well as take a dream trip and
 *  visit any stadium wanted.
 *
 **/
/*
    File: mainwindow.h
    Class for handling all the front end portion of
    the application
*/

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

/**
* @brief Mainwindow class used to handle all of the UI
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * @brief Constructor for mainwindow
    */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
    * @brief Destructor for mainwindow
    */
    ~MainWindow();

    /**
    * @brief Reads from files and stores into map.
    * @param readOriginal - used for reinitializing all data
    */
    void readFromFiles(bool readOriginal);

    /**
    * @brief Reads the expansion files to add extra team
    */
    void readExpansionFiles();

    /**
    * @brief Writes all information to files so program is persistent
    */
    void writeToFiles();

    /**
    * @brief Resets all information, updates as soon as something is changed
    */
    void resetManageStadiumsInformation();

    /**
    * @brief Updates the vectors in order for the view stadiums tabs to be updated
    */
    void updateVectors();

    /**
    * @brief Reads from file to create all edges using all baseball stadiums and distances
    */
    void createGraph();

    /**
    * @brief creates matrix of all distances, returns 2d vector
    * @return 2dVector - 2d vector of type matrix holding distances
    */
    vector<vector<int>> createAdjacencyMatrix();

    /**
    * @brief boolean isInteger checks if input is an integer
    * @return isInteger - true if its an int false if not
    */
    bool isInteger(const QString &string);

    /**
    * @brief getSubtotal returns the total of purchased items
    * @return total - price
    */
    float getSubTotal();

private slots:

    /**
    * @brief checkbox for showing the password in login screen
    * @param int state - state in which checkbox is in
    */
    void on_checkBox_showPW_stateChanged(int);

    /**
    * @brief handles the function when login is pressed. Encrypts
    *        username and password and checks if it exists
    */
    void on_loginPushButton_clicked();

    /**
    * @brief handles when manage stadiums button was clicked (admin)
    */
    void on_manageStadiumsButton_clicked();

    /**
    * @brief handles when take a trip button was clicked (admin)
    */
    void on_takeTripButton_admin_clicked();

    /**
    * @brief handles the back button for take a trip (admin)
    */
    void on_manageStadiumsBackButton_clicked();

    /**
    * @brief Used to reach and display the information after the user would like to see a new stadium
    * @param current - current item clicked
    * @param previous - item taken off of
    */
    void on_stadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Used to handle information button clicked (user)
    */
    void on_informationButton_user_clicked();

    /**
    * @brief Used to handle information back button clicked (user)
    */
    void on_informationBackButton_clicked();

    /**
    * @brief Used to handle view information button clicked (admin)
    */
    void on_informationButton_admin_clicked();

    /**
    * @brief used to handle view stadiums back button clicked (user/admin)
    */
    void on_viewStadiumsBackButton_clicked();

    /**
    * @brief used to handle view stadiums button clicked (user)
    */
    void on_viewStadiumsButton_clicked();

    /**
    * @brief Used to handle when user wants to view a different stadium (user)
    * @param current - the current item user is viewing
    * @param previous - the last item the user was viewing
    */
    void on_stadiumListWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief used to handle when the capacity line is edited, changes in database
    * @param arg1 - new capacity
    */
    void on_capacityLineEdit_textEdited(const QString &arg1);

    /**
    * @brief used to handle when the surface line is edited, changes in database
    * @param arg1 - new surface
    */
    void on_surfaceLineEdit_textEdited(const QString &arg1);

    /**
    * @brief used to handle when the rooftype is edited
    * @param arg1 - new rooftype
    */
    void on_roofTypeLineEdit_textEdited(const QString &arg1);

    /**
    * @brief used to handle when typology line is edited, changes in databse
    * @param arg1 - new typology
    */
    void on_typologyLineEdit_textEdited(const QString &arg1);

    /**
    * @brief used to handle when date line is edited, changes in database
    * @param arg1 - new date
    */
    void on_dateOpenedLineEdit_textEdited(const QString &arg1);

    /**
    * @brief used to handle distance to center field is edited, changes in database
    * @param arg1 - new distance to center field
    */
    void on_distToCenterLineEdit_textEdited(const QString &arg1);

    /**
    * @brief Used to handle when the user/admin would like to logout
    */
    void on_actionLogout_triggered();

    /**
    * @brief Used to handle when the user would like to visit multiple locations
    */
    void on_visitMultipleButton_clicked();

    /**
    * @brief Used to handle when the user clicks on take a trip
    */
    void on_takeTripButton_user_clicked();

    /**
    * @brief used to handle when the user clicks the back button on take a trip page
    */
    void on_takeTripPageBackButton_clicked();

    /**
    * @brief Used to handle when the user clicks optimize (runs Dijkstra, finds shortest path)
    */
    void on_optimizeButton_clicked();

    /**
    * @brief Used to handle multiple selection page back button
    */
    void on_multipleSelectionPageBackButton_clicked();

    /**
    * @brief Used to handle when user views a different stadium
    * @param item - new item changed
    */
    void on_availibleStadiumsListWidget_itemChanged(QListWidgetItem *item);

    /**
    * @brief Used to handle when admin adds new team (calls readFromExpansionFiles())
    */
    void on_AddTeamButton_clicked();

    /**
    * @brief Used to handle reinitialize (calls readFromFiles(true)), resets all data
    */
    void on_ReinitializeButton_clicked();

    /**
    * @brief Used to handle when user clicks on DFS button in take a trip
    */
    void on_performdfsButton_clicked();

    /**
    * @brief Used to handle when user clicks back button on DFS page
    */
    void on_dfsPageBackButton_clicked();

    /**
    * @brief Used to handle when user would like to change their starting team in dfs page
    * @param current - the new stadium
    * @param previous - the previous stadium
    */
    void on_dfsStadiumsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Runs DFS given the initial stadium chosen by user. Displays the total distance
    */
    void on_dfsPushButton_clicked();

    /**
    * @brief Handles the select all teams checkbox in dfs
    * @param arg1 - state of checkbox
    */
    void on_selectAllTeamsCheckBox_stateChanged(int arg1);

    /**
    * @brief Used to handle the bfs starting stadium
    * @param current - the current stadium
    * @param previous - the previous stadium
    */
    void on_bfsStadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Runs BFS using the starting stadium, displays the total distance traveled
    */
    void on_bfsPushButton_clicked();

    /**
    * @brief Handles when user would like to go to BFS page
    */
    void on_performbfsButton_clicked();

    /**
    * @brief Handles when user would like to go back to take a trip page from BFS page
    */
    void on_bfsPageBackButton_clicked();

    /**
    * @brief Handles when user would like to enter MST page
    */
    void on_performmstButton_clicked();

    /**
    * @brief Handles when the user would like to change their starting stadium
    * @param current - current stadium selected
    * @param previous -previous stadium selected
    */
    void on_mstStadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Runs Prims MST given the initial stadium, displays the total distance
    */
    void on_mstPushButton_clicked();

    /**
    * @brief Handles the back button in MST to go back to take a trip page
    */
    void on_mstBackButton_clicked();

    /**
    * @brief Handles when the user would like to add a souvenir push button
    */
    void on_addSouvenirPushButton_clicked();

    /**
    * @brief Handles the delete souvenir push button
    */
    void on_deleteSouvenirPushButton_clicked();

    /**
    * @brief Handles when user would like to view a different souvenir
    * @param current - current souvenir
    * @param previous - previous souvenir
    */
    void on_souvenirListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Handles when the admin would like to change souvenir price
    * @param arg1 - new price
    */
    void on_changeSouvenirPriceLineEdit_textEdited(const QString &arg1);

    /**
    * @brief handles when the admin wants to change a souvenir
    */
    void on_changeSouvenirPushButton_clicked();

    /**
    * @brief Handles when admin changes the location of a stadium
    * @param arg1 - new location
    */
    void on_locationLineEdit_textEdited(const QString &arg1);

    /**
    * @brief Handles when admin changes stadium name
    * @param arg1 - new stadium name
    */
    void on_stadiumLineEdit_textEdited(const QString &arg1);

    /**
    * @brief Handles when admin changes league
    * @param arg1 - new league name
    */
    void on_leagueLineEdit_textEdited(const QString &arg1);

    /**
    * @brief Handles when user would like to take trip with specified teams
    */
    void on_goButton_clicked();

    /**
    * @brief Handles souvenir purchasing at the next stadium available
    */
    void nextStadium();

    /**
    * @brief Handles when user would like to change how many souvenirs to buy at each stadium
    * @param item - new number
    */
    void on_tripSouvenirQuantityListWidget_itemDoubleClicked(QListWidgetItem *item);

    /**
    * @brief Handles when user would like to change how many souvenirs to buy at each stadium
    * @param current - the current number in the listwidget
    * @param previous - the previous number in the listwidget
    */
    void on_tripSouvenirQuantityListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    /**
    * @brief Handles when user would like to travel to next restaurant (calls nextStadium())
    */
    void on_checkoutButton_clicked();

    /**
    * @brief Handles when the user would like to end the trip
    */
    void on_endTripButton_clicked();

    /**
    * @brief Handles when the souvenir add item price is edited (checks for -1)
    * @param arg1 - new price
    */
    void on_souvenirAddItemPriceTextEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui; /** <Object for mainwindow*/
    Map thisMap; /** Creates the map that will hold all stadium and team information*/
    HashMap encryptionTable; /** <creates encryption table for password encryption*/
    bool isAdmin; /** <boolean for if user is an admin or not*/
    bool isAddedStadium; /** <boolean for if stadium is added (used for displaying picture)*/
    Graph graph; /** <graph for running dijkstra, DFS, BFS, and MST*/
    vector<string> orderedStadiumList;  /** <stadiumList for taking a trip*/
    vector<int> orderedWeightsList;  /** <weight list for taking a trip*/
    int currentLocationIndex; /** <currentLocationIndex used for knowing the exact location in taking a trip*/
    float subTotal; /** <subtotal at current location*/

    QVector<entry> v1; /** <Holds stadiums Major League, used to sort by name*/
    QVector<entry> v2; /** <Holds stadiums Major League, used to sort by stadium*/
    QVector<entry> v3; /** <Holds stadiums American League*/
    QVector<entry> v4; /** <Holds stadiums National League*/
    QVector<entry> v5; /** <Holds stadiums by Park Typology*/
    QVector<entry> v6; /** <Holds stadiums With Open roof type*/
    QVector<entry> v7; /** <Holds stadiums by chronological date order*/
    QVector<entry> v8; /** <Holds stadiums by seating capacity*/
    QVector<entry> v9; /** <Holds stadiums by greatest distance to center field*/
    QVector<entry> v10; /** <Holds stadiums by smallest distance to center field*/
};

#endif // MAINWINDOW_H
