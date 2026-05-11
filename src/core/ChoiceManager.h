#pragma once
#include <string>
#include <vector>
#include <functional>

// a single choice (like "look at desk")
struct Choice {
  std::string label; // text for the button
  std::function<std::string()> action; // what happens (returns msg)
  bool isAvailable; // show it or not?

  Choice(const std::string& label, std::function<std::string()> action, bool available=true)
    : label(label), action(action), isAvailable(available) {}
};

// manager to build and run choice lists
// handles making buttons for looking around, moving rooms, etc.
class ChoiceManager {
private:
  std::vector<Choice> currentChoices; // current buttons on screen
  std::string lastResult; // result from the last thing clicked

public:
  ChoiceManager();

  // clear everything and set new ones
  void setChoices(const std::vector<Choice>& choices);

  // add one choice to the list
  void addChoice(const Choice& choice);

  // wipe the list
  void clearChoices();

  // run a choice using its index
  // returns the string result or error if index is bad
  std::string executeChoice(int index);

  // for the renderer to draw stuff
  const std::vector<Choice>& getChoices() const;

  // get the message from last action
  std::string getLastResult() const;
};