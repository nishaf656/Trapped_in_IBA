#include "GameManager.h"
#include "GameError.h"
#include "../locations/Library.h"
#include "../locations/Classroom.h"
#include "../locations/ComputerLab.h"
#include "../locations/Cafeteria.h"
#include "../interactables/Book.h"
#include "../interactables/Computer.h"
#include "../interactables/NoticeBoard.h"
#include "../interactables/EnergyItem.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>


GameManager::GameManager():window(sf::VideoMode({960u, 680u}), "Trapped in IBA: After Hours"),
currentState(GameState::MAIN_MENU),
    campusMap(nullptr),
    player(nullptr),
    timeRemaining(600.0f),
    lastClickedBtn(-1)
{
    window.setFramerateLimit(60);

    //font req - throw if not found
    bool fontLoaded = font.openFromFile("assets/arial.ttf");
    if (!fontLoaded)
        fontLoaded = font.openFromFile(
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    if (!fontLoaded)
        fontLoaded = font.openFromFile(
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    if (!fontLoaded)
        throw AssetLoadError("assets/arial.ttf");

    //textures - not req missing ones fall back to magenta placeholder
    assets.loadAll(); }

GameManager::~GameManager() { teardownWorld(); }

//world 
void GameManager::teardownWorld() {
    choiceManager.clearChoices();
    delete campusMap; 
    campusMap=nullptr;
    delete player;     
    player=nullptr;
    for (Clue* c:allClues) 
    delete c;
    allClues.clear();
    while (!locationHistory.empty()) 
    locationHistory.pop();
    timeRemaining=600.0f;
    displayText.clear();
}

void GameManager::initializeWorld() {
    teardownWorld();

    CampusMap* map=nullptr;
    Player* p=nullptr;
    std::vector<Clue*> clues;

    try {
        map=new CampusMap();
        p=new Player("Student",100.0f);

        //clues
    clues.push_back(new Clue("Gate Override Code",
        "A sticky note falls out:\n"
        "\"Emergency gate code: 4-7-2-1\"\n"
        "Maybe the security panel near the exit?"));

    clues.push_back(new Clue("Lab B Keypad Code",
        "A notebook margin scribble:\n"
        "\"Remind self: Lab B code = CS101\"\n"
        "Written in red pen."));

clues.push_back(new Clue("Staff Exit Location",
        "An email on screen reads:\n"
        "\"The staff-only side exit near the canteen\n"
        "opens with the same code as the main gate.\""));

    clues.push_back(new Clue("Cafeteria Shutter Code",
        "A note taped to the monitor:\n"
        "\"Canteen shutter pin: 0000 (still not changed lol)\""));

    Clue* clueGate=clues[0];
    Clue* clueLabB =clues[1];
    Clue* clueExit=clues[2];
    Clue* clueCaf=clues[3];

        //locations
        Library* library =new Library();
        Classroom* room204 = new Classroom(204,false);
        ComputerLab* labA = new ComputerLab("A",false);
        ComputerLab* labB = new ComputerLab("B",true);
        Cafeteria* cafeteria = new Cafeteria(true);

        labB->lock(
            "The keypad blinks red. You need the access code.");

        cafeteria->lock("The shutters are down. There's a number pad on the side.");

        //library
        library->addObject(new Book("OOP Textbook",
            "A dog-eared copy of C++ How to Program. A sticky note sticks out.", clueGate));
        NoticeBoard* libBoard = new NoticeBoard( "Library Notice Board", "A cork board covered in papers near the entrance.");
        libBoard->addNotice("Library hours: Mon-Sat, 8am-8pm.");
        libBoard->addNotice("LOST: One grey hoodie near the CS section.");
        libBoard->addNotice("OOP study group - WhatsApp Nisha for details.");
        libBoard->addNotice("Do not feed the campus cats inside the building.");
        library->addObject(libBoard);

        //class 204
        room204->addObject(new Book( "Forgotten Notebook", "A spiral notebook left on a desk. Full of messy lecture notes.",clueLabB));
        NoticeBoard* classBoard=new NoticeBoard( "Whiteboard", "Today's recursion lecture notes are still up.");
        classBoard->addNotice( "Recursion: a function that calls itself.");
        classBoard->addNotice( "Always define the base case first!");
        classBoard->addNotice( "Midterm covers chapters 1-8.");
        room204->addObject(classBoard);

        //lab a
        labA->addObject( new Computer( "PC-07", "An old desktop still logged into a student profile.",
            "", clueCaf));
        labA->addObject(new Computer(
            "PC-12",
            "A newer model, password protected. Belongs to a professor.","iba2025", clueExit));

    NoticeBoard* labBoard=new NoticeBoard( "Lab Rules Board","A laminated sheet taped to the wall.");
        labBoard->addNotice("No food or drink near computers.");
        labBoard->addNotice("Log off when done.");
        labBoard->addNotice("Lab B: CS dept only. See Ms. Sadaf to get access.");
        labA->addObject(labBoard);

        //cafe
        cafeteria->addObject(new EnergyItem("Leftover Bambou chowmein", "Cold chowmein..yum! Midnight snack!", 30.0f));
        cafeteria->addObject(new EnergyItem( "Chugg's peach iced tea", "So refreshing on a hot day! Better than anything!", 20.0f));

        //connect
        library->addConnection(room204);  
        room204->addConnection(library);
        library->addConnection(labA);     
        labA->addConnection(library);
        labA->addConnection(labB);        
        labB->addConnection(labA);
        labA->addConnection(cafeteria);   
        cafeteria->addConnection(labA);

        //reguster
        map->addLocation(library);
        map->addLocation(room204);
        map->addLocation(labA);
        map->addLocation(labB);
        map->addLocation(cafeteria);
        map->setStartLocation(library);


        campusMap=map;
        player=p;
        allClues=clues;

        setDisplay(library->onEnter());
        refreshChoices();

    } 
    catch (...) {
        for (Clue* c:clues) 
        delete c;
        delete map;
        delete p;
        throw;  } }
// handles refreshing the list of buttons
void GameManager::refreshChoices() {
  choiceManager.clearChoices();
  Location* here=campusMap?campusMap->getCurrentLocation():nullptr;
  if (!here) return;

  for (Interactable* obj:here->getObjects()) {
    choiceManager.addChoice(Choice(
      "Examine: "+obj->getName(),
      [obj, this]() -> std::string {
        std::string result=obj->interact();
        EnergyItem* ei=dynamic_cast<EnergyItem*>(obj);
        if (ei && ei->wasConsumed())
          player->restoreEnergy(ei->getRestoreAmount());
        player->drainEnergy(5.0f);
        checkUnlocks();
        refreshChoices(); //update after interacting
        return result;
      }
    ));

    Computer* comp=dynamic_cast<Computer*>(obj);
    if (comp && comp->needsPassword()) {
      for (const std::string& pw:{"iba2024","CS101","4721","0000"}) {
        choiceManager.addChoice(Choice(
          "Try password \""+pw+"\" on "+obj->getName(),
          [comp, pw=std::string(pw), this]() -> std::string {
            std::string result=comp->tryPassword(pw);
            player->drainEnergy(3.0f);
            checkUnlocks();
            refreshChoices();
            return result;
          }
        ));
      }
    }
  }

  for (const std::string& exitName:campusMap->getAvailableExits()) {
    choiceManager.addChoice(Choice(
      "Go to: "+exitName,
      [exitName, this]() -> std::string {
        locationHistory.push(campusMap->getCurrentLocation()->getName());
        std::string result=campusMap->moveTo(exitName);
        player->drainEnergy(10.0f);
        refreshChoices();
        return result;
      }
    ));
  }

  if (!locationHistory.empty()) {
    choiceManager.addChoice(Choice(
      "<-- Go Back",
      [this]() -> std::string {
        std::string prev=locationHistory.top();
        locationHistory.pop();
        std::string result=campusMap->moveTo(prev);
        player->drainEnergy(5.0f);
        refreshChoices();
        return result;
      }
    ));
  }

  // check if we have everything to win
  if (countCollectedClues()>=(int)allClues.size() && !allClues.empty()) {
    choiceManager.addChoice(Choice(
      "*** USE CLUES TO ESCAPE THE CAMPUS ***",
      [this]() -> std::string {
        currentState=GameState::WIN;
        return "";
      }
    ));
  }
}

// helpers n stuff
void GameManager::setDisplay(const std::string& text) { displayText=text; }
void GameManager::appendDisplay(const std::string& text) {
  if (!text.empty()) displayText+="\n\n"+text;
}

int GameManager::countCollectedClues() const {
  int n=0;
  for (const Clue* c:allClues) if (c->isCollected()) n++;
  return n;
}

void GameManager::checkUnlocks() {
  if (!campusMap) return;
  auto tryUnlock=[&](const std::string& locName, const std::string& clueName, const std::string& msg) {
    Location* loc=campusMap->getLocationByName(locName);
    if (!loc || !loc->getIsLocked()) return;
    for (const Clue* c:allClues)
      if (c->getName()==clueName && c->isCollected()) {
        loc->unlock();
        appendDisplay(msg);
        return;
      }
  };
  tryUnlock("Computer Lab B","Lab B Keypad Code","[Lab B is now unlocked!]");
  tryUnlock("Cafeteria","Cafeteria Shutter Code","[Cafeteria is now unlocked! Midnight snack time.]");
}

void GameManager::checkWinLose() {
  if (!player) return;
  if (timeRemaining<=0.0f || !player->isAlive())
    currentState=GameState::GAME_OVER;
}

std::string GameManager::currentBgKey() const {
  if (!campusMap || !campusMap->getCurrentLocation()) return "bg_menu";
  const std::string& name=campusMap->getCurrentLocation()->getName();
  if (name=="IBA Library") return "bg_library";
  if (name=="Classroom 204") return "bg_classroom";
  if (name=="Computer Lab A") return "bg_lab_a";
  if (name=="Computer Lab B") return "bg_lab_b";
  if (name=="Cafeteria") return "bg_cafeteria";
  return "bg_menu";
}

// main loop
void GameManager::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    while (auto event=window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
    }
    float dt=clock.restart().asSeconds();
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) lastClickedBtn=-1;

    if (currentState==GameState::PLAYING) {
      timeRemaining-=dt;
      checkWinLose();
    }

    window.clear(sf::Color(15,15,25));
    try {
      if(currentState==GameState::MAIN_MENU) drawMainMenu();
      else if(currentState==GameState::PLAYING) drawGame();
      else if(currentState==GameState::GAME_OVER) drawGameOver();
      else if(currentState==GameState::WIN) drawWin();
    } catch (const std::exception& e) {
      std::cerr<<"[GameManager] Draw error: "<<e.what()<<"\n";
      setDisplay("An internal error occurred. Check the console.");
    }
    window.display();
  }
}

// ui functions
void GameManager::drawBackground(const std::string& assetKey, sf::Color fallback) {
  if (assets.has(assetKey)) {
    const sf::Texture& tex=assets.getTexture(assetKey);
    sf::Sprite sprite(tex);
    sf::Vector2u texSize=tex.getSize();
    float scaleX=960.f/(float)texSize.x;
    float scaleY=680.f/(float)texSize.y;
    sprite.setScale({scaleX,scaleY});
    window.draw(sprite);
  } else {
    sf::RectangleShape bg({960.f,680.f});
    bg.setFillColor(fallback);
    window.draw(bg);
  }
}

void GameManager::drawIcon(const std::string& assetKey, float x, float y, float size) {
  if (!assets.has(assetKey)) return;
  const sf::Texture& tex=assets.getTexture(assetKey);
  sf::Sprite icon(tex);
  sf::Vector2u texSize=tex.getSize();
  float scale=size/(float)std::max(texSize.x,texSize.y);
  icon.setScale({scale,scale});
  icon.setPosition({x,y});
  window.draw(icon);
}

void GameManager::drawPanel(float x, float y, float w, float h, sf::Color fill, sf::Color outline) {
  sf::RectangleShape rect({w,h});
  rect.setPosition({x,y});
  rect.setFillColor(fill);
  rect.setOutlineColor(outline);
  rect.setOutlineThickness(2.f);
  window.draw(rect);
}

void GameManager::drawLabel(const std::string& str, unsigned int size, float x, float y, sf::Color col, sf::Text::Style style) {
  sf::Text t(font,str,size);
  t.setFillColor(col);
  t.setStyle(style);
  t.setPosition({x,y});
  window.draw(t);
}

void GameManager::drawCentred(const std::string& str, unsigned int size, float windowWidth, float y, sf::Color col, sf::Text::Style style) {
  sf::Text t(font,str,size);
  t.setFillColor(col);
  t.setStyle(style);
  float tw=t.getLocalBounds().size.x;
  t.setPosition({(windowWidth-tw)/2.f,y});
  window.draw(t);
}

bool GameManager::button(const std::string& label, float x, float y, float w, float h, int id, sf::Color col) {
  sf::Vector2i mouse=sf::Mouse::getPosition(window);
  bool hovered=(mouse.x>=x && mouse.x<=x+w && mouse.y>=y && mouse.y<=y+h);

  sf::Color drawCol=hovered?sf::Color(std::min(255,(int)col.r+45),std::min(255,(int)col.g+45),std::min(255,(int)col.b+45)):col;
  drawPanel(x,y,w,h,drawCol,sf::Color(160,160,220));

  sf::Text txt(font,label,13);
  txt.setFillColor(sf::Color::White);
  sf::FloatRect b=txt.getLocalBounds();
  txt.setPosition({x+(w-b.size.x)/2.f-b.position.x, y+(h-b.size.y)/2.f-b.position.y-2.f});
  window.draw(txt);

  bool clicked=hovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && lastClickedBtn==-1;
  if (clicked) lastClickedBtn=id;
  return clicked;
}

void GameManager::drawWrappedText(const std::string& str, float x, float y, float maxWidth, unsigned int charSize, sf::Color col) {
  sf::Text txt(font,"",charSize);
  txt.setFillColor(col);
  float lineY=y;
  float lineH=(float)charSize+4.f;
  std::string para;
  std::istringstream paraStream(str);
  while (std::getline(paraStream,para)) {
    std::istringstream wordStream(para);
    std::string word, line;
    while (wordStream>>word) {
      std::string test=line.empty()?word:line+" "+word;
      txt.setString(test);
      if (txt.getLocalBounds().size.x>maxWidth && !line.empty()) {
        txt.setString(line);
        txt.setPosition({x,lineY});
        window.draw(txt);
        lineY+=lineH;
        line=word;
      } else { line=test; }
    }
    if (!line.empty()) {
      txt.setString(line);
      txt.setPosition({x,lineY});
      window.draw(txt);
      lineY+=lineH;
    }
    lineY+=4.f;
  }
}

// screens
void GameManager::drawMainMenu() {
  drawBackground("bg_menu",sf::Color(10,10,20));
  sf::RectangleShape overlay({960.f,680.f});
  overlay.setFillColor(sf::Color(0,0,0,150));
  window.draw(overlay);

  if (assets.has("logo")) {
    const sf::Texture& logoTex=assets.getTexture("logo");
    sf::Sprite logo(logoTex);
    sf::Vector2u s=logoTex.getSize();
    float scale=std::min(400.f/s.x,120.f/s.y);
    logo.setScale({scale,scale});
    logo.setPosition({(960.f-s.x*scale)/2.f,30.f});
    window.draw(logo);
  }

  drawCentred("TRAPPED IN IBA",42,960,100,sf::Color(180,130,255),sf::Text::Style::Bold);
  drawCentred("After Hours",22,960,155,sf::Color(120,180,255));
  drawWrappedText("You fell asleep in the library. The campus is locked.\nFind the clues. Escape before morning classes begin.",200,215,560,14,sf::Color(200,200,210));

  drawPanel(230,268,500,108,sf::Color(10,15,30,200),sf::Color(80,80,120));
  drawWrappedText("HOW TO PLAY\nExamine objects to find 4 clues.\nMoving costs energy - eat in the cafeteria to refill.\nCollect all clues, then escape.\nYou have 10 minutes!",242,276,478,12,sf::Color(200,200,230));

  if (button("PLAY",380,400,200,50,100,sf::Color(50,110,60))) {
    try { initializeWorld(); currentState=GameState::PLAYING; }
    catch (...) { setDisplay("Failed to start game"); }
  }
  if (button("QUIT",380,462,200,50,101,sf::Color(120,50,50))) window.close();

  drawCentred("Nisha Fatima (32480) | Shanzey Shaikh (32490) | OOP - IBA Karachi",11,960,645,sf::Color(160,160,180));
}

void GameManager::drawGame() {
  if (!campusMap || !player) return;
  drawBackground(currentBgKey(),sf::Color(18,18,35));

  sf::RectangleShape storyOverlay({600.f,330.f});
  storyOverlay.setFillColor(sf::Color(0,0,0,170));
  storyOverlay.setPosition({10.f,10.f});
  window.draw(storyOverlay);

  drawPanel(10,10,590,320,sf::Color(18,18,35,180),sf::Color(70,70,140));
  Location* here=campusMap->getCurrentLocation();
  drawLabel(here?here->getName():"???",16,18,14,sf::Color(255,215,80),sf::Text::Style::Bold);
  drawWrappedText(displayText,18,40,570,13,sf::Color(215,215,245));

  // timer logic
  drawPanel(610,10,340,215,sf::Color(18,18,35,210),sf::Color(70,70,140));
  int mins=(int)(timeRemaining/60.f);
  int secs=(int)timeRemaining%60;
  std::ostringstream ts;
  ts<<"Time Left: "<<mins<<":"<<std::setw(2)<<std::setfill('0')<<secs;
  drawLabel(ts.str(),15,620,18,timeRemaining<60.f?sf::Color::Red:sf::Color(100,230,100));

  // energy bar
  float pct=player->getEnergy()/100.f;
  drawPanel(700,48,200.f,14,sf::Color(40,40,40),sf::Color(80,80,80));
  sf::Color barCol=pct<0.25f?sf::Color::Red:pct<0.5f?sf::Color(255,165,0):sf::Color(50,200,80);
  if (pct>0.f) drawPanel(700,48,200.f*pct,14,barCol,barCol);

  drawLabel("Clues Found ("+std::to_string(countCollectedClues())+"/"+std::to_string(allClues.size())+"):",13,620,74,sf::Color(180,180,255),sf::Text::Style::Bold);
  float clueY=97.f;
  for (const Clue* c:allClues) {
    drawLabel(c->isCollected()?"[x] "+c->getName():"[ ] ???",12,625,clueY,c->isCollected()?sf::Color(80,220,80):sf::Color(100,100,120));
    clueY+=22.f;
  }

  // action buttons
  drawPanel(10,340,940,330,sf::Color(14,14,28,220),sf::Color(60,60,120));
  const auto& choices=choiceManager.getChoices();
  float btnW=455.f, btnH=32.f, gap=5.f, btnY=368.f;
  int col=0;
  for (int i=0; i<(int)choices.size() && btnY<655.f; i++) {
    float bx=18.f+col*(btnW+12.f);
    sf::Color btnCol=sf::Color(50,80,50);
    const std::string& lbl=choices[i].label;
    if (lbl.find("Go to")!=std::string::npos) btnCol=sf::Color(50,60,120);
    if (lbl.find("Go Back")!=std::string::npos) btnCol=sf::Color(80,60,30);
    if (lbl.find("ESCAPE")!=std::string::npos) btnCol=sf::Color(160,90,0);

    if (button(lbl,bx,btnY,btnW,btnH,i,btnCol)) {
      std::string result=choiceManager.executeChoice(i);
      if (!result.empty()) setDisplay(result);
    }
    col=1-col;
    if (col==0) btnY+=btnH+gap;
  }
}

void GameManager::drawGameOver() {
  drawBackground("bg_gameover",sf::Color(30,0,0));
  drawCentred("GAME OVER",48,960,150,sf::Color::Red,sf::Text::Style::Bold);
  std::string reason=(timeRemaining<=0.f)?"The sun rose. You were found wandering.":"You ran out of energy. A guard found you.";
  drawWrappedText(reason,250,248,460,16,sf::Color(220,180,180));

  if (button("TRY AGAIN",330,410,180,50,200,sf::Color(100,40,40))) {
    initializeWorld(); currentState=GameState::PLAYING;
  }
  if (button("MAIN MENU",530,410,180,50,201,sf::Color(60,40,80))) {
    teardownWorld(); currentState=GameState::MAIN_MENU;
  }
}

void GameManager::drawWin() {
  drawBackground("bg_win",sf::Color(0,20,0));
  drawCentred("YOU ESCAPED!",48,960,130,sf::Color(80,255,80),sf::Text::Style::Bold);
  std::ostringstream ss;
  ss<<"You slipped out through the staff exit. Nice work.\nTime taken: "<<(int)((600.f-timeRemaining)/60)<<" min\nEnergy left: "<<(int)player->getEnergy()<<"%";
  drawWrappedText(ss.str(),230,230,500,15,sf::Color(180,255,180));

  if (button("PLAY AGAIN",330,490,180,50,300,sf::Color(40,100,40))) {
    initializeWorld(); currentState=GameState::PLAYING;
  }
  if (button("MAIN MENU",530,490,180,50,301,sf::Color(40,60,100))) {
    teardownWorld(); currentState=GameState::MAIN_MENU;
  }
}