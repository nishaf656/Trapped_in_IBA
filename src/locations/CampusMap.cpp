#include "CampusMap.h"

CampusMap::CampusMap() : currentLocation(nullptr) {
}

CampusMap::~CampusMap() {
    //clean up all locations we own
    for (Location* loc : allLocations) {
        delete loc;
    }
}

void CampusMap::addLocation(Location* loc) {
    allLocations.push_back(loc);
}

void CampusMap::setStartLocation(Location* loc) {
    currentLocation = loc;
}

std::string CampusMap::moveTo(const std::string& locationName) {
    if (currentLocation == nullptr) {
        return "Error: No current location set.";
    }

    // Search the connected locations from current room
    for (Location* loc : currentLocation->getConnections()) {
        if (loc->getName() == locationName) {
            // Found it - check if it's locked
            if (loc->getIsLocked()) {
                return "You try to enter " + locationName + " but it's locked.\n" + loc->getLockReason();
            }
            // Move there
            currentLocation = loc;
            return loc->onEnter();
        }
    }

    return "You can't get to '" + locationName + "' from here.";
}

Location* CampusMap::getCurrentLocation() const {
    return currentLocation;
}

Location* CampusMap::getLocationByName(const std::string& name) const {
    for (Location* loc : allLocations) {
        if (loc->getName() == name) {
            return loc;
        }
    }
    return nullptr;
}

std::vector<std::string> CampusMap::getAvailableExits() const {
    std::vector<std::string> exits;
    if (currentLocation == nullptr) return exits;

    for (Location* loc : currentLocation->getConnections()) {
        exits.push_back(loc->getName());
    }
    return exits;
}