#include "Food.h"


Food::Food(GameMechs* thisGMRef){
    srand((time(0)));
    mainGameMechsRef = thisGMRef; // reference to game mechs class
    int randX, randY;
    char symbol;
    bool isValidPosition;

    foodBucket = new objPosArrayList();

    for(int i=0; i<5; i++)
    {
        symbol = 'o';

        do 
        {
            // gets random coordinates for x and y, sets the flag to true
            randX = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 3);
            randY = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 3);
            isValidPosition = true;

            // Check for coordinates in the foodBucket list
            for (int j = 0; j < foodBucket->getSize(); j++) {
                foodBucket->getElement(foodPos, j);

                // if the coordinates match any in the list, the flag is set to false and new coordinate will be made
                // if the coordinates are unique, the flag stays set to true and breaks out of the loop
                if (randX == foodPos.x && randY == foodPos.y) {
                    isValidPosition = false;
                    break;
                }
            }
        } while (!isValidPosition);

        // set special symbols for 2 elements in food bucket
        if (i%2 != 0)
        {
            symbol = '$';
        }

        // sets the newly found coordinates to food
        foodPos.setObjPos(randX, randY, symbol);
        foodBucket->insertHead(foodPos);
    }

}

Food::~Food(){
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOffList){
    srand((time(0)));

    int randX, randY;
    char symbol;
    bool isValidPosition = false; // flag to check if the food coordinates match any in the player list or already in the foodBucket list

    // generate new food bucket list
    for(int i =0; i<foodBucket->getSize(); i++)
    {
        symbol = 'o';
        foodBucket->removeTail();

        do 
        {
            // gets random coordinates for x and y, sets the flag to true
            randX = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 3);
            randY = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 3);
            isValidPosition = true;

            // iterates through the player and existing foodbucket list to check for matching coordinates
            for (int j = 0; j < blockOffList->getSize(); j++) 
            {
                blockOffList->getElement(bodyPos, j);
                // if the coordinates match any in the list, the flag is set to false and new coordinate will be made
                // if the coordinates are unique, the flag stays set to true and breaks out of the loop
                if (randX == bodyPos.x && randY == bodyPos.y) 
                {
                    isValidPosition = false;
                    break;
                }
            }

            // Check for coordinates in the foodBucket list
            for (int j = 0; j < foodBucket->getSize(); j++) 
            {
                foodBucket->getElement(foodPos, j);
                // if the coordinates match any in the list, the flag is set to false and new coordinate will be made
                // if the coordinates are unique, the flag stays set to true and breaks out of the loop
                if (randX == foodPos.x && randY == foodPos.y) 
                {
                    isValidPosition = false;
                    break;
                }
            }

        } while (!isValidPosition);

        // set special symbols for 2 elements in food bucket
        if (i%2 != 0)
        {
            symbol = '$';
        }

        // sets the newly found coordinates to food
        foodPos.setObjPos(randX, randY, symbol);
        foodBucket->insertHead(foodPos);
    }
}


objPosArrayList* Food::getFoodBucket(){
    return foodBucket;
}

char Food::getFoodSymbol(){
    objPos tempPos;
    foodBucket->getElement(tempPos, 0);
    return tempPos.getSymbol();
}