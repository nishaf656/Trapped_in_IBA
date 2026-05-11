#include "ChoiceManager.h"

ChoiceManager::ChoiceManager():lastResult("") {
}

void ChoiceManager::setChoices(const std::vector<Choice>& choices) {
  currentChoices=choices;
}

void ChoiceManager::addChoice(const Choice& choice) {
  currentChoices.push_back(choice);
}

void ChoiceManager::clearChoices() {
  currentChoices.clear();
}

std::string ChoiceManager::executeChoice(int index) {
  // check if index is actually in the vector
  if (index<0 || index>=(int)currentChoices.size()) {
    return "Invalid choice.";
  }

  Choice& chosen=currentChoices[index];

  if (!chosen.isAvailable) {
    return "That option isn't available right now.";
  }

  // run the lambda function inside the choice
  lastResult=chosen.action();
  return lastResult;
}

const std::vector<Choice>& ChoiceManager::getChoices() const {
  return currentChoices;
}

std::string ChoiceManager::getLastResult() const {
  return lastResult;
}