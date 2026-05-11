#pragma once
#include "Interactable.h"
#include <vector>
#include <string>

//represents physical pinboards in the game world
//can hold multiple strings (notices) and potentially one hidden clue
class NoticeBoard : public Interactable {
private:
    std::vector<std::string> notices; // list of messages pinned to the board

public:
    NoticeBoard(const std::string& name, const std::string& description, Clue* clue = nullptr);

    // used by the room builder to populate the board with text
    void addNotice(const std::string& notice);

    // implementation of the interactable interface
    // displays all notices and checks for the hidden clue
    std::string interact() override;
};