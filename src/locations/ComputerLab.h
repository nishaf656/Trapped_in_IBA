#pragma once
#include "Location.h"

// has PCs that might have useful files or emails
class ComputerLab : public Location {
private:
    std::string labName;    // "Lab A" or "Lab B"

public:
    ComputerLab(const std::string& labName, bool locked = false);

    std::string onEnter() override;
};