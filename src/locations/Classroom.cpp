#include "Classroom.h"

Classroom::Classroom(int roomNumber, bool locked)
    : Location("Classroom " + std::to_string(roomNumber),
               "An empty classroom. Chairs are stacked on desks. "
               "The whiteboard still has today's lecture notes on it.",
               locked),
      roomNumber(roomNumber) {
}

std::string Classroom::onEnter() {
    if (isLocked) {
        return "The door to Classroom " + std::to_string(roomNumber) + " is locked.\n" + lockReason;
    }
    return "You enter Classroom " + std::to_string(roomNumber) + ".\n" + description;
}