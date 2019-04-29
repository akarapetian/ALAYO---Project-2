#include "map.h"

Map::Map()
{
    currentSize = 0;
}

Map::~Map()
{
}

void Map::insert(const string& theKey, const MLB& value)
{
    entry thisEntry;
    thisEntry.key = theKey;
    thisEntry.value = value;

    thisTable.push_back(thisEntry);

    currentSize+=1;
}

int Map::mapSize()
{
    return currentSize;
}

entry& Map::atIndex(int index)
{
    return thisTable.at(index);
}

void Map::deleteAll()
{
    for(int i = 0; i < currentSize; i++)
    {
        thisTable.pop_back();
    }
    currentSize = 0;
}

void Map::popBack()
{
    thisTable.pop_back();
    currentSize-=1;
}

void Map::printAll()
{
    for(unsigned long long i = 0; i < currentSize; i++)
    {
        cout << "key: " << thisTable.at(i).key << endl;
        cout << "ID: " << thisTable.at(i).value.getID() << endl;
        cout << "Stadium Name: " << thisTable.at(i).value.getStadiumName() << endl;
        cout << "Seating Capacity: " << thisTable.at(i).value.getSeatingCapacity() << endl;
        cout << "Location: " << thisTable.at(i).value.getLocation() << endl;
        cout << "Playing Surface: " << thisTable.at(i).value.getPlayingSurface() << endl;
        cout << "League: " << thisTable.at(i).value.getLeague() << endl;
        cout << "Date Opened: " << thisTable.at(i).value.getDateOpened() << endl;
        cout << "Distance to Center Field: " << thisTable.at(i).value.getDistanceToCenterField() << endl;
        cout << "Ballpark Typology: " << thisTable.at(i).value.getBallParkTypology() << endl;
        cout << "Roof Type: " << thisTable.at(i).value.getRoofType() << endl;
        cout << endl;
    }
}
