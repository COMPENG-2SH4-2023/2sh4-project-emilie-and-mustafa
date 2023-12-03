#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>
#include "GameMechs.h"

using namespace std;

class Food {

    private:
        objPos foodPos;
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOffList);
        void getFoodPos(objPos &returnPos);

        char getFoodSymbol();


};

#endif