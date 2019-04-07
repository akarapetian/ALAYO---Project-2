#ifndef MLB_H
#define MLB_H

#include <QString>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

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
    vector<int> distances;
};

#endif // MLB_H
