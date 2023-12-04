#include "objPosArrayList.h"
#include <stdexcept>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[sizeArray];

    for(int i = 0; i < ARRAY_MAX_CAP; i++){
		aList[i].x = 0;
        aList[i].y = 0;
        aList[i].symbol = 0;
    }

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList >= sizeArray){
        throw std::out_of_range("Full list h.");
    } else {
        for(int i = sizeList; i > 0; i--){
            aList[i] = aList[i-1];
        }

        aList[0] = thisPos;

        sizeList++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList >= sizeArray){
        throw std::out_of_range("Full list t.");
    } else {
        aList[sizeList++] = thisPos;
    }
        
    
}

void objPosArrayList::removeHead()
{
    
    if(sizeList == 0){
        throw std::out_of_range("Empty list.");
    } else {
        for(int i = 0; i < sizeList-1; i++){
            aList[i] = aList[i+1];
        }

        sizeList--;
    }
    
}

void objPosArrayList::removeTail()
{
    if(sizeList == 0){
        throw std::out_of_range("Empty list.");
    } else {
        sizeList--;      
    }
    
    
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(sizeList == 0){
        throw std::out_of_range("Empty list.");
    } else {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList == 0) {
		throw std::out_of_range("Empty list.");
	} else {
        returnPos = aList[sizeList-1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index < 0 || index >= sizeList) {
		throw std::out_of_range("Invalid index.");
	} else if (sizeList == 0){
        throw std::out_of_range("Empty list.");
    } else {
        returnPos = aList[index];
    }
}