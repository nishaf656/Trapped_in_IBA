#include "player/Player.h"
#include "core/GameError.h"
#include <algorithm> // for std::find

Player::Player(const std::string& name, float startEnergy)
  : name(name), energy(startEnergy)
{
  if (name.empty()) {
    throw InvalidDataError("Player name must not be empty.");
  }
  if (startEnergy<=0.0f || startEnergy>100.0f) {
    throw InvalidDataError("Player start energy must be in range (0, 100]. Got: "+std::to_string(startEnergy));
  }
}

void Player::drainEnergy(float amount) {
  if (amount<0.0f) {
    // negative amount is a bug
    throw InvalidDataError("drainEnergy() requires a non-negative amount. Got: "+std::to_string(amount));
  }
  energy-=amount;
  if (energy<0.0f) energy=0.0f; // dont go below zero
}

void Player::restoreEnergy(float amount) {
  if (amount<0.0f) {
    throw InvalidDataError("restoreEnergy() requires a non-negative amount. Got: "+std::to_string(amount));
  }
  energy+=amount;
  if (energy>100.0f) energy=100.0f; // cap at 100
}

float Player::getEnergy() const { return energy; }
bool Player::isAlive() const { return energy>0.0f; }

void Player::addFlag(const std::string& flag) {
  if (flag.empty()) return;
  if (!hasFlag(flag)) {
    decisionFlags.push_back(flag);
  }
}

bool Player::hasFlag(const std::string& flag) const {
  return std::find(decisionFlags.begin(), decisionFlags.end(), flag)!=decisionFlags.end();
}

std::string Player::getName() const { return name; }