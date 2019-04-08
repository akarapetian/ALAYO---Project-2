#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDesktopWidget"
#include "QTextStream"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    reinitialize();


    //add default souvenir items to each baseball stadium
    for(int i = 0; i < thisMap.mapSize(); i++)
    {
        thisMap.atIndex(i).value.addSouvenir(souvenir("Baseball cap", 22.99));
        thisMap.atIndex(i).value.addSouvenir(souvenir("Baseball bat", 89.93));
        thisMap.atIndex(i).value.addSouvenir(souvenir("Team pennant", 17.99));
        thisMap.atIndex(i).value.addSouvenir(souvenir("Autographed baseball", 25.99));
        thisMap.atIndex(i).value.addSouvenir(souvenir("Team jersey", 199.99));
    }


    //resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//************************************ PARSING ************************************************

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


    QTextStream(stdout) << "opening csv1\n";
    csvFile1.open("C:/ALAYO---Project-2-master/ALAYO/inputMLBInformation.csv");
    if(csvFile1.is_open())
    {
        int index = 0;

        while(!csvFile1.eof())
        {
            QTextStream(stdout) << "filling up map\n";
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
    }
    else {
        QTextStream(stdout) << "file1 opening failed...\n";
    }

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

    csvFile2.open("C:/ALAYO---Project-2-master/ALAYO/inputDistance.csv");
    if(csvFile2.is_open())
    {
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
    }
    else {
        QTextStream(stdout) << "file2 opening failed...";
    }

    csvFile2.close();

}


//************************************ LOGIN ************************************************

void MainWindow::on_loginPushButton_clicked()
{
    if(ui->usernameLineEdit->text() == "admin" && ui->passwordLineEdit->text() == "admin")
    {
        ui->primaryPageStackedWidget->setCurrentIndex(1);

        isAdmin = true;
    }
    else if(ui->usernameLineEdit->text() == "user" && ui->passwordLineEdit->text() == "user")
    {
        ui->primaryPageStackedWidget->setCurrentIndex(2);
        isAdmin = false;
    }
    else
    {
        //error
        //QMessageBox::Warning(nmullptr, "error", "Wrong login information! Please try again.");
    }
}

//************************************ MANAGING STADIUMS (admin) ************************************************

//if the user presses the manage stadiums button, this method changes the page
void MainWindow::on_manageStadiumsButton_clicked()
{
    ui->adminStackedWidget->setCurrentIndex(1);

    //initialize all the data in the list widgets
    for(int i = 0; i < thisMap.mapSize(); i++)
    {
        ui->stadiumListWidget->addItem(QString::fromStdString(thisMap.atIndex(i).value.getStadiumName()));
    }
}


void MainWindow::on_manageStadiumsBackButton_clicked()
{
    //returns to welcome screen
    ui->adminStackedWidget->setCurrentIndex(0);


    ui->stadiumListWidget->blockSignals(true);
    ui->stadiumListWidget->clear();
    ui->stadiumListWidget->blockSignals(false);
}

void MainWindow::on_stadiumListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->souvenirListWidget->clear();
    ui->souvenirPriceListWidget->clear();
    //if the user clicks on an item, the values in the souvenir list widget, along with all other attributes need to be updated
    for(int i = 0; i < thisMap.atIndex(current->listWidget()->currentRow()).value.getSouvenirListSize(); i++)
    {
        ui->souvenirListWidget->addItem(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getSouvenir(i).itemName));
        ui->souvenirPriceListWidget->addItem(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getSouvenir(i).itemPrice));
    }

    ui->capacityLineEdit->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getSeatingCapacity()));
    ui->surfaceLineEdit->setText(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getPlayingSurface()));
    ui->roofTypeLineEdit->setText(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getRoofType()));
    ui->typologyLineEdit->setText(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getBallParkTypology()));
    ui->dateOpenedLineEdit->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getDateOpened()));
    ui->distToCenterLineEdit->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getDistanceToCenterField()));
    //ui->newLocationLineEdit->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.()));
}

//************************************ VIEWING STADIUMS (user) ************************************************
//if the user presses the manage stadiums button, this method changes the page
void MainWindow::on_viewStadiumsButton_clicked()
{
    ui->userStackedWidget->setCurrentIndex(3);

    //initialize all the data in the list widgets
    for(int i = 0; i < thisMap.mapSize(); i++)
    {
        ui->stadiumListWidget_2->addItem(QString::fromStdString(thisMap.atIndex(i).value.getStadiumName()));
    }
}


void MainWindow::on_viewStadiumsBackButton_clicked()
{
    //returns to welcome screen
    ui->userStackedWidget->setCurrentIndex(0);


    ui->stadiumListWidget_2->blockSignals(true);
    ui->stadiumListWidget_2->clear();
    ui->stadiumListWidget_2->blockSignals(false);
}

void MainWindow::on_stadiumListWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->souvenirListWidget_2->clear();
    ui->souvenirPriceListWidget_2->clear();
    //if the user clicks on an item, the values in the souvenir list widget, along with all other attributes need to be updated
    for(int i = 0; i < thisMap.atIndex(current->listWidget()->currentRow()).value.getSouvenirListSize(); i++)
    {
        ui->souvenirListWidget_2->addItem(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getSouvenir(i).itemName));
        ui->souvenirPriceListWidget_2->addItem(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getSouvenir(i).itemPrice));
    }

    ui->capacityLineEdit_2->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getSeatingCapacity()));
    ui->surfaceLineEdit_2->setText(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getPlayingSurface()));
    ui->roofTypeLineEdit_2->setText(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getRoofType()));
    ui->typologyLineEdit_2->setText(QString::fromStdString(thisMap.atIndex(current->listWidget()->currentRow()).value.getBallParkTypology()));
    ui->dateOpenedLineEdit_2->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getDateOpened()));
    ui->distToCenterLineEdit_2->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.getDistanceToCenterField()));
    //ui->newLocationLineEdit->setText(QString::number(thisMap.atIndex(current->listWidget()->currentRow()).value.()));
}


//************************************ INFORMATION ************************************************

//admin has requested to view stadiums
void MainWindow::on_informationButton_admin_clicked()
{
    //function "reaches" into the user side of the program to re-use the user methods for viewing stadums
    //changes page
    ui->primaryPageStackedWidget->setCurrentIndex(2);
    on_informationButton_user_clicked();
}


//regular user has requested to view stadiums
void MainWindow::on_informationButton_user_clicked()
{
    //initialize data
    //.
    //.
    //.


    ui->userStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_informationBackButton_clicked()
{
    //clear data in viewing lists
    //.
    //.
    //.


    //since this method is shared between admins and regular users, we perform a check
    if(isAdmin)
    {
        ui->primaryPageStackedWidget->setCurrentIndex(1);
        ui->adminStackedWidget->setCurrentIndex(0);
    }
    else
    {
        ui->userStackedWidget->setCurrentIndex(0);
    }
}



//************************************ TAKING TRIPS ************************************************
void MainWindow::on_takeTripButton_admin_clicked()
{
    //function "reaches" into the user side of the program to re-use the user methods for taking a trip
    //changes page
    ui->primaryPageStackedWidget->setCurrentIndex(2);
    ui->userStackedWidget->setCurrentIndex(1);
}

