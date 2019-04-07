#include "souvenirs.h"

souvenirs::souvenirs()
{
    baseballCap = 22.99;
    baseballBat = 89.39;
    teamPennant = 17.99;
    autographedBaseball = 25.99;
    teamJersey = 199.99;
}

souvenirs::~souvenirs(){}

vector<double> souvenirs::getSouvenirs()
{
    vector<double> thisVector;
    thisVector.push_back(baseballCap);
    thisVector.push_back(baseballBat);
    thisVector.push_back(teamPennant);
    thisVector.push_back(autographedBaseball);
    thisVector.push_back(teamJersey);

    return thisVector;
}

void souvenirs::changeBaseballCap(double nBaseballCap)
{
    baseballCap = nBaseballCap;
}

void souvenirs::changeBaseballBat(double nBaseballBat)
{
    baseballBat = nBaseballBat;
}

void souvenirs::changeTeamPennant(double nTeamPennant)
{
    teamPennant = nTeamPennant;
}

void souvenirs::changeAutographedBaseball(double nAutographedBaseball)
{
    autographedBaseball = nAutographedBaseball;
}

void souvenirs::changeTeamJersey(double nTeamJersey)
{
    teamJersey = nTeamJersey;
}
