#pragma once
#include <string>
#include <vector>

// player state like energy and flags
// clues arent tracked here to avoid bugs with counting
class Player {
private:
  std::string name;
  float energy; // 0 to 100, 0 means you lose
  std::vector<std::string> decisionFlags; // for checking if you did certain things

public:
  // error if name is empty or energy is weird
  Player(const std::string& name, float startEnergy=100.0f);

  // take energy away
  // clamped at 0 so it doesnt go negative
  void drainEnergy(float amount);

  // add energy back (max 100)
  void restoreEnergy(float amount);

  float getEnergy() const;
  bool isAlive() const; // true if energy > 0

  // save a flag so we know an event happened
  void addFlag(const std::string& flag);
  bool hasFlag(const std::string& flag) const;

  std::string getName() const;
};