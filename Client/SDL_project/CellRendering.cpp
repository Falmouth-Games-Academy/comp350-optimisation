#include "stdafx.h"
#include "CellRendering.h"

//! Constructor that initalises all the texture file locations
CellRendering::CellRendering() : roomCell(RoomSpriteTextureLocation + "center.png"), emptyCell(RoomSpriteTextureLocation + "emptyCell.png"),
Grass1Texture(TerrainSpriteTextureLocation + "Grass.png"),
Grass2Texture(TerrainSpriteTextureLocation + "Grass2.png"),
DirtTexture(TerrainSpriteTextureLocation + "Dirt.png"),
Flower1Texture(TerrainSpriteTextureLocation + "Flower1.png"),
Flower2Texture(TerrainSpriteTextureLocation + "Flower2.png"),
BerryPlantTexture(TerrainSpriteTextureLocation + "Berry.png"),
BushTexture(TerrainSpriteTextureLocation + "Bush.png"),
WaterTexture(TerrainSpriteTextureLocation + "\\Sea\\Water.png"),
WaterTexture2(TerrainSpriteTextureLocation + "\\Sea\\Water2.png"),
SandTexture(TerrainSpriteTextureLocation + "Sand.png"),
LongGrass1(TerrainSpriteTextureLocation + "LongGrass1.png"),
LongGrass2(TerrainSpriteTextureLocation + "LongGrass2.png"),
LongGrass3(TerrainSpriteTextureLocation + "LongGrass3.png"),
rockTexture(TerrainSpriteTextureLocation + "Rock.png"),
StoneWallTexture(TerrainSpriteTextureLocation + "StoneWall.png"),
StoneTexture(TerrainSpriteTextureLocation + "Stone.png"),
OakTreeTexture(TerrainSpriteTextureLocation + "OakTree.png"),
FernTreeTexture(TerrainSpriteTextureLocation + "FernTree.png"),
PineTreeTexture(TerrainSpriteTextureLocation + "PineTree.png"),
TreePixelTexture(TreeTerrainSpriteTextureLocation + "pixelTree.png"),
TreeTwoTexture(TreeTerrainSpriteTextureLocation + "Tree2.png"),
TreeThreeTexture(TreeTerrainSpriteTextureLocation + "Tree3.png"),
SnowTexture(TerrainSpriteTextureLocation + "Snow.png"),
WoodTexture(TerrainSpriteTextureLocation + "Wood.png"),
WoodFenceSide(WallSpriteTextureLocation + "woodFenceSideCenter.png"), WoodFenceUP(WallSpriteTextureLocation + "woodFenceUp2.png"), WoodFenceCenter(WallSpriteTextureLocation + "woodFenceCenter.png"),
WheatStageOne(TerrainSpriteTextureLocation + "WheatStageOne.png"), WheatStageTwo(TerrainSpriteTextureLocation + "WheatStageTwo.png"), WheatStageThree(TerrainSpriteTextureLocation + "WheatStageThree.png"), WheatStageFour(TerrainSpriteTextureLocation + "WheatStageFour.png"),

characterTex(characterTextureLocation + "Alli.png"), npcDown(characterTextureLocation + "Sam.png"),
healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"), hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png")

{
}

//! Destructor
CellRendering::~CellRendering()
{
}

void CellRendering::AlterTextures(Level& level)
{
	WaterTexture.alterTransparency(200);
	WaterTexture2.alterTransparency(200);
	//TreePixelTexture.alterTransparency(200);

		time = level.getTimeOfDay();

		if (time > 9.0 && time < 21.0)
		{
			Tdarkness = 255;
		}
		else if (time < 9.0 || time > 21.0)
		{
			Tdarkness = 50;
		}


		if (Tdarkness > darkness)
			darkness++;
		else if (Tdarkness < darkness)
			darkness--;
		
		Grass1Texture.alterTextureColour(darkness, darkness, darkness);
		TreePixelTexture.alterTextureColour(darkness, darkness, darkness);
		SandTexture.alterTextureColour(darkness, darkness, darkness);
		WaterTexture.alterTextureColour(darkness, darkness, darkness);
		WaterTexture2.alterTextureColour(darkness, darkness, darkness);
		LongGrass1.alterTextureColour(darkness, darkness, darkness);
		LongGrass2.alterTextureColour(darkness, darkness, darkness);
		LongGrass3.alterTextureColour(darkness, darkness, darkness);
		PineTreeTexture.alterTextureColour(darkness, darkness, darkness);
		OakTreeTexture.alterTextureColour(darkness, darkness, darkness);
		FernTreeTexture.alterTextureColour(darkness, darkness, darkness);
}

void CellRendering::RenderChunk(Level& level, Camera& camera, Player& player, std::shared_ptr<Chunk>& chunk, SDL_Renderer* renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = level.getCellSize();

	
	for (int x = 0; x < level.getChunkSize(); x++)
		for (int y = 0; y < level.getChunkSize(); y++)
		{
			newX = chunk->tiles[x][y]->getX();
			newY = chunk->tiles[x][y]->getY();

			xPos = newX * cellSize + cellSize / 2;
			yPos = newY * cellSize + cellSize / 2;

			xPos -= camera.getX();
			yPos -= camera.getY();

			//int light = chunk->tiles[x][y]->cellLightness;
			//LongGrass3.alterTextureColour(darkness + light, darkness + light, darkness + light);

			if (chunk->tiles[x][y]->isWater)
			{
				// Code for ripples
				//sin(sqrt(pow(chunk->tiles[x][y]->getX(),2) + pow(chunk->tiles[x][y]->getY(),2)) + SDL_GetTicks() / 500) > 0)
				if (sin(chunk->tiles[x][y]->getX() + SDL_GetTicks() / 500) > 0)
					WaterTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				else
					WaterTexture2.render(renderer, xPos, yPos, cellSize, cellSize);
				
			}
			else
			{
				// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
				if (chunk->tiles[x][y]->isGrass)
					Grass1Texture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isFlower1)
					Flower1Texture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isDirt)
					DirtTexture.render(renderer, xPos, yPos, cellSize, cellSize);

				
				if (chunk->tiles[x][y]->isSand)
					SandTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isStoneWall)
					StoneWallTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isFlower1)
					Flower1Texture.render(renderer, xPos, yPos, cellSize / 3, cellSize / 2);
				if (chunk->tiles[x][y]->isFlower2)
					Flower2Texture.render(renderer, xPos, yPos, cellSize / 3, cellSize / 2);
				if (chunk->tiles[x][y]->isBerryPlant)
					BerryPlantTexture.render(renderer, xPos, yPos, cellSize / 2, cellSize / 1.5);
				if (chunk->tiles[x][y]->isBush)
					BushTexture.render(renderer, xPos, yPos, cellSize / 2, cellSize / 1.5);
				if (chunk->tiles[x][y]->isLongGrass)
					LongGrass1.render(renderer, xPos - cellSize, yPos, cellSize * 2, cellSize);
				if (chunk->tiles[x][y]->isLongGrass2)
					LongGrass2.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isSnow)
					SnowTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if(chunk->tiles[x][y]->isRock)
					rockTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isWood)
					WoodTexture.render(renderer, xPos, yPos, cellSize, cellSize);
				if (chunk->tiles[x][y]->isStone)
					StoneTexture.render(renderer, xPos, yPos, cellSize, cellSize);

				if (chunk->tiles[x][y]->isWheat)
				{
					switch (chunk->tiles[x][y]->seedsStage)
					{
					case Cell::seedsGrowthStage::PlantStageOne:
						WheatStageOne.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					case Cell::seedsGrowthStage::PlantStageTwo:
						WheatStageTwo.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					case Cell::seedsGrowthStage::PlantStageThree:
						WheatStageThree.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					case Cell::seedsGrowthStage::PlantStageFour:
						WheatStageFour.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					}
				}
				
				if (chunk->tiles[x][y]->isTree)
				{
					// Above player

					tree t;
					if (chunk->tiles[x][y]->treeType == Cell::TreeType::oakTree)
						t.isOak = true;
					if (chunk->tiles[x][y]->treeType == Cell::TreeType::fernTree)
						t.isFern = true;
					if (chunk->tiles[x][y]->treeType == Cell::TreeType::pineTree)
						t.isPine = true;
					t.pos = glm::vec2(xPos, yPos - cellSize * 3 + cellSize);
					t.treeSize = glm::vec2(cellSize * 3, cellSize * 6);
					if (chunk->tiles[x][y]->getY() > player.getY() / level.getCellSize())
						treesBelow.push_back(t);
					else
						treesAbove.push_back(t);

				}
					
					
				
				if (chunk->tiles[x][y]->isWoodFence)
				{
					WoodFenceCenter.render(renderer, xPos, yPos, cellSize, cellSize);
					// Uncomment for fences to be combined
					if (level.isCellInChunk(x, y - 1) && level.isCellInChunk(x, y + 1) && level.isCellInChunk(x - 1, y) && level.isCellInChunk(x + 1, y))
					{
						if (chunk->tiles[x][y]->isWoodFence && chunk->tiles[x][y + 1]->isWoodFence && chunk->tiles[x][y - 1]->isWoodFence && !chunk->tiles[x + 1][y]->isWoodFence && !chunk->tiles[x - 1][y]->isWoodFence)
							WoodFenceUP.render(renderer, xPos, yPos, cellSize, cellSize);
						else if (chunk->tiles[x][y]->isWoodFence && chunk->tiles[x][y + 1]->isWoodFence && chunk->tiles[x][y - 1]->isWoodFence && chunk->tiles[x + 1][y]->isWoodFence && chunk->tiles[x - 1][y]->isWoodFence)
							WoodFenceCenter.render(renderer, xPos, yPos, cellSize, cellSize);
						else
							WoodFenceSide.render(renderer, xPos, yPos, cellSize, cellSize);
					}
					
				}
			}
		}
}


//! Renders the chunks of cells
void CellRendering::RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, Player& player, std::vector<std::shared_ptr<Player>>& allPlayers)
{	
	// Alter the textures
	AlterTextures(level);

	// Render all the cells in the chunks
	for (int i = (camera.getX() / level.getCellSize()) / level.getChunkSize() - 1; i < ((camera.getX() / level.getCellSize()) / level.getChunkSize()) + camera.ChunksOnScreen.x; i++)
		for (int j = (camera.getY() / level.getCellSize()) / level.getChunkSize() - 1; j < ((camera.getY() / level.getCellSize()) / level.getChunkSize()) + camera.ChunksOnScreen.y; j++)
				RenderChunk(level,camera,player, level.World[i][j], renderer);


	
	// Render all the trees above the player
	for each(auto &tree in treesAbove)
	{
		if (tree.isFern)
			FernTreeTexture.render(renderer, tree.pos.x, tree.pos.y, tree.treeSize.x, tree.treeSize.y);
		else if (tree.isOak)
			OakTreeTexture.render(renderer, tree.pos.x, tree.pos.y, tree.treeSize.x, tree.treeSize.y);
		else if (tree.isPine)
			PineTreeTexture.render(renderer, tree.pos.x, tree.pos.y, tree.treeSize.x, tree.treeSize.y);
	}

	// Render the player
	player.RenderPlayer(renderer, camera);
	//Update and render multi players
	for each (auto &player in allPlayers)
	{
		player->Update(level);
		player->RenderPlayer(renderer, camera);
	}

	// Render the trees below last
	for each(auto &tree in treesBelow)
	{
		if (tree.isFern)
			FernTreeTexture.render(renderer, tree.pos.x, tree.pos.y, tree.treeSize.x, tree.treeSize.y);
		else if (tree.isOak)
			OakTreeTexture.render(renderer, tree.pos.x, tree.pos.y, tree.treeSize.x, tree.treeSize.y);
		else if (tree.isPine)
			PineTreeTexture.render(renderer, tree.pos.x, tree.pos.y, tree.treeSize.x, tree.treeSize.y);
	}
	hungerBarTexture.alterTransparency(100);
	hungerBarTexture.render(renderer, player.placeItemPos.x * level.getCellSize() + (level.getCellSize() / 2) - camera.getX() , player.placeItemPos.y * level.getCellSize() + (level.getCellSize() / 2) - camera.getY(), level.getCellSize(), level.getCellSize());
	
	// Erase the trees after rendering them
	treesBelow.erase(treesBelow.begin(), treesBelow.end());
	treesAbove.erase(treesAbove.begin(), treesAbove.end());
	
}

void CellRendering::RenderPlayer(SDL_Renderer* renderer, Player& player,  Level& level, Camera& camera)
{
	//int x = player.getX() - camera.getX();
	//int y = player.getY() - camera.getY();
	//player.setPosition(x, y);
	//if (player.characterType == "Player")
		//characterTex.renderRotation(renderer, x, y, player.getSize(), player.getSize(), player.getRotation());
		//player.RenderPlayer(renderer);

}

void CellRendering::RenderAgents(Agent& agent, SDL_Renderer* renderer, Level& level, Camera& camera)
{

	int x = agent.getX()  - camera.getX();
	int y = agent.getY()  - camera.getY();
	if (agent.characterType == "NPC")
	{
		//npcDown.alterTextureColour(0, rand(), 0);
		npcDown.renderRotation(renderer, x, y, agent.getSize(), agent.getSize(), agent.getRotation());


		//Render agent stats to the right of agent
		if (renderStats)
		{
			if (agent.getHealth() < 100.0)
				healthBarTexture.render(renderer, x + agent.getSize() - agent.getSize() / 10, y, agent.getSize() / 10, agent.getHealth() / 2);
			if (agent.getOxygenLevel() < 100.0)
				oxygenBarTexture.render(renderer, x + agent.getSize(), y, agent.getSize() / 10, agent.getOxygenLevel() * 30.0);
			if (agent.getHunger() < 100.0)
				hungerBarTexture.render(renderer, x + agent.getSize() + agent.getSize() / 10, y, agent.getSize() / 10, agent.getHunger() * 30.0);
			if (agent.getTiredness() > 0.0)
				tiredBarTexture.render(renderer, x + agent.getSize() + agent.getSize() * 2 / 10, y, agent.getSize() / 10, agent.getTiredness() * 100);
			if (agent.getToietNeed() > 0.0)
				hungerBarTexture.render(renderer, x + agent.getSize() + agent.getSize() / 10, y, agent.getSize() / 10, agent.getToietNeed() * 100);
		}
	}
	if (agent.characterType == "Player")
		characterTex.renderRotation(renderer, x, y, agent.getSize(), agent.getSize(), agent.getRotation());
}