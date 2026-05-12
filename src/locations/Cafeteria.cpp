#include "Cafeteria.h"

Cafeteria::Cafeteria(bool locked)
  : Location("Cafeteria",
             "The canteen is dark but the serving counter is visible. "
             "There is some leftover chowmein and iced tea from the evening. "
             "Eating something here might restore your energy.",
             locked) {
  if (locked) {
    lockReason = "The cafeteria shutters are down. You need a way to open them.";
  }
}

std::string Cafeteria::onEnter() {
  if (isLocked) {
    // blocked by shutters
    return "The cafeteria shutters are pulled down and locked.\n" + lockReason;
  }
  return "You step into the dimly lit cafeteria.\n" + description;
}