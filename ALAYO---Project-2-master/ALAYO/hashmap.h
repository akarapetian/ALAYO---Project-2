
#define HASHMAP_H_

#include "Entry.h"
#include <vector>
using namespace std;

class HashMap
{
    public:
        //Public default constructor
        HashMap();

        //Public default destructor
        ~HashMap();

        //Returns if the hash map is full or not
        bool isFull();

        //Insertion algorithm for the quadratic hash algorithm
        void putQuadraticHash(const int& theKey, const string& theValue);

        //Remove method for the quadratic hash algorithm
        void removeQuad(const int& theKey);

        void clearTable();

    private:
    Entry **table;		//Double pointer for a table(hash) of entries
    int currentSize;	//Integer variable for current size
};
