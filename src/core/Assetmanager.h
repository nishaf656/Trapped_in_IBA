#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "GameError.h"

// loads textures once and keeps them in memory
// call getTexture() by name so we dont load the same file twice
// rule: sprites need the texture to stay alive. since this manager
// lives the whole game, we're good.
// if a file is missing, it shows a magenta box instead of crashing
class AssetManager {
public:
  // call this at the start to load everything
  // prints a warning if a file is missing but doesnt stop the game
  void loadAll();

  // get a texture by name (like "library")
  // returns the pink placeholder if the name isnt found
  const sf::Texture& getTexture(const std::string& name) const;

  // check if we actually have the texture
  bool has(const std::string& name) const;

private:
  // try to load one file, if it fails use the placeholder
  void load(const std::string& name, const std::string& filepath);

  // name -> texture map
  std::unordered_map<std::string, sf::Texture> textures;

  // pink square for missing art
  mutable sf::Texture placeholderTexture;
  mutable bool placeholderReady=false;

  // makes the placeholder texture if its not ready yet
  const sf::Texture& placeholder() const;
};