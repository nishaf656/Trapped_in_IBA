#pragma once
#include "Location.h"


// player starts here when the game begins
class Library : public Location {
public:
    Library();

    //whar the player sees when they first walk in
    std::string onEnter() override;
};