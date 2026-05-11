#pragma once
#include "Interactable.h"

// book you can interact with
// read it to maybe find a hidden clue
class Book:public Interactable {
private:
  std::string title; // title of the book

public:
  Book(const std::string& title, const std::string& description, Clue* clue=nullptr);

  // implementing the virtual function from interactable
  std::string interact() override;
};