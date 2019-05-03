#ifndef MLB_H
#define MLB_H

#include <QString>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct souvenir
{
    souvenir(){}
    souvenir(string nItemName, float nItemPrice)
    {
        itemName = nItemName;
        itemPrice = nItemPrice;
    }
    ~souvenir(){}

    void setItemName(string newName)
    {
        this->itemName = newName;
    }

    void setItemPrice(float newPrice)
    {
        this->itemPrice = newPrice;
    }

    string itemName;
    float  itemPrice;
};

class MLB
{
public:
    //constructor
    MLB();
    MLB(int id, string nStadiumName, int nSeatingCapacity, string nLocation, string nPlayingSurface,
        string nLeague, int nDateOpened, int nDistanceToCenterField, string nBallParkTypology, string nRoofType);
    ~MLB();
    // Getters
    int getID();
    string getStadiumName();
    int getSeatingCapacity();
    string getLocation();
    string getPlayingSurface();
    string getLeague();
    int getDateOpened();
    int getDistanceToCenterField();
    string getBallParkTypology();
    string getRoofType();
    int getDistanceSize();

    void setID(int newID);
    void setStadiumName(string newStadiumName);
    void setSeatingCapacity(int newSeatingCapacity);
    void setLocation(string newLocation);
    void setPlayingSurface(string newPlayingSurface);
    void setLeague(string newLeague);
    void setDateOpened(int newDate);
    void setDistanceToCenterField(int newDistance);
    void setTypology(string newTypology);
    void setRoofType(string newRoofType);



    int getSouvenirListSize() const;
    souvenir getSouvenir(int index) const;

    void addSouvenir(souvenir newSouvenir);

    void setInitialDistances(int size);
    void setDistance(int i, int distance);
    void printDistances();
private:
    int ID;
    string stadiumName;
    int seatingCapacity;
    string location;
    string playingSurface;
    string league;
    int dateOpened;
    int distanceToCenterField;
    string ballparkTypology;
    string roofType;

    vector<souvenir> souvenirs;

    vector<int> distances;
};

#endif // MLB_H
