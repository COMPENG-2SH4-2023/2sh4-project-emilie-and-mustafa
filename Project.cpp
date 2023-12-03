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
    foodPtr = new Food(); // pointer to food class
    playerPtr = new Player(gameMechsPtr, foodPtr); // pointer to player class

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

    // Game winning condition: score = 10
    if(gameMechsPtr->getScore() == 10){
        gameMechsPtr->setExitTrue();
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPos current; // current position
    objPos tempBody; // position of an element from the player list
    objPos foodPos; // food position
    objPosArrayList* playerBody;
    char playerSymbol, foodSymbol;
    int itemFound;

    foodPtr->getFoodPos(foodPos); 
    playerBody = playerPtr->getPlayerPos();

    // loops through each position of the game board to draw it
    for(int i = 0; i < gameMechsPtr->getBoardSizeY(); i++){
        for(int j = 0; j < gameMechsPtr->getBoardSizeX(); j++){

            current.setObjPos(j,i,' '); // current position on the board

            // checks if the food is equal to the current position and gets the symbol
            foodSymbol = foodPos.getSymbolIfPosEqual(&current);

            // sets boarder if at edge of row or column
            if(i == 0 || i == gameMechsPtr->getBoardSizeY()-1 || j == 0 || j == gameMechsPtr->getBoardSizeX()-1){
                MacUILib_printf("#");
            } else if (foodSymbol == 'o'){ // prints player symbol if at its coordinates
                MacUILib_printf("%c", foodSymbol);
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
    MacUILib_printf("\n\nGet 10 points to win the game!");
    MacUILib_printf("\nIf you collide with yourself, you lose!");   
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

    //deallocations
    delete playerPtr;
    delete foodPtr;
    delete gameMechsPtr;

    
}