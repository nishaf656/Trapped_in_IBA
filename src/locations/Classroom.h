#pragma once
#include "Location.h"

// classroom w desks, a whiteboard, maybe a clue on the board
class Classroom : public Location {
private:
    int roomNumber;     //  Room 101

public:
    Classroom(int roomNumber, bool locked = false);

    std::string onEnter() override;
};