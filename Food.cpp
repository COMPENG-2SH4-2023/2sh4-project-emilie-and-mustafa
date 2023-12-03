#include "Food.h"


Food::Food(GameMechs* thisGMRef){
    srand((time(0)));
    mainGameMechsRef = thisGMRef; // reference to game mechs class
    int randX, randY;
    char symbol = 'o';

    // randomly generates x and y coordinates 
    // until it gets a set that is not equal to the starting position of the player (14,7)
    do {
        randX = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 3); 
        randY = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 3);
    }
    while(randX == 14 || randY == 7);

    foodPos.setObjPos(randX, randY, symbol);
}

Food::~Food(){
    
}

void Food::generateFood(objPosArrayList* blockOffList){
    srand((time(0)));

    int randX, randY;
    char symbol = 'o';
    objPos bodyPos;
    bool isValidPosition = false; // flag to check if the food coordinates match any in the player list  

    do {
        // gets random coordinates for x and y, sets the flag to true
        randX = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 3);
        randY = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 3);
        isValidPosition = true;

        // iterates through the player list
        for (int j = 0; j < blockOffList->getSize(); j++) {
            blockOffList->getElement(bodyPos, j);
            // if the coordinates match any in the list, the flag is set to false and new coordinate will be made
            // if the coordinates are unique, the flag stays set to true and breaks out of the loop
            if (randX == bodyPos.x && randY == bodyPos.y) {
                isValidPosition = false;
                break;
            }
        }
    } while (!isValidPosition);

    // sets the newly found coordinates to food
    foodPos.setObjPos(randX, randY, symbol);
}

void Food::getFoodPos(objPos &returnPos){
    returnPos = foodPos;
}

char Food::getFoodSymbol(){
    return foodPos.getSymbol();
}