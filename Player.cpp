#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPos.setObjPos(14,7,'*');

    // more actions to be included
}


Player::~Player()
{
    delete mainGameMechsRef;
    delete playerPtr;
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos = playerPos;
}

void Player::updatePlayerDir()
{
    if(mainGameMechsRef->getInput() != '\0'){
        switch(mainGameMechsRef->getInput()){
            case 'w': // up
                if (!(myDir == UP || myDir == DOWN)) {
                    myDir = UP;
                }
                break;
            case 'a': // left
                if (!(myDir == LEFT || myDir == RIGHT)) {
                    myDir = LEFT;
                }
                break;
            case 's': // down
                if (!(myDir == DOWN || myDir == UP)) {
                    myDir = DOWN;
                }
                break;
            case 'd': // right
                if (!(myDir == RIGHT || myDir == LEFT)) {
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }
    }


}

void Player::movePlayer()
{
    if(myDir == UP){
        (playerPos.y)--;
        if(playerPos.y == 0){
            playerPos.y = mainGameMechsRef->getBoardSizeY()-2;
        }
    } else if (myDir == DOWN){
        (playerPos.y)++;
        if(playerPos.y > mainGameMechsRef->getBoardSizeY()-2){
            playerPos.y = 1;
        }
    } else if (myDir == LEFT){
        (playerPos.x)--;
        if(playerPos.x == 0){
            playerPos.x = mainGameMechsRef->getBoardSizeX()-2;
        }
    } else if (myDir == RIGHT){
        (playerPos.x)++;
        if(playerPos.x == mainGameMechsRef->getBoardSizeX()-1){
            playerPos.x = 1;
        }
    }
}

char Player::getPlayerSymbol(){
    return playerPos.getSymbol();
}

