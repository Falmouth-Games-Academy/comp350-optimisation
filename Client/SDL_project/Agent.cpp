#include "stdafx.h"
#include "Agent.h"


Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::Update(Level& level)
{
	// Set agents cell x & y tile values & point values
	int cellSize = level.getCellSize();
	setCellX(getX() / level.getCellSize());
	setCellY(getY() / level.getCellSize());
	getAgentPointLocation() = Point(getCellX(), getCellY());

	// Decrease/Increase stats over time
	tiredness = tiredness + tirednessDecayRate;
	hunger = hunger - hungerDecayRate;
	toiletLevel = toiletLevel + toiletDecayRate;
	

	// ROTATE AGENT /////
	if (agentCanRotate)
	{
		if (getRotation() == 360 - getRotationSpeed() || getRotation() == 360)
			setRotation(0);
		if (getRotation() == -90 - getRotationSpeed() || getRotation() == -90)
			setRotation(270);
		// Perform agent rotation based on player input
		if (getRotation() != getTargetRotation())
		{
			// Edge case
			if (getRotation() == 270 && getTargetRotation() == 0)
				setTargetRotation(360);
			if (getRotation() == 0 && getTargetRotation() == 270)
				setTargetRotation(-90);

			if (getRotation() < getTargetRotation())
				setRotation(getRotation() + getRotationSpeed());
			else if (getRotation() > getTargetRotation())
				setRotation(getRotation() - getRotationSpeed());
		}
	}
	// Determines what direction the user accesses cells based on direction
	if (getRotation() == 90)
		cellInteractionDirection.x = -1;
	else if (getRotation() == 180)
		cellInteractionDirection.y = -1;
	else if (getRotation() == 270)
		cellInteractionDirection.x = +1;
	else if (getRotation() == 0 || 360)
		cellInteractionDirection.y = +1;
	else
	{
		cellInteractionDirection.x = 0;
		cellInteractionDirection.y = 0;
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


		// Change speed when the player enters water
		if (level.World[chunkPos.x][chunkPos.y]->tiles[cellPos.x][cellPos.y]->isWater)
			setSpeed(1);
		else
			setSpeed(5);

	
}

void Agent::Move(Level& level, Point& StartPoint, Point& EndPoint)
{
	// Erase path
	path.erase(path.begin(), path.end());
	pathPointIterator = 0;

	// Move along path
	path = pathfinder.findPath(level, StartPoint, EndPoint);
	if (path.size() > 0)
	{
		movementStatus = TraversingPath;
		//this->isMoving = true;
	}
}
