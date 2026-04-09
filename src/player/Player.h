#pragma once
#include <vector>
#include <string>
using namespace std;

class Player {
public:
    int energy;
    vector<string> clues;
    string currentLocation;

    Player();
    void addClue(string clue);
    void reduceEnergy(int amount);
};