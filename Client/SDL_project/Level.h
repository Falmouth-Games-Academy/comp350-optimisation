#pragma once
#include "Cell.h"
#include "Chunk.h"
#include "Point.h"
#include "Camera.h"
#include "ProceduralTerrain.h"

//! This class generates the base of the level 
/*!
This class creates a vector of vector of shared pointers to cells
*/

class Level
{
public:
	//! A constructor
	Level();
	//! A deconstructor 
	~Level();
	std::shared_ptr<Cell>& getCell(int cellX, int cellY);

	//! Return the cellSizes and level with/height
	int getCellSize() { return cellSize; }
	int getChunkSize() { return chunkSize; }
	int setCellSize(int newCellSize) { return cellSize = newCellSize; }
	int getLevelWidth() { return levelWidth; }
	int getLevelHeight() { return levelHeight; }

	//! Get and set the time of day (24 Hour)
	float getTimeOfDay() { return timeOfDay; }
	float setTimeOfDay(int newtime) { return timeOfDay = newtime; }

	//! The base grid that contains the cells
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	//! Returns the cells x and y value for the cell
	glm::vec2 Level::GetGlobalCell(Camera& camera, int cellX, int cellY);

	//! Creates a cell from json file
	

	//! Sets the cells value (NOT USED)
	void Level::SetCell(int x, int y, Cell& newcell);
	Cell& Level::GetCellFromJson(json& newcell);

	//! Generates the world around the camera
	void Level::GenerateWorld(Camera& camera);

	//! Creates a vector of vectors to store cells in
	void Level::CreateChunk(int initX, int initY);

	int xMinExplored = 0;
	int xMaxExplored = 0;
	int yMinExplored = 0;
	int yMaxExplored = 0;

	//! The wold contains key value pairs of chunks
	std::map<int, std::map<int, std::shared_ptr<Chunk>>> World;

	bool Level::isCellInChunk(int x, int y);




protected:
	//! Create an instance of procedural terrain for the world
	ProceduralTerrain proceduralTerrain;

	//! The size that the cell will be rendered at
	int cellSize = 50;
	//! chunkSizes value is set when level is constructed and is used for ease of access for the rest of the game to use
	int chunkSize;

	//! Time of day (24 hour)
	float timeOfDay = 12.0;

	//! The extra chunks that are generated at the screens border and beyond
	int levelGenerationRadius = 2;

	int levelWidth, levelHeight;
};

