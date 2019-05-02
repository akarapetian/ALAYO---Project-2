#include "Entry.h"

//Default constructor sets private data to default values
Entry::Entry()
{
    key   = 0;
    value = "Not Specified";
}

//Non-default constructor sets private data to specified values
Entry::Entry(int theKey, string theValue)
{
    key   = theKey;
    value = theValue;
}

Entry::~Entry()
{

}

//Returns the private attribute 'key' to calling program
int Entry::getKey() const
{
    return key;
}

//Returns the private attribute 'value' to the calling program
string Entry::getValue() const
{
    return value;
}

//Sets the private attribute 'key' to new integer 'newKey'
void Entry::setKey(int newKey)
{
    key = newKey;
}

//Sets the private attribute 'value' to new string 'newValue'
void Entry::setValue(string newValue)
{
    value = newValue;
}
