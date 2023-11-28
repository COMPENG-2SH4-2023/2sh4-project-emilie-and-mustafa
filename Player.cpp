#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos initial;
    initial.setObjPos(14,7,'*');
    playerPosList = new objPosArrayList[0];
    playerPosList->insertHead(initial);

    // more actions to be included
}


Player::~Player()
{
    delete mainGameMechsRef;
    delete playerPtr;
    delete playerPosList;
}

void Player::getPlayerPos(objPosArrayList &returnPos)
{
    returnPos = *playerPosList;
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

    objPos headPos;
    playerPosList->getHeadElement(headPos);

    if(myDir == UP){
        headPos.y--;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        if(headPos.y == 0){
            headPos.y = mainGameMechsRef->getBoardSizeY()-2;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    } else if (myDir == DOWN){
        headPos.y++;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        if(headPos.y > mainGameMechsRef->getBoardSizeY()-2){
            headPos.y = 1;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    } else if (myDir == LEFT){
        headPos.x--;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        if(headPos.x == 0){
            headPos.x = mainGameMechsRef->getBoardSizeX()-2;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    } else if (myDir == RIGHT){
        headPos.x++;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        if(headPos.x == mainGameMechsRef->getBoardSizeX()-1){
            headPos.x = 1;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    }
}

char Player::getPlayerSymbol(){

    objPos headPos;
    playerPosList->getHeadElement(headPos);
    return headPos.getSymbol();
}

