#pragma once
#include <string>

// stuff the player finds to unlock areas/escape
class Clue {
private:
  std::string name; // like "security code"
  std::string description; // what shows up on screen
  bool collected; // got it or not?

public:
  // make a clue with name and text
  Clue(const std::string& name, const std::string& description);

  // getters
  std::string getName() const;
  std::string getDescription() const;
  bool isCollected() const;

  // set to true when found
  void collect();
};