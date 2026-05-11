#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <stack>
#include "GameState.h"
#include "ChoiceManager.h"
#include "player/Player.h"
#include "AssetManager.h"
#include "../locations/CampusMap.h"
#include "../clues/Clue.h"

class GameManager {

private:
    sf::RenderWindow window;
    sf::Font font;
    AssetManager assets;   //owns all textures for the game lifetime

    GameState currentState;
    CampusMap* campusMap;
    ChoiceManager choiceManager;
    Player* player;

    std::vector<Clue*> allClues;
    std::stack<std::string> locationHistory;

    float timeRemaining;
    std::string displayText;
    int lastClickedBtn;

    //world setup
    void initializeWorld();
    void teardownWorld();
    //choices
    void refreshChoices();

    //helper funcs
    void setDisplay(const std::string& text);
    void appendDisplay(const std::string& text);
    void checkWinLose();
    void checkUnlocks();
    int  countCollectedClues() const;

    //returns asset key for background of curr location eg IBA Library -> "bg_library"
    std::string currentBgKey() const;

    //draws
    void drawMainMenu();
    void drawGame();
    void drawGameOver();
    void drawWin();

    //draws full-window background image (stretched to fit)- falls back to a solid colour if texture is missing.
    void drawBackground(const std::string& assetKey,sf::Color fallback=sf::Color(15,15,25));

    //draw small icon to left of a button
    void drawIcon(const std::string& assetKey, float x, float y,float size=28.f);

    bool button(const std::string& label, float x, float y, float w, float h, int id, 
        sf::Color col = sf::Color(60,100,160));

    void drawWrappedText(const std::string& str, float x, float y,float maxWidth, unsigned int charSize, 
sf::Color col);

    void drawPanel(float x, float y, float w, float h, 
        sf::Color fill= sf::Color(25,25,45), sf::Color outline=sf::Color(80,80,160));

    void drawLabel(const std::string& str, unsigned int size, float x, float y, sf::Color col,
         sf::Text::Style style = sf::Text::Style::Regular);

    void drawCentred(const std::string& str, unsigned int size, float windowWidth, float y, sf::Color col, 
        sf::Text::Style style=sf::Text::Style::Regular);

public:
    //yhrows AssetLoadError if font cant be loaded
    //asset textures loaded with good fallback so there is no throw if image missing
    GameManager();
    
    ~GameManager();
    void run();
};