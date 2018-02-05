#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
}

// 
Cell::Cell(int x, int y)
{
	setX(x);
	setY(y);
}

Cell::~Cell(){
}

//TO modify these values, the other values in classes gameSettings.loadGameFromSave and NetWorkManager.MapNetworkUpdate need to be modified
json Cell::getCellData()
{	
	json cellData;
	cellData["X"] = x;
	cellData["Y"] = y;
	if(isWoodFence)
		cellData["Fence"] = isWoodFence;
	if(isDirt)
		cellData["Dirt"] = isDirt;
	if(isGrass)
		cellData["Grass"] = isGrass;
	if (isWater)
		cellData["Water"] = isWater;
	if (isSand)
		cellData["Sand"] = isSand;
	if(isWood)
		cellData["Wood"] = isWood;
	if(isRock)
		cellData["Stone"] = isRock;
	if(isStoneWall)
		cellData["StoneWall"] = isStoneWall;
	if(isWheat)
		cellData["Wheat"] = isWheat;
	if(seedsStage >= 0 && seedsStage< 10)
		cellData["PlantStage"] = seedsStage;
	
	return cellData;
}

