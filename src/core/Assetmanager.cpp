#include "AssetManager.h"
#include <iostream>

// add new images here
// logical name is what we use in code, path is where the file is
static const std::pair<std::string, std::string> MANIFEST[]={
  // backgrounds
  {"bg_library","assets/images/bg_library.png"},
  {"bg_classroom","assets/images/bg_classroom.png"},
  {"bg_lab_a","assets/images/bg_lab_a.png"},
  {"bg_lab_b","assets/images/bg_lab_b.png"},
  {"bg_cafeteria","assets/images/bg_cafeteria.png"},

  // menus and screens
  {"bg_menu","assets/images/bg_menu.png"},
  {"bg_win","assets/images/bg_win.png"},
  {"bg_gameover","assets/images/bg_gameover.png"},

  // icons for buttons
  {"icon_book","assets/images/icon_book.png"},
  {"icon_computer","assets/images/icon_computer.png"},
  {"icon_noticeboard","assets/images/icon_noticeboard.png"},
  {"icon_food","assets/images/icon_food.png"},

  // ui stuff
  {"ui_panel","assets/images/ui_panel.png"},
  {"ui_clue_badge","assets/images/ui_clue_badge.png"},
  {"logo","assets/images/logo.png"},
};

void AssetManager::loadAll() {
  for (const auto& [name,path]:MANIFEST) {
    load(name,path);
  }
}

void AssetManager::load(const std::string& name, const std::string& filepath) {
  sf::Texture tex;
  if (tex.loadFromFile(filepath)) {
    // make it look smooth when scaled
    tex.setSmooth(true);
    textures[name]=std::move(tex);
  } else {
    // print warning if file is missing
    std::cerr<<"[AssetManager] WARNING: couldnt load "<<filepath<<". using placeholder\n";
  }
}

const sf::Texture& AssetManager::getTexture(const std::string& name) const {
  auto it=textures.find(name);
  if (it==textures.end()) {
    return placeholder();
  }
  return it->second;
}

bool AssetManager::has(const std::string& name) const {
  return textures.count(name)>0;
}

const sf::Texture& AssetManager::placeholder() const {
  if (!placeholderReady) {
    // make a pink square so we know something is missing
    sf::Image img({64,64},sf::Color(255,0,255));
    if (placeholderTexture.loadFromImage(img)) {
      placeholderReady=true;
    }
  }
  return placeholderTexture;
}