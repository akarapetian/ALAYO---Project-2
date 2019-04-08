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

void MainWindow::reinitialize()
{
    // creates a blank map and sets it to the main window map, so it is all deleted
    Map blankMap;
    thisMap = blankMap;

    string iStadiumName;
    string iName;
    string iSeatingCapacity;
    string iLocation;
    string iPlayingSurface;
    string iLeague;
    string iDateOpened;
    string iDistanceToCenterField;
    string iBallparkTypology;
    string iRoofType;

    ifstream csvFile1;
    csvFile1.open("C:/Users/Oscar/Desktop/CS1D/Project 2 - ALAYO/QT Alayo/ALAYO/inputMLBInformation.csv");

    int index = 0;

    while(!csvFile1.eof())
    {
        getline(csvFile1, iName, ',');
        getline(csvFile1, iStadiumName, ',');
        getline(csvFile1, iSeatingCapacity, ',');
        int iSeatingcapacity = stoi(iSeatingCapacity);
        csvFile1.ignore(1);
        getline(csvFile1, iLocation, '"');
        csvFile1.ignore(1);
        getline(csvFile1, iPlayingSurface, ',');
        getline(csvFile1, iLeague, ',');
        getline(csvFile1, iDateOpened, ',');
        int iDateopened = stoi(iDateOpened);
        getline(csvFile1, iDistanceToCenterField, ',');
        int idistanceToCenterField = stoi(iDistanceToCenterField);
        getline(csvFile1, iBallparkTypology, ',');
        getline(csvFile1, iRoofType, '\n');

        MLB thisMLB(index, iStadiumName, iSeatingcapacity,
                    iLocation, iPlayingSurface, iLeague,
                    iDateopened, idistanceToCenterField,
                    iBallparkTypology, iRoofType);

        thisMap.insert(iName, thisMLB);
        index++;
    }
    thisMap.popBack();
    csvFile1.close();

    string iStadium1;
    string iStadium2;
    string iDistance;
    string previous;
    int distance;
    int index1;
    int index2;
    bool found;

    ifstream csvFile2;
    csvFile2.open("C:/Users/Oscar/Desktop/CS1D/Project 2 - ALAYO/QT Alayo/ALAYO/inputDistance.csv");

    getline(csvFile2, iStadium1, ',');
    while(!csvFile2.eof())
    {
        index1 = 0;
        found = false;
        while(!found)
        {
            if(thisMap.atIndex(index1).value.getStadiumName() == iStadium1)
            {
                thisMap.atIndex(index1).value.setInitialDistances(thisMap.mapSize());
                found = true;
            }
            else
            {
                index1++;
            }
        }

        previous = iStadium1;

        while(iStadium1 == previous)
        {
            getline(csvFile2, iStadium2, ',');
            getline(csvFile2, iDistance, '\n');
            distance = stoi(iDistance);

            index2 = 0;
            found = false;

            while(!found)
            {
                if(thisMap.atIndex(index2).value.getStadiumName() == iStadium2)
                {
                    found = true;
                    thisMap.atIndex(index1).value.setDistance(index2, distance);
                }
                else
                {
                    index2++;
                }
            }
            getline(csvFile2, iStadium1, ',');
        }
        thisMap.atIndex(index1).value.printDistances();
    }

    csvFile2.close();

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
