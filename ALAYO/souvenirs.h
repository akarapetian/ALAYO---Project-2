#ifndef SOUVENIRS_H
#define SOUVENIRS_H

#include <vector>
using namespace std;

class souvenirs
{
public:
    souvenirs();
    ~souvenirs();
    vector<double> getSouvenirs();
    void changeBaseballCap(double nBaseballCap);
    void changeBaseballBat(double nBaseballBat);
    void changeTeamPennant(double nTeamPennant);
    void changeAutographedBaseball(double nAutographedBaseball);
    void changeTeamJersey(double nTeamJersey);

private:
    double baseballCap;
    double baseballBat;
    double teamPennant;
    double autographedBaseball;
    double teamJersey;
};

#endif // SOUVENIRS_H
