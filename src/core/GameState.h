#pragma once
//tracks which screen shows atm
//GameManager reads this every frame in main loop to decide what to draw
enum class GameState {
    MAIN_MENU,   //start screen-shows title, PLAY and QUIT buttons
    PLAYING,     //player actively exploring rooms and finding clues
    GAME_OVER,   //player ran out of time or energy hit zero
    WIN          //player collected all clues and used escape option
};