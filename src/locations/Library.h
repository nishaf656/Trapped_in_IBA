#pragma once
#include "Location.h"

class Library:public Location {
public:
    Library();
    void interact(Player &player) override;
};