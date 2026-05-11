#include "Clue.h"

Clue::Clue(const std::string& name, const std::string& description)
  : name(name), description(description), collected(false) {
  // initializer list does the work
}

std::string Clue::getName() const {
  return name;
}

std::string Clue::getDescription() const {
  return description;
}

bool Clue::isCollected() const {
  return collected;
}

void Clue::collect() {
  collected=true;
}