#include "Book.h"

Book::Book(const std::string& title, const std::string& description, Clue* clue)
  : Interactable(title, description, clue), title(title) {
}

std::string Book::interact() {
  if (hasBeenUsed) {
    return "You already read this book. Nothing new to find here.";
  }

  hasBeenUsed=true;

  // check if a clue is tucked inside the book
  if (hiddenClue!=nullptr && !hiddenClue->isCollected()) {
    hiddenClue->collect();
    return "You flip through the pages of '"+title+ 
           "' and find a handwritten note!\nCLUE FOUND: "+hiddenClue->getName()+ 
           "\n"+hiddenClue->getDescription();
  }

  return "You read '"+title+"'. Interesting, but nothing useful stands out.";
}