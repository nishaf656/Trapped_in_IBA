#include "Computer.h"

Computer::Computer(const std::string& name, const std::string& description,
                   const std::string& password, Clue* clue)
  : Interactable(name, description, clue), password(password)
{
  // if there's no password it's already on
  isPoweredOn=password.empty(); 
}

std::string Computer::interact() {
  if (!isPoweredOn) {
    return "The screen glows with a login prompt.\n"
           "This computer is password-protected. Try the password buttons below.";
  }
  if (hasBeenUsed) {
    return "You already checked "+name+". The files are still open on screen.";
  }

  hasBeenUsed=true;

  if (hiddenClue!=nullptr && !hiddenClue->isCollected()) {
    hiddenClue->collect();
    return "You browse through the files and find an open email.\n\n"
           "CLUE FOUND: "+hiddenClue->getName()+"\n"
    +hiddenClue->getDescription();
  }

  return "You browse through "+name+"'s files. Nothing sensitive here.";
}

std::string Computer::tryPassword(const std::string& attempt) {
  if (isPoweredOn) {
    return name+" is already unlocked. No password needed.";
  }
  if (attempt.empty()) {
    return "You didn't type anything. The cursor blinks at you.";
  }
  if (attempt==password) {
    isPoweredOn=true;
    return "Correct password! "+name+" unlocks.\n\n"+interact();
  }
  return "Wrong password. The screen flashes red. Try again.";
}

bool Computer::needsPassword() const {
  // if it's still locked show the password buttons
  return !isPoweredOn;
}