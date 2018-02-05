#pragma once
#include "Cell.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	Chunk::Chunk(int initX, int initY);
	int getChunkSize() { return chunkSize; }
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;

	int getX() { return x; }
	int getY() { return y; }
	
private:
	int x = 0;
	int y = 0;
	int chunkSize = 16;
	
	std::string chunkID;
};

