#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state
        

        Player(GameMechs* thisGMRef, Food* foodRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();

        char getPlayerSymbol();

        bool checkFoodConsumption();
        bool checkSelfCollision();

    private:
        //objPos playerPos;   // Upgrade this in iteration 3.       
        
        objPosArrayList* playerPosList; // iteration 3 upgrade
        enum Dir myDir;
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* myFoodRef;
        
        objPos foodPos;
        objPos headPos;
};

#endif