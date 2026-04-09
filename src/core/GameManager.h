#pragma once
#include "../player/Player.h"
#include "../locations/Library.h"
#include "../locations/ComputerLab.h"
#include <stack>

class GameManager {
private:
    Player player;
    Library library;
    Lab lab;
    stack<string> history;
public:
    void startGame();
};