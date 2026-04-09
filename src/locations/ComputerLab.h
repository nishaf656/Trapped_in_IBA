#pragma once
#include "Location.h"

class Lab:public Location {
public:
    Lab();
    void interact(Player &player) override;
};