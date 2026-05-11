#pragma once
#include "Interactable.h"

// pc you can use in game
// needs a password check before you can see the clue
class Computer:public Interactable {
private:
  bool isPoweredOn; // true if unlocked or no pass
  std::string password; // empty = no password needed

public:
  Computer(const std::string& name, const std::string& description, const std::string& password="", Clue* clue=nullptr);

  // returns a msg. prompts for pass if it's still locked
  std::string interact() override;
  // tries to unlock it. returns if it worked or not
  std::string tryPassword(const std::string& attempt);
  // for the ui to show password buttons
  bool needsPassword() const;
};