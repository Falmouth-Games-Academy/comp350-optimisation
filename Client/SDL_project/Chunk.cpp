#include "stdafx.h"
#include "Chunk.h"


Chunk::Chunk()
{
}
Chunk::Chunk(int initX, int initY)
{
	x = initX;
	y = initY;
	chunkID = "X:" + std::to_string(x) + ",Y:" + std::to_string(y);
}



Chunk::~Chunk()
{
	if(!tiles.empty())
		tiles.erase(tiles.begin() , tiles.end());

}
