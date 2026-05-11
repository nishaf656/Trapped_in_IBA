#pragma once // headr file included only once in complation
#include <string>
#include <vector>
#include "../interactables/Interactable.h"


class Location;

//abstract base class for all places, all inheirt
class Location {
protected:
    std::string name;                           
    std::string description;                    // What the player sees when they enter
    bool isLocked;                              // Can the player enter right now?
    std::string lockReason;                     // Why it's locked 
    std::vector<Interactable*> objects;         // Objects in this room
    std::vector<Location*> connectedLocations;  // Where you can go from here

public:
    Location(const std::string& name, const std::string& description, bool locked = false);

    // Virtual destructor
    virtual ~Location() {}

    // Pure virtual, each location must define what happens on enter
    virtual std::string onEnter() = 0;

    // add an interactable object to this room
    void addObject(Interactable* obj);

    // Connect this room to another , navigates
    void addConnection(Location* loc);

    // Lock or unlock the room
    void lock(const std::string& reason);
    void unlock();

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    bool getIsLocked() const;
    std::string getLockReason() const;
    std::vector<Interactable*>& getObjects();
    std::vector<Location*>& getConnections();
};