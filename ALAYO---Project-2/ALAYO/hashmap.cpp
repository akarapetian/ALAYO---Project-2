#include "hashmap.h"
#include <iostream>
#include <iomanip>
#include <math.h>

HashMap::HashMap()
{
    table = new Entry* [SIZE]();
    for(int index = 0; index < SIZE; index++)
    {
        table[index] = nullptr;
    }
    currentSize = 0;
}

HashMap::~HashMap()
{

}

bool HashMap::isFull()
{
    if(currentSize == SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void HashMap::putQuadraticHash(const int& theKey, const string& theValue)
{
    //If the hash table is full, immediately exit
    if(isFull())
    {
        return;
    }

    //Declare an instance of Entry
    Entry *newEntry;

    //Store key and value into newEntry
    newEntry = new Entry(theKey, theValue);

    //Iterates through entire hash map, checks if key about to be inserted
    //equals any key currently in the map
    for(int i = 0; i < SIZE; i++)
    {
        //Makes sure program doesn't access cells with nullptr, else it'll crash
        if(table[i] != nullptr)
        {
            //Checks if the table at the current index which isnt nullptr holds
            //the same key as the one to be inserted
            if(table[i]->getKey() == theKey)
            {
                table[i]->setValue(theValue);
                return;
            }
        }
    }

    //FIRST HASH FUNCTION, set equal to int index value
    int index = theKey % 31;

    if(table[index] != nullptr)
    {
        int j = 1;

        int newIndex = (index + (j*j)) % 31;

        if(table[newIndex] == nullptr)
        {
            //Set the open space in table at newIndex with data from newEntry
            table[newIndex] = newEntry;
            return;
        }

        while(table[newIndex] != nullptr)
        {
            //j++;
            int newIndex = (index + (j*j)) % 31;

            if(table[newIndex] == nullptr)
            {
                //Set the open space in table at newIndex with data from newEntry
                table[newIndex] = newEntry;
                break;
            }
            j++;
        }
    }
    else
    {
        //Set the open space in table at newIndex with data from newEntry
        table[index] = newEntry;
    }
}

void HashMap::removeQuad(const int& theKey)
{
    //first hash
    int index = theKey % 31;

    //Checks if the current location in table holds the desired key
    if(table[index]->getKey() != theKey)
    {
        //If true, initialize j and begin quadratic hashing
        int j = 1;

        int newIndex = (index + (j*j)) % 31;

        //Checks if the new hash table location holds the desired key
        if(table[newIndex]->getKey() == theKey)
        {
            table[newIndex] = nullptr;
        }
        else
        {
            //If the desired key was not found, increment j and hash again
            j++;

            while(1)
            {
                //Perform another quadratic hash
                int newIndex = (index + (j*j)) % 31;
                //Check if that hash index holds the desired key
                if(table[newIndex]->getKey() == theKey)
                {
                    table[newIndex] = nullptr;
                    break;
                }
                j++;
            }
        }
    }
    else
    {
        table[index] = nullptr;
    }
}

void HashMap::clearTable()
{
    int index = 0;

    while(index < SIZE)
    {
        if(table[index] != nullptr)
        {
            table[index] = nullptr;
        }

        index++;
    }
}

