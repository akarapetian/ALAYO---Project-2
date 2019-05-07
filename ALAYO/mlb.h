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
    File: mlb.h
    Class for initializing and manipulating all MLB
    information stored in the value portion of the
    map.
*/

#ifndef MLB_H
#define MLB_H

#include <QString>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/** Souvenir Struct
* @brief struct for holding souvenirs of each team
*/
struct souvenir
{
    /**
    * @brief default constructor
    */
    souvenir(){}

    /**
    * @brief constructor to create souvenir given item name and price
    * @param nItemName - souvenir name
    * @param nItemPrice - souvenir price
    */
    souvenir(string nItemName, double nItemPrice)
    {
        itemName = nItemName;
        itemPrice = nItemPrice;
    }

    /**
    * @brief default destructor
    */
    ~souvenir(){}

    /**
    * @brief sets the item price
    * @param newPrice - newprice for souvenir
    */
    void setItemPrice(double newPrice)
    {
        this->itemPrice = newPrice;
    }

    /**
    * @brief sets the item name
    * @param newName - new name for souvenir
    */
    void setItemName(string newName)
    {
        this->itemName = newName;
    }

    string itemName;
    double  itemPrice;
};

class MLB
{
public:
    //constructor
    /**
    * @brief default constructor
    */
    MLB();

    /**
    * @brief constructor setting all MLB Information
    * @param nStadiumName - stadium name
    * @param nSeatingCapacity - new seating capacity
    * @param nLocation - new location
    * @param nPlayingSurface - new playing surface
    * @param nLeague - new league
    * @param nDateOpened - new date opened
    * @param nDistanceToCenterField - new distance to center field
    * @param nBallParkTypology - new ballpark typology
    * @param nRoofType - new roof type
    */
    MLB(string nStadiumName, int nSeatingCapacity, string nLocation, string nPlayingSurface,
        string nLeague, int nDateOpened, int nDistanceToCenterField, string nBallParkTypology, string nRoofType);

    /**
    * @brief default destructor
    */
    ~MLB();

    // Getters
    /**
    * @brief gets stadium name
    * @return stadium name
    */
    string   getStadiumName();

    /**
    * @brief gets seating capacity
    * @return seating capacity
    */
    int      getSeatingCapacity();

    /**
    * @brief gets location
    * @return location
    */
    string   getLocation();

    /**
    * @brief gets playing surface
    * @return playing surface
    */
    string   getPlayingSurface();

    /**
    * @brief gets league
    * @return league
    */
    string   getLeague();

    /**
    * @brief gets date opened
    * @return date opened
    */
    int      getDateOpened();

    /**
    * @brief gets distance to center field
    * @return distance to center field
    */
    int      getDistanceToCenterField();

    /**
    * @brief gets ballpark typology
    * @return ballpark typology
    */
    string   getBallParkTypology();

    /**
    * @brief gets roof type
    * @return rooftype
    */
    string   getRoofType();

    /**
    * @brief gets distance vector size
    * @return distance vector size
    */
    int      getDistanceSize();

    /**
    * @brief gets distance at specific index
    * @return distance
    */
    int      getDistance(int i);

    /**
    * @brief gets souvenir vector size
    * @return souvenir vector size
    */
    int      getSouvenirListSize() const;

    /**
    * @brief gets souvenir
    * @return souvenir of type struct souvenir
    */
    souvenir getSouvenir(int index) const;

    // Setters
    /**
    * @brief sets StadiumName
    * @param newStadiumname - new stadium name
    */
    void setStadiumName(string newStadiumName);

    /**
    * @brief sets SeatingCapacity
    * @param newSeatingCapactiy - new seating capacity
    */
    void setSeatingCapacity(int newSeatingCapacity);

    /**
    * @brief sets location
    * @param newLocation - new location
    */
    void setLocation(string newLocation);

    /**
    * @brief sets PlayingSurface
    * @param newPlayingSurface - new playing surface
    */
    void setPlayingSurface(string newPlayingSurface);

    /**
    * @brief sets league
    * @param newLeague - new league
    */
    void setLeague(string newLeague);

    /**
    * @brief sets dateOpened
    * @param newDate - new date
    */
    void setDateOpened(int newDate);

    /**
    * @brief sets DistanceToCenterField
    * @param newDistance - new distance to center field
    */
    void setDistanceToCenterField(int newDistance);

    /**
    * @brief sets typology
    * @param newTypology - new ballpark typology
    */
    void setTypology(string newTypology);

    /**
    * @brief sets roof type
    * @param newRoofType - new roof type
    */
    void setRoofType(string newRoofType);

    /**
    * @brief sets Initial distances (all 0)
    * @param size vector is needed
    */
    void setInitialDistances(int size);

    /**
    * @brief sets a distance at a certain index
    * @param i - index new distance will be added
    * @param distance - new distance to be changed
    */
    void setDistance(int i, int distance);

    // Other Methods
    /**
    * @brief changeSouvenir changes name price and index
    * @param name - name of souvenir
    * @param price - price of the souvenir
    * @param index - index of what souvenir to be changed in souvenir vector
    */
    void changeSouvenir(string name, double price, int index);

    /**
    * @brief pushBackDistance (used when new team is added, adds 0 to back)
    */
    void pushBackDistance();

    /**
    * @brief addSouvenir adds a new souvenir
    * @param souvenir - new souvenir
    */
    void addSouvenir(souvenir newSouvenir);

    /**
    * @brief delete souvenir deletes a souvenir at an index
    * @param index - index of souvenir to be deleted
    */
    void deleteSouvenir(int index);

private:
    string stadiumName; /** <stadium name*/
    int seatingCapacity; /** <seating capacity of the stadium*/
    string location; /** <loaction of the stadium*/
    string playingSurface; /** <playing surface of the stadium*/
    string league; /** <league team is in*/
    int dateOpened; /** <date the stadium was opened*/
    int distanceToCenterField; /** <distance to center field of stadium*/
    string ballparkTypology; /** <ballParkTypology of stadium*/
    string roofType; /** <roof type of stadium*/

    vector<souvenir> souvenirs; /** <vector holding souvenirs of specific team*/
    vector<int> distances; /** <vector holding distances to all other stadiums*/
};

#endif // MLB_H
