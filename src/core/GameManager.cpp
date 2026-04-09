#include "GameManager.h"
#include <iostream>
using namespace std;

void GameManager::startGame() {
    int choice;

    while (player.energy > 0) {
        cout << "\n1. Library\n2. Lab\n3. Interact\n4. Back\n";
        cin >> choice;
        if (choice == 1) {
            history.push(player.currentLocation);
            player.currentLocation = "Library";
            library.enter();
        }
        else if (choice == 2) {
            history.push(player.currentLocation);
            player.currentLocation = "Lab";
            lab.enter();
        }
        else if (choice == 3) {
            if (player.currentLocation == "Library")
                library.interact(player);
            else if (player.currentLocation == "Lab")
                lab.interact(player);
        }
        else if (choice == 4 && !history.empty()) {
            player.currentLocation = history.top();
            history.pop();
            cout << "Went back\n";
        }

        if (player.clues.size() >= 2) {
            cout << "You escaped!\n";
            break;
        }
    }
    cout << "Game Over\n";
}