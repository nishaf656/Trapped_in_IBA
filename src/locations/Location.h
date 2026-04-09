#pragma once
#include <iostream>
#include "../player/Player.h"
using namespace std;

class Location {
protected:
    string name;
    string description;
public:
    Location(string n,string d);
    virtual void enter();
    virtual void interact(Player &player) = 0;
};