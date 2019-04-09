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

    ui->primaryPageStackedWidget->setCurrentIndex(0);
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
    entry thisEntry;

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
    csvFile1.open("C:/Users/Oscar/Desktop/ALAYO---Project-2-Alek/ALAYO---Project-2-Alek/ALAYO/inputMLBInformation.csv");
    if(csvFile1.is_open())
    {
        int index = 0;

        while(!csvFile1.eof())
        {
            QTextStream(stdout) << "filling up map\n";
            getline(csvFile1, iName, ',');
            if(iName == "")
            {
                break;
            }
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
            thisEntry.key = iName;
            thisEntry.value = thisMLB;

            //this makes it so vectors 1 and 2 contain only american teams
            if(thisMLB.getLeague() == "American"){
                v1.push_back(thisEntry);
                v2.push_back(thisEntry);
                v5.push_back(thisEntry);
                v7 = v5;
                v8 = v5;
                v9 = v5;
                v10 = v5;
            }
            //this makes it so vectors 3 and 4 contain only national teams
            else if(thisMLB.getLeague() == "National"){
                v3.push_back(thisEntry);
                v4.push_back(thisEntry);
                v5.push_back(thisEntry);
                v7 = v5;
                v8 = v5;
                v9 = v5;
                v10 = v5;
            }
            if(thisMLB.getRoofType() == "Open"){
                v6.push_back(thisEntry);
            }

            index++;
        }
//        thisMap.popBack();
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

    csvFile2.open("C:/Users/Oscar/Desktop/ALAYO---Project-2-Alek/ALAYO---Project-2-Alek/ALAYO/inputDistance.csv");
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
//        QMessageBox::Warning(nullptr, "error", "Wrong login information! Please try again.");
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
    int min;
    //sorting for american teams via team name
    for(int i = 0; i < v1.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v1.size(); j++){
            if(v1[j].key < v1[min].key){
                min = j;
            }
        }
        swap(v1[min], v1[i]);
    }
    //sorting for american teams via stadium name
    for(int i = 0; i < v2.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v2.size(); j++){
            if(v2[j].value.getStadiumName() < v2[min].value.getStadiumName()){
                min = j;
            }
        }
        swap(v2[min], v2[i]);
    }
    //sorting for national teams via team name
    for(int i = 0; i < v3.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v3.size(); j++){
            if(v3[j].key < v3[min].key){
                min = j;
            }
        }
        swap(v3[min], v3[i]);
    }
    //sorting for national teams via stadium name
    for(int i = 0; i < v4.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v4.size(); j++){
            if(v4[j].value.getStadiumName() < v4[min].value.getStadiumName()){
                min = j;
            }
        }
        swap(v4[min], v4[i]);
    }
    //sorting by park typology
    for(int i = 0; i < v5.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v5.size(); j++){
            if(v5[j].value.getBallParkTypology() < v5[min].value.getBallParkTypology()){
                min = j;
            }
        }
        swap(v5[min], v5[i]);
    }
    //sorting open roof types by team name
    for(int i = 0; i < v6.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v6.size(); j++){
            if(v6[j].key < v6[min].key){
                min = j;
            }
        }
        swap(v6[min], v6[i]);
    }
    //sorting by chronological order
    for(int i = 0; i < v7.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v7.size(); j++){
            if(v7[j].value.getDateOpened() < v7[min].value.getDateOpened()){
                min = j;
            }
        }
        swap(v7[min], v7[i]);
    }
    //sorting by seating capacity
    for(int i = 0; i < v8.size()-1; i++){

        min = i;
        for(int j = i + 1; j < v8.size(); j++){
            if(v8[j].value.getSeatingCapacity() < v8[min].value.getSeatingCapacity()){
                min = j;
            }
        }
        swap(v8[min], v8[i]);
    }
    ui->teamListWidget_1->clear();
    ui->teamListWidget_2->clear();
    ui->teamListWidget_3->clear();
    ui->teamListWidget_4->clear();
    ui->teamListWidget_5->clear();
    ui->teamListWidget_6->clear();
    ui->teamListWidget_7->clear();
    ui->teamListWidget_8->clear();
    ui->teamListWidget_9->clear();
    ui->teamListWidget_10->clear();
    ui->stadiumList_1->clear();
    ui->stadiumList_2->clear();
    ui->stadiumList_3->clear();
    ui->stadiumList_4->clear();
    ui->stadiumList_5->clear();
    ui->stadiumList_6->clear();
    ui->stadiumList_7->clear();
    ui->stadiumList_8->clear();
    ui->stadiumList_9->clear();
    ui->stadiumList_10->clear();
    ui->openRoofList->clear();
    ui->typologyList->clear();
    ui->dateOpenedList->clear();
    ui->seatingCapacityList->clear();
    //for american teams
    for(int i = 0; i < v1.size(); i++){
        ui->stadiumList_1->addItem(QString::fromStdString(v1[i].value.getStadiumName()));
        ui->stadiumList_2->addItem(QString::fromStdString(v2[i].value.getStadiumName()));
        ui->teamListWidget_1->addItem(QString::fromStdString(v1[i].key));
        ui->teamListWidget_2->addItem(QString::fromStdString(v2[i].key));
    }
    //for national teams
    for(int i = 0; i < v3.size(); i++){
        ui->stadiumList_3->addItem(QString::fromStdString(v3[i].value.getStadiumName()));
        ui->stadiumList_4->addItem(QString::fromStdString(v4[i].value.getStadiumName()));
        ui->teamListWidget_3->addItem(QString::fromStdString(v3[i].key));
        ui->teamListWidget_4->addItem(QString::fromStdString(v4[i].key));
    }
    //for open roof
    for(int i = 0; i < v6.size(); i++){
        ui->stadiumList_6->addItem(QString::fromStdString(v6[i].value.getStadiumName()));
        ui->teamListWidget_6->addItem(QString::fromStdString(v6[i].key));
        ui->openRoofList->addItem(QString::fromStdString(v6[i].value.getRoofType()));
    }
    //for everything else
    for(int i = 0; i < v5.size(); i++)
    {
        ui->stadiumList_5->addItem(QString::fromStdString(v5[i].value.getStadiumName()));
        ui->stadiumList_7->addItem(QString::fromStdString(v7[i].value.getStadiumName()));
        ui->stadiumList_8->addItem(QString::fromStdString(v8[i].value.getStadiumName()));
        ui->stadiumList_9->addItem(QString::fromStdString(v9[i].value.getStadiumName()));
        ui->stadiumList_10->addItem(QString::fromStdString(v10[i].value.getStadiumName()));
        ui->teamListWidget_5->addItem(QString::fromStdString(v5[i].key));
        ui->teamListWidget_7->addItem(QString::fromStdString(v7[i].key));
        ui->teamListWidget_8->addItem(QString::fromStdString(v8[i].key));
        ui->teamListWidget_9->addItem(QString::fromStdString(v9[i].key));
        ui->teamListWidget_10->addItem(QString::fromStdString(v10[i].key));
        ui->typologyList->addItem(QString::fromStdString(v5[i].value.getBallParkTypology()));
        ui->dateOpenedList->addItem(QString::number(v7[i].value.getDateOpened()));
        ui->seatingCapacityList->addItem(QString::number(v8[i].value.getSeatingCapacity()));
    }


    ui->userStackedWidget->setCurrentIndex(2);
}

void MainWindow::on_informationBackButton_clicked()
{
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

