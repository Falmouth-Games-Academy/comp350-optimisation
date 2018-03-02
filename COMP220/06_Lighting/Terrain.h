#pragma once

#include <vector>
#include "noise.h"
#include "Mesh.h"

class Terrain
{
public:
	Terrain(int iterations, Mesh &passedMesh);

	~Terrain();

	void generateTerrain(int maxX, int maxY, float noiseAmplification, float heightAmplification);

	double getLayeredNoise(double nx, double ny);

	//used to get mvp height
	double getXMax() { return xMax; }
	double getYMax() { return yMax; }
	double getNoiseAmp() { return noiseAmp; }
	double getHeightAmp() { return heightAmp; }

private:
	std::vector<noise::Perlin> noiseArray;

	//determine the colour based on the position of the point
	glm::vec3 getColour(double &layeredNoise);

	//mesh to add the terrain to
	Mesh *mesh;

	//stored for use in player movement
	double xMax;
	double yMax;
	double noiseAmp;
	double heightAmp;
};

