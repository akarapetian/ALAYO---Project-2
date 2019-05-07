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
    File: entry.h
    Class for the map getting and setting the key and
    value for the Hashtable.
*/

#ifndef ENTRY_H_
#define ENTRY_H_

const int SIZE = 15;

#include <string>
using namespace std;

/**
@brief used to hold the key and value of a map.
*/
class Entry
{
    public:
        /** Default constructor
        */
        Entry           ();				   //Public default constructor

        /** Constructor for creating key int key and string value
        @param key - integer holding the key
        @param value - string holding the value
        */
        Entry           (int, string);	   //Public non-default constructor

        /** Destructor
        */
        ~Entry			();				   //Public default destructor

        /** Getkey - returns the key value
        @return key - key value
        */
        int    getKey   () const;		   //Returns private data 'key' to
                                           //calling function
        /** Getvalue - returns the value
        @return value - value of the hashmap
        */
        string getValue () const;		   //Returns private data 'value' to
                                           //calling function
        /** setKey - sets the value of the key
        @param newKey - key value
        */
        void   setKey   (int newKey);	   //Recieves new int ket and sets
                                           //private 'key' to 'newKey'
        /** setValue - sets the value part of the hashmap
        @param newValue - new value
        */
        void   setValue (string newValue); //Recieves new string value and sets
                                           //private 'value' to 'newValue'
                                           //same key, if there is one

    private:
        string value;	/** <The value to be stored as an entry*/
        int    key;		/** <The key associated with its value*/
};

#endif /* ENTRY_H_ */
