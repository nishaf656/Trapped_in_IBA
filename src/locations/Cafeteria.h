#pragma once
#include "Location.h"

// the player can eat here to restore energy.
// Locked initially, unlocked after finding the cafeteria key clue
class Cafeteria : public Location {
public:
    Cafeteria(bool locked = true);
    std::string onEnter() override;
};