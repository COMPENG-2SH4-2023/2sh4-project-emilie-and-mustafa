#include <iostream>
#include <stdlib.h>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Food.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechsPtr;
Food* foodPtr;
Player* playerPtr;
objPosArrayList* foodList;



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

    gameMechsPtr = new GameMechs(); // pointer to gameMechs class
    foodPtr = new Food(gameMechsPtr); // pointer to food class
    playerPtr = new Player(gameMechsPtr, foodPtr); // pointer to player class
    foodList = new objPosArrayList();

}

void GetInput(void)
{
   if(MacUILib_hasChar() != 0){
        gameMechsPtr->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    // gets keyboard input
    if(gameMechsPtr->getInput() != '\0'){
        // updates the player direction based on the input
        playerPtr->updatePlayerDir();
        // checks for exit key to end game
        switch(gameMechsPtr->getInput()){                      
            case 27:  // escape key to exit
                gameMechsPtr->setExitTrue(); // sets exit flag to true
                break;
            default:
                break;
        }
        gameMechsPtr->clearInput(); // clears input while it waits for a new one
    }
    playerPtr->movePlayer(); // moves player based on player direction

    // Game winning condition: score = 50
    if(gameMechsPtr->getScore() >= 50){
        gameMechsPtr->setExitTrue();
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPos current; // current position
    objPos tempBody; // position of an element from the player list
    objPos foodPos; // food position
    char playerSymbol, foodSymbol;
    int itemFound;

    objPosArrayList* playerBody;
    

    playerBody = playerPtr->getPlayerPos();
    foodPtr->getFoodBucket(*foodList);
    

    // loops through each position of the game board to draw it
    for(int i = 0; i < gameMechsPtr->getBoardSizeY(); i++){
        for(int j = 0; j < gameMechsPtr->getBoardSizeX(); j++){
            
            current.setObjPos(j,i,' '); // current position on the board

            // sets boarder if at edge of row or column
            if(i == 0 || i == gameMechsPtr->getBoardSizeY()-1 || j == 0 || j == gameMechsPtr->getBoardSizeX()-1){
                MacUILib_printf("#");
            } else {
                // iterates thorugh player list and gets symbol if coordinates match
                itemFound = 0;
                for(int k =0; k<playerBody->getSize(); k++){
                    playerBody->getElement(tempBody, k);
                    if(tempBody.isPosEqual(&current)){
                        MacUILib_printf("%c", tempBody.getSymbol());
                        itemFound = 1;
                        break;
                    }
                }

                for(int k =0; k<foodList->getSize(); k++){
                    foodList->getElement(foodPos, k);
                    if(foodPos.isPosEqual(&current)){
                        MacUILib_printf("%c", foodPos.getSymbol());
                        itemFound = 1;
                        break;
                    }
                }
                
                //otherwise prints a whitespace
                if(!itemFound){
                    MacUILib_printf(" ");
                }
            }
        }

        MacUILib_printf("\n");
    } 
    

    // in game messages
    MacUILib_printf("\n\nYour Score: %d", gameMechsPtr->getScore());
    MacUILib_printf("\n\nGet 50 points to win the game!");
    MacUILib_printf("\n\n'o' foods are worth 1 point\t'$' foods are worth 10 points'");
    MacUILib_printf("\n\nIf you collide with yourself, you lose!");   
    MacUILib_printf("\n\nPress escape to exit the game.");

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    // game end messages
    if(gameMechsPtr->getLoseFlagStatus()){ // if the lose flag is raised
        MacUILib_printf("You collided with yourself.\nSorry, You Lose!!");
        MacUILib_printf("\n\nYour Final Score: %d", gameMechsPtr->getScore()); 
    } else{ // if the lose flag is not raised, the player either won or exited the game
        if(gameMechsPtr->getScore() >= 50){
            MacUILib_printf("Congrats, You Won!");
            MacUILib_printf("\n\nYour Final Score: %d\n\n", gameMechsPtr->getScore());  
        } else {
            MacUILib_printf("Aw, leaving so soon?");
            MacUILib_printf("\nYou exited the game :(");
            MacUILib_printf("\n\nYour Final Score: %d\n\n", gameMechsPtr->getScore());  
        }
    }

    MacUILib_uninit();

    //deallocations
    delete playerPtr;
    delete foodPtr;
    delete gameMechsPtr;

    
}