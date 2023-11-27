#include "Food.h"
#include "GameMechs.h"
#include <ctime>


Food::Food(){
    srand(static_cast<unsigned>(time(0)));

    int randX, randY;
    char randSymbol;

    randSymbol = 'A' + rand() % 26;
    randX = 1+ rand() % (gameMechsPtr->getBoardSizeX() - 3); 
    randY = 1+ rand() % (gameMechsPtr->getBoardSizeY() - 3);

    foodPos.setObjPos(randX, randY, randSymbol);
}

Food::~Food(){
    delete foodPosPtr;
}

void Food::generateFood(objPos blockOff){
    srand(static_cast<unsigned>(time(0)));

    int randX, randY;
    char randSymbol;

    randSymbol = 'A' + rand() % 26;

    do {
        randX = 1 + rand() % (gameMechsPtr->getBoardSizeX() - 2); 
        randY = 1 + rand() % (gameMechsPtr->getBoardSizeY() - 2);
    }
    while(randX == blockOff.x || randY == blockOff.y);

    foodPos.setObjPos(randX, randY, randSymbol);
}

void Food::getFoodPos(objPos &returnPos){
    returnPos = foodPos;
}

char Food::getFoodSymbol(){
    return foodPos.getSymbol();
}