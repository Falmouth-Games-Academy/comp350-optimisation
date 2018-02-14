#pragma once
#include "cell.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include "Chunk.h"
#include "point.h"
#include "Camera.h"



class ProceduralTerrain
{
public:
	ProceduralTerrain();
	~ProceduralTerrain();
	//! Elevation noise
	PerlinNoise Elevation;
	PerlinNoise ElevationLayerTwo;
	PerlinNoise ElevationLayerThree;
	SimplexNoise simNoise;
	SimplexNoise grassNoise;

	//! Other noise generations
	PerlinNoise forrestNoise;
	PerlinNoise riverNoise;
	PerlinNoise riverNoiseLayerTwo;


	//! Getters and setters for seed
	int getSeed() { return seed; }
	int setSeed(int newSeed) { return seed = newSeed; }

	//! function that calls the functions below
	void ProceduralTerrain::populateTerrain(std::shared_ptr<Chunk>& level);
	//! Spawns the trees in a chunk
	void ProceduralTerrain::spawnRandomTrees(std::shared_ptr<Chunk>& chunk);
	//! Spawn the vegetation
	void ProceduralTerrain::spawnRandomVegetation(std::shared_ptr<Chunk>& chunk);
	//! Generate the ground based of the elevation and climate
	void ProceduralTerrain::generateGround(std::shared_ptr<Chunk>& chunk, int x, int y);

private:
	//! Seed values are random
	int seed = 3210387;
	int forrestSeed = seed + 30;
	int elevationSeed = seed + 36945;
	int riverSeed = seed + 1255;

	// Lower is more
	int riverBendyness = 50;
	int forrestJaggedness = 50;

	//! Needs work
	//! Makes the sin of the y cell pos to be the climate
	//! Turns grass into snow and water into ice
	bool thereIsClimate = false;

	float terrainNoiseOffest = 180.0;
	float forrestNoiseOffset = 180.0;

	float forrestAmplifier = 1.5;

	// Number of items randomly placed in chunk
	int numberOfTrees = 2;
	int numberOfPlants = 4;

};

