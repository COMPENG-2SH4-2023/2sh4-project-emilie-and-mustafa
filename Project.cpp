#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include <stdlib.h>
#include <time.h>
#include "GameMechs.h"
#include "Food.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechsPtr;
Food* foodPosPtr;
Player* playerPtr;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(!gameMechsPtr->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gameMechsPtr = new GameMechs();
    foodPosPtr = new Food();
    playerPtr = new Player(gameMechsPtr);


}

void GetInput(void)
{
   if(MacUILib_hasChar() != 0){
        gameMechsPtr->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{

    objPos blockOffPos;

    if(gameMechsPtr->getInput() != '\0'){
        playerPtr->updatePlayerDir();
        switch(gameMechsPtr->getInput()){                      
            case 27:  // escape key to exit
                gameMechsPtr->setExitTrue();
                break;
            case 32: // space bar to increase score
                gameMechsPtr->incrementScore();
                break;
            case 8: // backspaace key to lose the game
                gameMechsPtr->setLoseFlag();
                gameMechsPtr->setExitTrue();
                break;
            case 9: // tab key to generate a new food
                foodPosPtr->generateFood(blockOffPos);
            default:
                break;
        }
        gameMechsPtr->setInput(0);
    }
    playerPtr->movePlayer();

    if(gameMechsPtr->getScore() == 10){
        gameMechsPtr->setExitTrue();
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPos playerPos;
    objPos foodPos;

    playerPtr->getPlayerPos(playerPos);
    foodPosPtr->getFoodPos(foodPos);

    for(int i = 0; i < gameMechsPtr->getBoardSizeY(); i++){
        for(int j = 0; j < gameMechsPtr->getBoardSizeX(); j++){
            if(i == 0 || i == gameMechsPtr->getBoardSizeY()-1 || j == 0 || j == gameMechsPtr->getBoardSizeX()-1){
                MacUILib_printf("#");
            } else if(playerPos.x == j && playerPos.y == i){
                MacUILib_printf("%c", playerPos.symbol);
            } else if (foodPos.x == j && foodPos.y == i){
                MacUILib_printf("%c", foodPos.symbol);
            } else {
                MacUILib_printf(" ");
            }
            

            
        }
        MacUILib_printf("\n");
    } 

    MacUILib_printf("\n\nYour Score (press space to increment): %d", gameMechsPtr->getScore());
    MacUILib_printf("\nGet 10 points to win the game!");   
    MacUILib_printf("\n\nPress tab generate a new food");
    MacUILib_printf("\n\nPress backspace to lose the game");
    
    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    

    if(gameMechsPtr->getLoseFlagStatus()){
        MacUILib_printf("Sorry, You Lose!!");
        MacUILib_printf("\n\nYour Final Score: %d", gameMechsPtr->getScore()); 
    } else{
        if(gameMechsPtr->getScore() == 10){
            MacUILib_printf("Congrats, You Won!");
            MacUILib_printf("\n\nYour Final Score: %d\n\n", gameMechsPtr->getScore());  
        } else {
            MacUILib_printf("Aw, leaving so soon?");
            MacUILib_printf("\nYou exited the game :(");
            MacUILib_printf("\n\nYour Final Score: %d\n\n", gameMechsPtr->getScore());  
        }
    }

    MacUILib_uninit();

    delete gameMechsPtr;
    delete foodPosPtr;
    delete playerPtr;
    

    
}