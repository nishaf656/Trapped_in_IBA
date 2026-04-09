#include "ComputerLab.h"
#include <iostream>
using namespace std;

Lab::Lab():Location("Lab","Computers everywhere") {}

void Lab::interact(Player &player) {
    cout << "Used a computer. Energy -10\n";
    player.reduceEnergy(10);
}