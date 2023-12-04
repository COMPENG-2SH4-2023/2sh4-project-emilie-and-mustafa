#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    mainGameMechsRef = thisGMRef; // reference to game mechs class
    myFoodRef = foodRef; // reference to food class
    myDir = STOP; // initial direction is STOP

    //sets initial head of snake to coordinates in the middle of the board
    objPos head;
    head.setObjPos(14,7,'*');
    playerPosList = new objPosArrayList(); // instance of array for snake body
    playerPosList->insertHead(head); // inserts new head objPos

}

// deallocates player list
Player::~Player(){
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // sets player direction based on input
    switch(mainGameMechsRef->getInput()){
        case 'w': // up
            if (!(myDir == UP || myDir == DOWN)){ // checks that the player is not already going up or down
                myDir = UP;
            }
            break;
        case 'a': // left
            if (!(myDir == LEFT || myDir == RIGHT)){ // checks that the player is not already going right or left
                myDir = LEFT;
            }
            break;
        case 's': // down
            if (!(myDir == DOWN || myDir == UP)){ // checks that the player is not already going up or down
                myDir = DOWN;
            }
            break;
        case 'd': // right
            if (!(myDir == RIGHT || myDir == LEFT)){ // checks that the player is not already going right or left
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }

}

void Player::movePlayer()
{

    objPos headPos;
    playerPosList->getHeadElement(headPos);

    // calculates new position player based on current direction
    switch(myDir){
        case UP:
            headPos.y--;
            if(headPos.y == 0){ // wrap around when player gets to top edge of board
                headPos.y = mainGameMechsRef->getBoardSizeY()-2;
            }
            break;
        case DOWN:
            headPos.y++;
            if(headPos.y > mainGameMechsRef->getBoardSizeY()-2){ // wrap around when player gets to bottom edge of board
                headPos.y = 1;
            }
            break;
        case LEFT:
            headPos.x--;
            if(headPos.x == 0){ // wrap around when player gets to right left of board
                headPos.x = mainGameMechsRef->getBoardSizeX()-2;
            }
            break;
        case RIGHT:
            headPos.x++;
            if(headPos.x > mainGameMechsRef->getBoardSizeX()-2){ // wrap around when player gets to right edge of board
                headPos.x = 1;
            }
            break;
        default:
            break;
    }
    
    playerPosList->insertHead(headPos);
    
    // checks if the new position is on top of a food
    // increments the score and generates a new food
    // otherwise, removes the tail
    if(checkFoodConsumption())
    {
        if(foodPos.getSymbol() == '$')
        {   
            mainGameMechsRef->incrementScore(10);
        } else {
            mainGameMechsRef->incrementScore(1);
        }
        myFoodRef->generateFood(playerPosList);
    } else {
        playerPosList->removeTail();
    }

    // checks if the player collides with itself
    // sets the exit flag and lose flag to true, ending the game immediately
    if(checkSelfCollision()){
        mainGameMechsRef->setLoseTrue();
        mainGameMechsRef->setExitTrue();
    }

    
    
}

// new current head should be inserted to the head of the list.


char Player::getPlayerSymbol(){

    objPos headPos;
    playerPosList->getHeadElement(headPos);
    return headPos.getSymbol();

}

// compares the position of the head and the food
bool Player::checkFoodConsumption(){

    objPos headPos;
    objPosArrayList* foodList;

    foodList = myFoodRef->getFoodBucket();
    playerPosList->getHeadElement(headPos);

    for(int i=0; i<foodList->getSize(); i++)
    {
        foodList->getElement(foodPos, i);
        if(headPos.isPosEqual(&foodPos))
        {
            return true;
        }
    }

    return false;
    
}

// compares the position of the head and the elements of the body
bool Player::checkSelfCollision(){
    objPos head;
    objPos body;
    playerPosList->getHeadElement(head);
    int listSize = playerPosList->getSize();
    if (listSize>4){ // can only collide with itself if has a length greater than 4
        for(int k=1; k<listSize; k++){
            playerPosList->getElement(body, k);
            if(head.isPosEqual(&body)){
                return true;
            }
        }
    }

    return false;

}