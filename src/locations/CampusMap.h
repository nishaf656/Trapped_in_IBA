#pragma once
#include <vector>
#include <string>
#include "../locations/Location.h"

// CampusMap holds ALL the locations , manages how you move between them
// the game's world/map
class CampusMap {
private:
    std::vector<Location*> allLocations;    // Every location in the game
    Location* currentLocation;              // Where the player is right now

public:
    CampusMap();
    ~CampusMap();

    // Add a location to the map
    void addLocation(Location* loc);

    // Set starting position
    void setStartLocation(Location* loc);

    // move to a connected location by name
    // Returns a result msg (success or failure w reason)
    std::string moveTo(const std::string& locationName);

    // Get the current location
    Location* getCurrentLocation() const;

    // Get a location by name (for setting up connections)
    Location* getLocationByName(const std::string& name) const;

    // Get names of all places you can go from current location
    std::vector<std::string> getAvailableExits() const;
};