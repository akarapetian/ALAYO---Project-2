#ifndef ENTRY_H_
#define ENTRY_H_

const int SIZE = 15;

#include <string>
using namespace std;

class Entry
{
    public:
        Entry           ();				   //Public default constructor

        Entry           (int, string);	   //Public non-default constructor

        ~Entry			();				   //Public default destructor

        int    getKey   () const;		   //Returns private data 'key' to
                                           //calling function
        string getValue () const;		   //Returns private data 'value' to
                                           //calling function
        void   setKey   (int newKey);	   //Recieves new int ket and sets
                                           //private 'key' to 'newKey'
        void   setValue (string newValue); //Recieves new string value and sets
                                           //private 'value' to 'newValue'
                                           //same key, if there is one

    private:
        string value;	//The value to be stored as an entry
        int    key;		//The key associated with its value
};

#endif /* ENTRY_H_ */
