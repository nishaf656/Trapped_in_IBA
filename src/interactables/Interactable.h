#pragma once
#include <string>
#include "../clues/Clue.h"

//abstract base class for anything clickable in a room
//you can't instantiate this directly; use Book, Computer, etc.
class Interactable {
protected:
    std::string name;        // object name
    std::string description; // text shown when looking at it
    bool hasBeenUsed;        // tracking if we've already clicked it
    Clue* hiddenClue;        // optional clue (can be nullptr)

public:
    Interactable(const std::string& name, const std::string& description, Clue* clue = nullptr);

    // virtual destructor ensures subclasses are cleaned up properly
    virtual ~Interactable() {}

    //every subclass must define what "interacting" actually does
    virtual std::string interact() = 0;

    // getters
    std::string getName() const;
    std::string getDescription() const;
    bool getHasBeenUsed() const;
    Clue* getHiddenClue() const;
};