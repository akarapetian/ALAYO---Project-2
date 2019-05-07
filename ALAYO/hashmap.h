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
    File: hashmap.h
    Class for encoding the username and password during
    login processes
*/

#define HASHMAP_H_

#include "Entry.h"
#include <vector>
using namespace std;

class HashMap
{
    public:

        /**
        * @brief Public default constructor
        */
        HashMap();

        /**
        * @brief Public default destructor
        */
        ~HashMap();

        /**
        * @brief Returns if the hash map is full or not
        * @return boolean true or false if map is full
        */
        bool isFull();

        /**
        * @brief Insertion algorithm for the quadratic hash algorithm
        * @param theKey - key value
        * @param theValue - string value linked to key
        */
        void putQuadraticHash(const int& theKey, const string& theValue);

        /**
        * @brief Remove method for the quadratic hash algorithm
        * @param theKey - key value
        */
        void removeQuad(const int& theKey);

        /**
        * @brief Clears the table
        */
        void clearTable();

    private:
    Entry **table;		/** <Double pointer for a table(hash) of entries*/
    int currentSize;	/** <Integer variable for current size*/
};
