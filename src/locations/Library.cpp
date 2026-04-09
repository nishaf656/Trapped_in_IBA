#include "Library.h"
#include <iostream>
using namespace std;

Library::Library():Location("Library","Quiet place full of books") {}

void Library::interact(Player &player) {
    cout << "You found a clue in a book!\n";
    player.addClue("Library Code");
}