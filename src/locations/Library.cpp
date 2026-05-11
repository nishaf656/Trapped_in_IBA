#include "Library.h"

Library::Library()
    : Location("IBA Library",
               "The library is dimly lit. Rows of bookshelves stretch into the dark. "
               "The main exit door is visible but sealed shut with an electronic lock.",
               false) {
    // Library starts unlocked , where player wakesup
}

std::string Library::onEnter() {
    return "You find yourself in the IBA Library. The lights flicker. "
           "It's way past closing time and you're alone.\n"
           "The main gate is locked. You need to find another way out.\n\n"
           + description;
}