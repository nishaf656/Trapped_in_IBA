#include "Interactable.h"

Interactable::Interactable(const std::string& name, const std::string& description, Clue* clue)
    : name(name), description(description), hasBeenUsed(false), hiddenClue(clue) {
}

std::string Interactable::getName() const {
    return name; }
std::string Interactable::getDescription() const {
    return description; }

bool Interactable::getHasBeenUsed() const {
    return hasBeenUsed; }

Clue* Interactable::getHiddenClue() const {
    return hiddenClue; 
}