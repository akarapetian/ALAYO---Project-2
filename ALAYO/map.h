#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include "mlb.h"
using namespace std;

struct entry
{
    string key;
    MLB value;
};

class Map
{
    public:
        //Public default constructor
        Map();

        //Public default destructor
        ~Map();

        //Returns if the map is full or not
        bool isFull();

        //Deletes all elements in the map (used for reinitializing)
        void deleteAll();

        //Deletes the last element in the map
        void popBack();

        // returns entry of the map
        entry& atIndex(int index);

        // returns the size of the map
        int mapSize();

        // Inserts a key and its value using linear algorithm
        void insert(const string& theKey, const MLB& value);

        void printStadium(int index);

        // Prints all the values
        void printAll();

    private:

    vector<entry> thisTable;
    int currentSize;	//Integer variable for current size
};

#endif // MAP_H
