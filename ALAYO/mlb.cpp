#include "mlb.h"

MLB::MLB()
{
    stadiumName = "";
    seatingCapacity = -1;
    location = "";
    playingSurface = "";
    league = "";
    dateOpened = -1;
    distanceToCenterField = -1;
    ballparkTypology = "";
    roofType = "";    
}

MLB::MLB(int nID, string nStadiumName, int nSeatingCapacity, string nLocation, string nPlayingSurface,
         string nLeague, int nDateOpened, int nDistanceToCenterField, string nBallParkTypology, string nRoofType)
{
    ID = nID;
    stadiumName = nStadiumName;
    seatingCapacity = nSeatingCapacity;
    location = nLocation;
    playingSurface = nPlayingSurface;
    league = nLeague;
    dateOpened = nDateOpened;
    distanceToCenterField = nDistanceToCenterField;
    ballparkTypology = nBallParkTypology;
    roofType = nRoofType;
}

MLB::~MLB()
{
}

int MLB:: getID()
{
    return ID;
}

string MLB::getStadiumName()
{
    return stadiumName;
}

int MLB::getSeatingCapacity()
{
    return seatingCapacity;
}

string MLB::getLocation()
{
    return location;
}

string MLB:: getPlayingSurface()
{
    return playingSurface;
}

string MLB::getLeague()
{
    return league;
}

int MLB::getDateOpened()
{
    return dateOpened;
}

int MLB:: getDistanceToCenterField()
{
    return distanceToCenterField;
}

string MLB::getBallParkTypology()
{
    return ballparkTypology;
}

string MLB::getRoofType()
{
    return roofType;
}

int MLB::getDistanceSize()
{
    return distances.size();
}

void MLB::setID(int newID)
{
    this->ID = newID;
}

void MLB::setStadiumName(string newStadiumName)
{
    this->stadiumName = newStadiumName;
}

void MLB::setSeatingCapacity(int newSeatingCapacity)
{
    this->seatingCapacity = newSeatingCapacity;
}

void MLB::setLocation(string newLocation)
{
    this->location = newLocation;
}

void MLB::setPlayingSurface(string newPlayingSurface)
{
    this->playingSurface = newPlayingSurface;
}

void MLB::setLeague(string newLeague)
{
    this->league = newLeague;
}

void MLB::setDateOpened(int newDate)
{
    this->dateOpened = newDate;
}

void MLB::setDistanceToCenterField(int newDistance)
{
    this->distanceToCenterField = newDistance;
}

void MLB::setTypology(string newTypology)
{
    this->ballparkTypology = newTypology;
}

void MLB::setRoofType(string newRoofType)
{
    this->roofType = newRoofType;
}







int MLB::getSouvenirListSize() const
{
    return souvenirs.size();
}

souvenir MLB::getSouvenir(int index) const
{
    return souvenirs[index];
}


void MLB::addSouvenir(souvenir newSouvenir)
{
    souvenirs.push_back(newSouvenir);
}

void MLB::setInitialDistances(int size)
{
    for(int i = 0; i < size; i++)
    {
        this->distances.push_back(0);
    }
}

void MLB::setDistance(int i, int distance)
{
    distances.at(i) = distance;
}

void MLB::printDistances()
{
    for(unsigned long long i = 0; i < distances.size(); i++)
    {
        if(distances.at(i) == 0)
        {
            cout << "   0   ";
        }
        else if(distances.at(i) < 100)
        {
            cout << "   " << distances.at(i) << "  ";
        }
        else if(distances.at(i) < 1000)
        {
            cout << "  " << distances.at(i) << "  ";
        }
        else
        {
            cout << " " << distances.at(i) << "  ";
        }
    }
    cout << endl;
}
