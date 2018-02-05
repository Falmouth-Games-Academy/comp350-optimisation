#pragma once
#include "Level.h"
#include "AgentManager.h"
#include "Agent.h"
#include "Camera.h"
#include "NetworkManager.h"
#include "Player.h"
#include "ToolBar.h"
#include "InventoryUI.h"
class UserInput
{
public:
	UserInput();
	~UserInput();

	Inventory craftingInventory;
	void UserInput::UseItemFromToolbar(int xPos, int yPos, ToolBar& toolbar, Player& player, Level& level, NetworkManager& networkManager, GameSettings& gameSettings, SDL_Renderer* renderer);

	void UserInput::HandleUserInput(SDL_Renderer* renderer, Level& level, Player& player, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar);

	bool UserInput::CheckIfCellIsWalkable(Level& level, int x, int y);

	void ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type);
private:
	float inventoryTimeout = 0;
	glm::vec2 playerChunkPos;
	glm::vec2 playercellPos;
	glm::vec2 InterDir;

	SDL_Joystick *joystick;
};

