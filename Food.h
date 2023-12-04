#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>
#include "GameMechs.h"
#include "MacUILib.h"

using namespace std;

class Food {

    private:
        objPos foodPos;
        objPos bodyPos;
        GameMechs* mainGameMechsRef;
        objPosArrayList* foodBucket;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOffList);
        void getFoodPos(objPos &returnPos);
        objPosArrayList* getFoodBucket();

        char getFoodSymbol();


};

#endif