#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos initial;
    initial.setObjPos(14,7,'*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(initial);

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef ->getBoardSizeX() / 2, mainGameMechsRef ->getBoardSizeY() / 2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);


    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    delete mainGameMechsRef;
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
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
        if(headPos.y == 0){
            headPos.y = mainGameMechsRef->getBoardSizeY()-2;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    } else if (myDir == DOWN){
        headPos.y++;
        if(headPos.y > mainGameMechsRef->getBoardSizeY()-2){
            headPos.y = 1;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    } else if (myDir == LEFT){
        headPos.x--;
        if(headPos.x == 0){
            headPos.x = mainGameMechsRef->getBoardSizeX()-2;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    } else if (myDir == RIGHT){
        headPos.x++;
        if(headPos.x == mainGameMechsRef->getBoardSizeX()-1){
            headPos.x = 1;
            playerPosList->insertHead(headPos);
            playerPosList->removeTail();
        }
    }
    // insert head
    playerPosList->insertHead(headPos);

    //remove tail
    playerPosList->removeTail();


}

// new current head should be inserted to the head of the list.


char Player::getPlayerSymbol(){

    objPos headPos;
    playerPosList->getHeadElement(headPos);
    return headPos.getSymbol();

    playerPosList -> removeTail();
}

