#include "stdafx.h"
#include "Level.h"

// Creates a grid of cells at a specified location
void Level::CreateChunk(int initX, int initY)
{
	Chunk chunktemp(initX, initY);
	auto& chunk = std::make_shared<Chunk>(chunktemp);
	for (int x = 0; x < chunkSize; x++)
	{
		std::vector<std::shared_ptr<Cell>> column;
		
		chunk->tiles.push_back(column);
		for (int y = 0; y < chunkSize; y++)
		{
			// Populates the column with pointers to cells
			Cell cell(x + (initX * chunkSize), y + (initY * chunkSize));
			cell.isWalkable = true;
			if (cell.getX() < xMinExplored)
				xMinExplored = cell.getX() ;
			if (cell.getX() > xMaxExplored)
				xMaxExplored = cell.getX();
			if (cell.getY() < yMinExplored)
				yMinExplored = cell.getY();
			if (cell.getY() > yMaxExplored)
				yMaxExplored = cell.getY();

			
			auto sharedCell = std::make_shared<Cell>(cell);
			chunk->tiles[x].push_back(sharedCell);
		}	
	}
	World[initX][initY] = chunk;
}


// Generates a hashmap of chunks around the camera
void Level::GenerateWorld(Camera& camera)
{
	int numOfChunksWidth = ((camera.WindowWidth / cellSize) / chunkSize) + levelGenerationRadius;
	int numOfChunksHeight = ((camera.WindowHeight /cellSize) / chunkSize) + levelGenerationRadius;
	camera.ChunksOnScreen.x = numOfChunksWidth;
	camera.ChunksOnScreen.y = numOfChunksHeight;
	int numOfChunksGen = 0;
	for (int i = ((camera.getX() / cellSize) / chunkSize) - levelGenerationRadius; i < ((camera.getX() / cellSize) / chunkSize) + numOfChunksWidth; i++)
	{
		for (int j = ((camera.getY() / cellSize) / chunkSize) - levelGenerationRadius; j < ((camera.getY() / cellSize) / chunkSize) + numOfChunksHeight; j++)
		{
			// If the chunk hasnt already been created
			if (World[i][j] == NULL)
			{
				CreateChunk(i, j);
				proceduralTerrain.populateTerrain(World[i][j]);
				numOfChunksGen++;
			}
		}
	}
	
	if(numOfChunksGen > 0)
		std::cout << "Generated " << numOfChunksGen << " chunks." << std::endl;
}



// Returns the value of the x & y values in the cell
glm::vec2 Level::GetGlobalCell(Camera& camera, int cellX, int cellY)
{
	glm::vec2 returnPoint;
	// ChunkX/Y is the chunk that the cell is in
	int chunkX = cellX / chunkSize;
	int chunkY = cellY / chunkSize;

	// Get x and y values of each chunk
	if (cellX >= chunkSize)
		cellX = cellX - (chunkX * chunkSize);
	if (cellY >= chunkSize)
		cellY = cellY - (chunkY * chunkSize);
	
	// ReturPoint is the value of the x/y values in the cell (takes into account the camera position)
	returnPoint.x = World[chunkX][chunkY]->tiles[cellX][cellY]->getX() + (camera.getX() * chunkSize);
	returnPoint.y = World[chunkX][chunkY]->tiles[cellX][cellY]->getY() - (camera.getY() * chunkSize);

	double elevation = World[chunkX][chunkY]->tiles[cellX][cellY]->terrainElevationValue;

	std::cout << returnPoint.x << " " << returnPoint.y << "|" << chunkX - (camera.getX() / chunkSize) << " " << chunkY - (camera.getY() / chunkSize) << "|" << cellX << " " << cellY << "| " << elevation << std::endl;
	return returnPoint;
}

std::shared_ptr<Cell>& Level::getCell(int cellX, int cellY)
{
	
	int chunkX = (cellX / chunkSize);
	int chunkY = (cellY / chunkSize);
	cellX = cellX - chunkX * chunkSize;
	cellY = cellY - chunkY * chunkSize;

	if (cellX > chunkSize)
		cellX = cellX - (chunkX * chunkSize);
	if (cellY > chunkSize)
		cellY = cellY - (chunkY * chunkSize);

	if (cellX < 0)
	{
		cellX += chunkSize;
		chunkX -= 1;
	}
	if (cellY < 0)
	{
		cellY += chunkSize;
		chunkY -= 1;
	}
	if (isCellInChunk(cellX, cellY))
	{
		return World[chunkX][chunkY]->tiles[cellX][cellY];
	}
	
}

// Set a cell with the values of another cell
// If the chunk doesn't exist it will create it
void Level::SetCell(int x, int y, Cell& newcell)
{
	try
	{
		auto sharedCell = std::make_shared<Cell>(newcell);
		int chunkX = (x /chunkSize);
		int chunkY = (y / chunkSize);
		x = x - chunkX * chunkSize;
		y = y - chunkY * chunkSize;

		if (x > chunkSize)
			x = x - (chunkX * chunkSize);
		if (y > chunkSize)
			y = y - (chunkY * chunkSize);

		if (x < 0)
		{
			x += chunkSize;
			chunkX -= 1;
		}
		if (y < 0)
		{
			y += chunkSize;
			chunkY -= 1;
		}

		if (isCellInChunk(x, y))
		{
			//std::cout << "Cell update at pos: " << x << " " << y << std::endl;
			// Make sure that the chunk has been created before trying to place the cell
			if (World[chunkX][chunkY] != NULL)
			{
				World[chunkX][chunkY]->tiles[x][y] = sharedCell;
			}
			// Else create the chunk
			else
			{
				CreateChunk(chunkX, chunkY);
				World[chunkX][chunkY]->tiles[x][y] = sharedCell;
			}
		}
		
	}
	catch (std::exception e)
	{
		std::cout << "Error trying to set cell: " << x << ", " << y << ". " << e.what() << std::endl;
	}

}

Cell& Level::GetCellFromJson(json& json)
{
	Cell nc;
	int x = json.at("X").get<int>();
	int y = json.at("Y").get<int>();
	nc.setPos(x, y);

	int plantGrowthStage;

	if (json.count("Grass") > 0)
		nc.isGrass = json.at("Grass").get<bool>();
	if (json.count("Water") > 0)
		nc.isWater = json.at("Water").get<bool>();
	if (json.count("Sand") > 0)
		nc.isSand = json.at("Sand").get<bool>();
	if (json.count("Fence") > 0)
		nc.isWoodFence = json.at("Fence").get<bool>();
	if (json.count("Dirt") > 0)
		nc.isDirt = json.at("Dirt").get<bool>();
	if (json.count("Wheat") > 0)
		nc.isWheat = json.at("Wheat").get<bool>();
	if (json.count("Wood") > 0)
		nc.isWood = json.at("Wood").get<bool>();
	if (json.count("Stone") > 0)
		nc.isStone = json.at("Stone").get<bool>();
	if (json.count("StoneWall") > 0)
		nc.isStoneWall = json.at("StoneWall").get<bool>();
	if (json.count("PlantStage") > 0)
		nc.seedsStage = (Cell::seedsGrowthStage)json.at("PlantStage").get<int>();

	return nc;

}

bool Level::isCellInChunk(int x, int y)
{
	if (x >= 0 && x <= chunkSize && y >= 0 && y <= chunkSize)
		return true;
	else
		return false;
}

Level::Level()
{
	Chunk exampleChunk;
	chunkSize = exampleChunk.getChunkSize();
	
	exampleChunk.~Chunk();
}



Level::~Level()
{
}
