#include "stdafx.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}


void RenderCharacter()
{

}


void Character::Update(Level& level)
{
	// Set agents cell x & y tile values & point values
	int cellSize = level.getCellSize();
	setCellX(getX() / level.getCellSize());
	setCellY(getY() / level.getCellSize());
	getAgentPointLocation() = Point(getCellX(), getCellY());


	// ROTATE AGENT /////
	if (incrementalRotating)
	{

		if (rotation == 360 - rotationSpeed || rotation == 360)
			rotation = 0;
		if (rotation == -90 - rotationSpeed || rotation == -90)
			rotation = 270;
		// Perform agent rotation based on player input
		if (rotation != targetRotation)
		{
			// Edge case
			if (rotation == 270 && targetRotation == 0)
				targetRotation = 360;
			if (rotation == 0 && targetRotation == 270)
				targetRotation = -90;

			if (rotation < targetRotation)
				rotation += rotationSpeed;
			else if (rotation > targetRotation)
				rotation -= rotationSpeed;
		}
	}


	//Set chunk and cell positions for the agent
	chunkPos.x = (getX() / cellSize) / level.getChunkSize();
	chunkPos.y = (getY() / cellSize) / level.getChunkSize();

	int x = getX() / cellSize;
	int y = getY() / cellSize;
	cellPos.x = x - (chunkPos.x * level.getChunkSize());
	cellPos.y = y - (chunkPos.y * level.getChunkSize());

	if (cellPos.x < 0)
	{
		cellPos.x += level.getChunkSize();
		chunkPos.x -= 1;
	}
	if (cellPos.y < 0)
	{
		cellPos.y += level.getChunkSize();
		chunkPos.y -= 1;
	}

	//std::cout << chunkPos.x << " " << chunkPos.y << " | " << cellPos.x << " " << cellPos.y << std::endl;

	//level.World[chunkPos.x][chunkPos.y].tiles[cellPos.x][cellPos.y]->cellLightness = 255;
	// Change speed when the player enters water
	if (level.World[chunkPos.x][chunkPos.y]->tiles[cellPos.x][cellPos.y]->isWater)
		setSpeed(1);
	else
		setSpeed(5);


}