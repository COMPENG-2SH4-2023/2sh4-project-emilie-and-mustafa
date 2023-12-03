#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>
#include "GameMechs.h"

using namespace std;

class Food {

    private:
        objPos foodPos;

    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* blockOffList);
        void getFoodPos(objPos &returnPos);

        char getFoodSymbol();


};

#endif