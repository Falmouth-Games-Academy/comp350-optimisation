#include "stdafx.h"
#include "AgentManager.h"


AgentManager::AgentManager() : characterTex(characterTextureLocation + "crew2.png"), characterLeft(characterTextureLocation + "crewLeft.png"), characterRight(characterTextureLocation + "crewRight.png"), characterUp(characterTextureLocation + "crewUp.png"), characterDown(characterTextureLocation + "crewDown.png"),
npcLeft(characterTextureLocation + "npcLeft.png"), npcRight(characterTextureLocation + "npcRight.png"), npcUp(characterTextureLocation + "npcUp.png"), npcDown(characterTextureLocation + "npcDown.png"),
healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"), hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png")
{
}


AgentManager::~AgentManager()
{

}

void AgentManager::SpawnAgent(std::string CharacterTypeVar, std::vector<Agent>& allAgents, int x, int y)
{
		Agent newAgent;
		newAgent.setX(x);
		newAgent.setY(y);
		newAgent.characterType = CharacterTypeVar;
		allAgents.push_back(newAgent);
}

void AgentManager::SpawnAgent(Agent& agent)
{
	
	allAgents.push_back(agent);
}

int AgentManager::GetAgentNumberFomID(std::string ID)
{
	for (int i = 0; i < allAgents.size(); i++)
	{
		if (ID == allAgents[i].getID())
		{
			return i;
		}
	}
}

void AgentManager::EraseAllAgentPaths(std::vector<Agent>& allAgents) 
{
	for (int i = 0; i < allAgents.size(); i++)
	{
		allAgents[i].path.erase(allAgents[i].path.begin(), allAgents[i].path.end());
		allAgents[i].agentMovementStatus::Idle;

	}
}

void AgentManager::EraseAllAgents(std::vector<Agent>& allAgents)
{
	allAgents.erase(allAgents.begin(), allAgents.end());
}

void drawPath(Point& point, Level& level, std::vector<Point>& path, SDL_Renderer* renderer)
{
	// Start at the start point


	// tileSize / 2 is added to all coordinates to put them in the centre of the tile
	int lastX = point.getX() * level.getCellSize() + level.getCellSize() / 2;
	int lastY = point.getY() * level.getCellSize() + level.getCellSize() / 2;


	// Step through the path
	for (const Point& point : path)
	{
		int nextX = point.getX() * level.getCellSize() + level.getCellSize() / 2;
		int nextY = point.getY() * level.getCellSize() + level.getCellSize() / 2;

		SDL_RenderDrawLine(renderer, lastX, lastY, nextX, nextY);
		lastX = nextX;
		lastY = nextY;
	}

}


void AgentManager::UpdateAgents(std::vector<Agent>& allAgents, SDL_Renderer* renderer, Level& level, Camera& camera)
{
	// Update agents and draw agent paths
	for (int i = 0; i < allAgents.size(); i++)
	{
		allAgents[i].Update(level);

		// DRAW THE PATH FOR ALL AGENTS
		if (drawAgentPaths)
		{
			for (int ip = 0; ip < allAgents[i].path.size(); ip++)
				drawPath(allAgents[i].path[ip], level, allAgents[i].path, renderer);
		}
	}


}

