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
    File: map.h
    Class map for holding the team name as key
    and mlb information as value
*/

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include "mlb.h"
using namespace std;


/** MAP Entry struct, string team, MLB stadium info
* @brief struct for holding key value and MLB stadium information value
*/
struct entry
{
    string key;
    MLB value;
};

/**
* @brief Class map used to handle data manipulation between key and values
*/
class Map
{
    public:

        /**
        * @brief default constructor
        */
        Map();

        /**
        * @brief default destructor
        */
        ~Map();

        /**
        * @brief returns if the map is full or not
        */
        bool isFull();

        /**
        * @brief Deletes all elements in the map (used for reinitializing)
        */
        void deleteAll();

        /**
        * @brief Deletes the last element in the map
        */
        void popBack();

        /**
        * @brief returns entry of the map
        */
        entry& atIndex(int index);

        /**
        * @brief returns the size of the map
        */
        int mapSize();

        /**
        * @brief Inserts a key and its value using linear algorithm
        */
        void insert(const string& theKey, const MLB& value);

    private:

    vector<entry> thisTable; /** < table holding the entries*/
    int currentSize;	/** <Integer variable for current size*/
};

#endif // MAP_H
