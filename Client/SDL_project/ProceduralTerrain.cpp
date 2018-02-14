#include "stdafx.h"
#include "ProceduralTerrain.h"


ProceduralTerrain::ProceduralTerrain()
{
	//set random seed to seednumber
	srand(seed);

	Elevation.GenerateNoise(elevationSeed);
	ElevationLayerTwo.GenerateNoise(elevationSeed - 1234);
	ElevationLayerThree.GenerateNoise(elevationSeed + 1234);


	forrestNoise.GenerateNoise(forrestSeed);
	riverNoise.GenerateNoise(riverSeed);
	riverNoiseLayerTwo.GenerateNoise(riverSeed / 2);
}


ProceduralTerrain::~ProceduralTerrain()
{
}

void ProceduralTerrain::spawnRandomTrees(std::shared_ptr<Chunk>& chunk)
{
	for (int i = numberOfTrees; i > 0; i--)
	{
		int x = rand() % chunk->tiles.size();
		int y = rand() % chunk->tiles[0].size();
		if (!chunk->tiles[x][y]->isVegetation && !chunk->tiles[x][y]->isWater)
		{
			chunk->tiles[x][y]->isVegetation = true;
			chunk->tiles[x][y]->isWalkable = false;

			int treeType = rand() % 3;
			if (treeType <= 0)
			{
				chunk->tiles[x][y]->isTree = true;
				chunk->tiles[x][y]->isWalkable = false;
				chunk->tiles[x][y]->treeType = Cell::fernTree;
			}
			else if (treeType == 1)
			{
				chunk->tiles[x][y]->isTree = true;
				chunk->tiles[x][y]->isWalkable = false;
				chunk->tiles[x][y]->treeType = Cell::pineTree;
			}
			else
			{
				chunk->tiles[x][y]->isTree = true;
				chunk->tiles[x][y]->treeType = Cell::oakTree;
				chunk->tiles[x][y]->isWalkable = false;
			}
		}
	}
}

void ProceduralTerrain::spawnRandomVegetation(std::shared_ptr<Chunk>& chunk)
{	
	for (int i = numberOfPlants; i > 0; i--)
	{
		int x = rand() % chunk->tiles.size();
		int y = rand() % chunk->tiles[0].size();
		
		if (!chunk->tiles[x][y]->isVegetation && !chunk->tiles[x][y]->isWater && !chunk->tiles[x][y]->isSand)
		{
			chunk->tiles[x][y]->isVegetation = true;
			int vegType = rand() % 3;

			switch (vegType)
			{
			case 0:
				chunk->tiles[x][y]->isFlower1 = true;
				break;
			case 1:
				chunk->tiles[x][y]->isFlower2 = true;
				break;
			case 2:
				chunk->tiles[x][y]->isRock = true;
				break;
			}
		}
	}
}


void ProceduralTerrain::populateTerrain(std::shared_ptr<Chunk>& chunk)
{
	//Renders all he cells
	for (int x = 0; x < chunk->getChunkSize(); x++)
	{
		for (int y = 0; y < chunk->getChunkSize(); y++)
		{
			//Generate the grass
			generateGround(chunk, x, y);
		}
	}
	//Cant spawn random items because that will cause de-sync between clients
	//spawnRandomTrees(chunk);
	//spawnRandomVegetation(chunk);
}

//TODO: Put all constant values in the headder
void ProceduralTerrain::generateGround(std::shared_ptr<Chunk>& chunk, int x, int y)
{
	float noiseX = chunk->tiles[x][y]->getX();
	float noiseY = chunk->tiles[x][y]->getY();
	double terrainElevation = Elevation.noise((double)noiseX / terrainNoiseOffest, (double)noiseY / terrainNoiseOffest, 0.0) * 20.0;
	double terrainElevationTwo = ElevationLayerTwo.noise((double)noiseX / terrainNoiseOffest / 2.0, (double)noiseY / terrainNoiseOffest / 2.0, 0.0) * 20.0;
	double terrainElevationThree = ElevationLayerThree.noise((double)noiseX, (double)noiseY, 0.0) * 20.0;
	double sNoise = simNoise.noise(noiseX / 40, noiseY / 40);

	

	terrainElevation = sNoise + terrainElevationTwo + terrainElevation + terrainElevationThree + 2;
	double climate = sin(chunk->tiles[x][y]->getY() / 500.0);
	
	
	double fNoise = forrestNoise.noise((double)noiseX / forrestNoiseOffset, (double)noiseY / forrestNoiseOffset, 0.0) * 20.0;
	fNoise += simNoise.noise(noiseX / forrestJaggedness, noiseY / forrestJaggedness);

	double gNoise = grassNoise.noise(noiseX / 15, noiseY / 15) + fNoise;
	double rNoise = (riverNoise.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0) + (riverNoiseLayerTwo.noise((double)noiseX / 300.0, (double)noiseY / 300.0, 0.0) * 20.0);
	rNoise += simNoise.noise(noiseX / riverBendyness, noiseY / riverBendyness);
	
	//set the cells terrain value
	chunk->tiles[x][y]->terrainElevationValue = terrainElevation;

	if (climate > 0 || !thereIsClimate)
	{
		// TERRAIN NOISE
		if (terrainElevation >= -1.8 && terrainElevation <= 20.0)
		{
			chunk->tiles[x][y]->isGrass = true;
		}
		else if (terrainElevation >= -2.3 && terrainElevation < -1.8)
		{
			chunk->tiles[x][y]->isSand = true;
			chunk->tiles[x][y]->isGrass = false;
			chunk->tiles[x][y]->isWater = false;
		}
		else if (terrainElevation < -2.3)
		{
			chunk->tiles[x][y]->isWater = true;
		}
		else if (terrainElevation > 10.0 && terrainElevation < 20.0)
		{
			chunk->tiles[x][y]->isStone = true;
		}
		else if (terrainElevation > 20.0)
		{
			chunk->tiles[x][y]->isSnow = true;
		}

		// FORREST NOISE ///////////
		// If spawn something cool when the forrest value is greater than the max set ( the center of a forrest)
		if (chunk->tiles[x][y]->isGrass && fNoise > 14.0 && rand() % numberOfTrees == 1)
		{
			chunk->tiles[x][y]->isTree = true;
			chunk->tiles[x][y]->treeType == Cell::fernTree;
			chunk->tiles[x][y]->isWalkable = false;
		}
		else if (chunk->tiles[x][y]->isGrass && fNoise > 8.0 && fNoise < 12.0 && rand() % numberOfTrees == 1)
		{
			chunk->tiles[x][y]->isTree = true;
			chunk->tiles[x][y]->treeType == Cell::oakTree;
			chunk->tiles[x][y]->isWalkable = false;
		}

		// Grass noise
		if (chunk->tiles[x][y]->isGrass && gNoise > 4.0 && gNoise < 10.0)
		{
			int randSpawn = rand() % 10;
			if (randSpawn == 0)
				chunk->tiles[x][y]->isLongGrass = true;
			else if (randSpawn == 1)
				chunk->tiles[x][y]->isFlower1 = true;
			else if (randSpawn == 2)
				chunk->tiles[x][y]->isFlower2 = true;
			else if(randSpawn == 3)
				chunk->tiles[x][y]->isLongGrass2 = true;
		}


		// RIVER NOISE
		if (rNoise > 0.5 && rNoise < 1.0)
		{
			chunk->tiles[x][y]->isWater = true;
			chunk->tiles[x][y]->terrainElevationValue = -2.1;

		}
		else if (rNoise >= 1.0 && rNoise < 1.3 || rNoise >= 0.3 && rNoise <= 0.5 && chunk->tiles[x][y]->isGrass)
		{
			chunk->tiles[x][y]->isSand = true;
			chunk->tiles[x][y]->isGrass = false;
		}
	}
	else
	{
		if (terrainElevation > -1.8 && terrainElevation < 13.0)
			chunk->tiles[x][y]->isSnow = true;
		else if (terrainElevation < -2)
			chunk->tiles[x][y]->isWater = true; // Change to ice
	}
}

