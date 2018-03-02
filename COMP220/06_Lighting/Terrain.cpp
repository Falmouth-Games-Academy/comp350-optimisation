#include "stdafx.h"
#include "Terrain.h"
#include "time.h"

Terrain::Terrain(int iterations, Mesh &passedMesh)
{
	for (int i = 0; i < iterations; i++)
	{
		noiseArray.push_back(noise::Perlin(time(0) + iterations * i));
	}

	mesh = &passedMesh;
}

void Terrain::generateTerrain(int maxX, int maxY, float noiseAmplification, float heightAmplification)
{
	double previousNx = 0, previousNy = 0;
	for (double x = 1; x < maxX; x++)
	{
		double nx = x / maxX * noiseAmplification;
		for (double y = 1; y < maxY; y++)
		{
			double ny = y / maxY * noiseAmplification;

			//vertex layered noise
			double ln1 = getLayeredNoise(previousNx, previousNy);
			double ln2 = getLayeredNoise(nx, previousNy);
			double ln3 = getLayeredNoise(nx, ny);
			double ln4 = getLayeredNoise(previousNx, ny);

			//vertex positions
			glm::vec3 p1(x - 1, ln1 * heightAmplification, y - 1);
			glm::vec3 p2(x, ln2 * heightAmplification, y - 1);
			glm::vec3 p3(x, ln3 * heightAmplification, y);
			glm::vec3 p4(x - 1, ln4 * heightAmplification, y);

			Vertex v1(p1, getColour(ln1));
			Vertex v2(p2, getColour(ln2));
			Vertex v3(p3, getColour(ln3));
			Vertex v4(p4, getColour(ln4));

			mesh->addSquare(v4, v3, v2, v1);

			previousNy = ny;

		}

		previousNx = nx;
	}
	xMax = maxX;
	yMax = maxY;
	noiseAmp = noiseAmplification;
	heightAmp = heightAmplification;
}

// Layers higher frequencys of noise over original generation for more varience
double Terrain::getLayeredNoise(double nx, double ny)
{
	int numberOfIterations = noiseArray.size();
	double layerOpacity = 1;
	double exponenial = 1;
	double noise = 0;

	for (int i = 0; i < numberOfIterations; i++)
	{
		layerOpacity /= 2;
		noise += layerOpacity * noiseArray[i].noise(exponenial * nx, exponenial * ny);
		exponenial *= 2;
	}
	return noise;
}

glm::vec3 Terrain::getColour(double &layeredNoise)
{
	glm::vec3 col(layeredNoise + 0.5, (layeredNoise + 0.5), (layeredNoise + 0.5));
	col = col + glm::vec3(0, 1 - (layeredNoise + 0.75), 0);
	if (layeredNoise <= -0.1)
	{
		col = col + glm::vec3(0,0, 1);
	}
	return col;
}




Terrain::~Terrain()
{
}
