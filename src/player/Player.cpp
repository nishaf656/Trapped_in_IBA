#include "Player.h"

Player::Player() {
    energy=100;
    currentLocation="Library";
}

void Player::addClue(string clue) {
    clues.push_back(clue);
}

void Player::reduceEnergy(int amount) {
    energy-=amount;
}