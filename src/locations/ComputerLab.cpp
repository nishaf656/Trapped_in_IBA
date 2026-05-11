#include "ComputerLab.h"

ComputerLab::ComputerLab(const std::string& labName, bool locked)
    : Location("Computer Lab " + labName,
               "Rows of desktop computers, all in sleep mode. "
               "The AC is still running. A few screens glow faintly.",
               locked),
      labName(labName) {
}

std::string ComputerLab::onEnter() {
    if (isLocked) {
        return "Computer Lab " + labName + " is locked.\n" + lockReason;
    }
    return "You enter Computer Lab " + labName + ".\n" + description;
}