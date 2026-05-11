#include "Location.h"

Location::Location(const std::string& name, const std::string& description, bool locked)
    : name(name), description(description), isLocked(locked) {
}

void Location::addObject(Interactable* obj) {
    objects.push_back(obj);
}

void Location::addConnection(Location* loc) {
    connectedLocations.push_back(loc);
}

void Location::lock(const std::string& reason) {
    isLocked = true;
    lockReason = reason;
}

void Location::unlock() {
    isLocked = false;
    lockReason = "";
}

std::string Location::getName() const { return name; }
std::string Location::getDescription() const { return description; }
bool Location::getIsLocked() const { return isLocked; }
std::string Location::getLockReason() const { return lockReason; }
std::vector<Interactable*>& Location::getObjects() { return objects; }
std::vector<Location*>& Location::getConnections() { return connectedLocations; }