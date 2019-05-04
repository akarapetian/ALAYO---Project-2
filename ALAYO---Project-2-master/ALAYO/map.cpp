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
