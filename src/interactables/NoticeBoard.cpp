#include "NoticeBoard.h"

NoticeBoard::NoticeBoard(const std::string& name, const std::string& description, Clue* clue)
    : Interactable(name, description, clue) {
}

void NoticeBoard::addNotice(const std::string& notice) {
    notices.push_back(notice);
}

std::string NoticeBoard::interact() {
    std::string result ="You look at the notice board. Several papers are pinned up:\n\n";

    if (notices.empty()) {
        result += "(The board is empty)\n";
    } else {
        // list all the notices pinned to the board
        for (int i = 0; i < (int)notices.size(); i++) {
            result += "- " + notices[i] + "\n";
        }
    }

    // check for a clue tucked behind the papers
    if (!hasBeenUsed && hiddenClue != nullptr && !hiddenClue->isCollected()) {
        hasBeenUsed = true;
        hiddenClue->collect();
        result+="\nWait - something is tucked behind one of the notices...\n";
        result+="CLUE FOUND: " + hiddenClue->getName() + "\n" + hiddenClue->getDescription();
    } else {
        hasBeenUsed=true;
    }

    return result;
}