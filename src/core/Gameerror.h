#pragma once
#include <stdexcept>
#include <string>

//base class for all game errors
//catch this to handle any game problem or catch subclasses for specific ones
class GameError:public std::runtime_error {
public:
  explicit GameError(const std::string& msg):std::runtime_error("[GameError] "+msg) {}
};

//thrown when a font or texture won't load so game basically cant run if this happens
class AssetLoadError:public GameError {
public:
  explicit AssetLoadError(const std::string& path):GameError("Failed to load required asset: "+path) {}
};

//when the world is set up wrong
// null ptrs or double names etc
class WorldSetupError:public GameError {
public:
  explicit WorldSetupError(const std::string& msg):GameError("World setup error: "+msg) {}
};

//for when you try to do something impossible like moving to a room that isnt connected
class InvalidActionError:public GameError {
public:
  explicit InvalidActionError(const std::string& msg):GameError("Invalid action: "+msg) {}
};

//for when input numbers are weird or out of range
class InvalidDataError:public GameError {
public:
  explicit InvalidDataError(const std::string& msg):GameError("Invalid data: "+msg) {}
};