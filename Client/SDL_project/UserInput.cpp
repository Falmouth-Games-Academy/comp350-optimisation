#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
	
}


UserInput::~UserInput()
{
}

bool UserInput::CheckIfCellIsWalkable(Level& level, int x, int y)
{
	
	int chunkX = (x / level.getCellSize()) / level.getChunkSize();
	int chunkY = (y / level.getCellSize()) / level.getChunkSize();

	int cellX = x / level.getCellSize() - (chunkX * level.getChunkSize());
	int cellY = y / level.getCellSize() - (chunkY * level.getChunkSize());

	//for negative cells
	if (cellX < 0)
	{
		cellX += level.getChunkSize();
		chunkX -= 1;
	}
	if (cellY < 0)
	{
		cellY += level.getChunkSize();
		chunkY -= 1;
	}

	if (!level.World[chunkX][chunkY]->tiles[cellX][cellY]->isWalkable)
	{
		return false;
	}
	else
		return true;
}

void UserInput::HandleUserInput(SDL_Renderer* renderer, Level& level, Player& player, AgentManager& agentManager, NetworkManager& networkManager, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar)
{
	int cellSize = level.getCellSize();
	//SDL_JoystickEventState(SDL_ENABLE);
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			gameSettings.running = false;
		}
		//Mouse wheel
		switch (ev.type)
		{
		case SDL_MOUSEWHEEL:  /* Handle Mousewheel Motion */
			if (ev.wheel.x < 0)
			{
				std::cout << "MOUSE : WHEEL LEFT" << std::endl;
			}
			else if (ev.wheel.x > 0)
			{
				std::cout << "MOUSE : WHEEL RIGHT" << std::endl;
			}
			if (ev.wheel.y < 0)
			{
				toolbar.setToolbarSelection(toolbar.getToolbarSelection() + 1);
			}
			else if (ev.wheel.y > 0)
			{
				toolbar.setToolbarSelection(toolbar.getToolbarSelection() - 1);
			}
			break;

		case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
			//std::cout << ev.jaxis.which << std::endl;
			if (ev.jaxis.axis == 0)
			{
				if (ev.jaxis.value < 0)
					player.setX(player.getX() - player.getSpeed());
				else if (ev.jaxis.value > 0)
					player.setX(player.getX() + player.getSpeed());
			}

			else if (ev.jaxis.axis == 1)
			{
				if (ev.jaxis.value < 0)
					player.setY(player.getY() - player.getSpeed());
				else if (ev.jaxis.value > 0)
					player.setY(player.getY() + player.getSpeed());
			}
			break;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		gameSettings.running = false;

	int playerX = player.getX();
	int playerY = player.getY();
	int playerSpeed = player.getSpeed();
	int agentNo = agentManager.GetAgentNumberFomID(player.getID());
	playerChunkPos = player.chunkPos;
	playercellPos = player.cellPos;
	/////////// PLAYER MOVEMENT ////////////
	//Diagonal movement
	if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D])
	{
		//player.setTargetRotation(225);
		player.setTargetRotation(270);
		player.setPlayerMoving(true);
		if(CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY - playerSpeed))
			player.setPosition(playerX + playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
	{
		//player.setTargetRotation(135);
		player.setTargetRotation(90);
		player.setPlayerMoving(true);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY - playerSpeed))
			player.setPosition(playerX - playerSpeed, playerY - playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(-45);
		player.setTargetRotation(270);
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY + playerSpeed))
			player.setPosition(playerX + playerSpeed, playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		//player.setTargetRotation(45);
		player.setTargetRotation(90);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY + playerSpeed))
			player.setPosition(playerX - playerSpeed, playerY + playerSpeed);
	}
	// Player Movement
	else if (state[SDL_SCANCODE_S])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(0);
		if (CheckIfCellIsWalkable(level, playerX, playerY + playerSpeed))
			player.setY(playerY + playerSpeed);
	}
	else if (state[SDL_SCANCODE_A])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(90);
		if (CheckIfCellIsWalkable(level, playerX - playerSpeed, playerY))
			player.setX(playerX - playerSpeed);

	}
	else if (state[SDL_SCANCODE_D])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(270);
		if (CheckIfCellIsWalkable(level, playerX + playerSpeed, playerY))
			player.setX(playerX + playerSpeed);
	}
	else if (state[SDL_SCANCODE_W])
	{
		player.setPlayerMoving(true);
		player.setTargetRotation(180);
		if (CheckIfCellIsWalkable(level, playerX, playerY - playerSpeed))
			player.setY(playerY - playerSpeed);
	}
	else
	{
		player.setSpeed(0);
		player.setPlayerMoving(false);
		player.setTargetRotation(0);
		//Reset the walk animation
		player.getWalkAnimation().setCurrentFrame(0);
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ACTION BAR
	if (state[SDL_SCANCODE_0])
		toolbar.setToolbarSelection(10);
	else if (state[SDL_SCANCODE_1])
		toolbar.setToolbarSelection(0);
	else if (state[SDL_SCANCODE_2])
		toolbar.setToolbarSelection(1);
	else if (state[SDL_SCANCODE_3])
		toolbar.setToolbarSelection(2);
	else if (state[SDL_SCANCODE_4])
		toolbar.setToolbarSelection(3);
	else if (state[SDL_SCANCODE_5])
		toolbar.setToolbarSelection(4);
	else if (state[SDL_SCANCODE_6])
		toolbar.setToolbarSelection(5);
	else if (state[SDL_SCANCODE_7])
		toolbar.setToolbarSelection(6);
	else if (state[SDL_SCANCODE_8])
		toolbar.setToolbarSelection(7);

	
	if (state[SDL_SCANCODE_RIGHT])
	{ 
		toolbar.setToolbarSelection(toolbar.getToolbarSelection() + 1);
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		Item wheat;
		wheat.type.Food = Item::ItemType::isWHEAT;
		player.inventory.add(wheat);
	}
	
	if (state[SDL_SCANCODE_LEFT])
	{
		toolbar.setToolbarSelection(toolbar.getToolbarSelection() - 1);
	}
	if (state[SDL_SCANCODE_UP])
	{
		std::cout << player.inventory.getCurrentSize() << " " << std::endl;
	}

	// Set cell size
	if (state[SDL_SCANCODE_PAGEUP])
	{
		level.setCellSize(level.getCellSize() + 1);
	}
		
	if (state[SDL_SCANCODE_PAGEDOWN] && level.getCellSize() > 1)
	{
		level.setCellSize(level.getCellSize() - 1);
	}
		

	if (state[SDL_SCANCODE_F10])
		level.setTimeOfDay(12.0);
	
	if (state[SDL_SCANCODE_F9])
		level.setTimeOfDay(7.0);

	if (state[SDL_SCANCODE_F])
	{
		//UseItemFromToolbar(player.getCellX(), player.getCellY(), toolbar, player, level, networkManager, gameSettings, renderer);
	}
	// Use Action
	if (toolbar.getSelectedItem().type.Resource != Item::ItemType::noResource)
	{
			//UseItemFromToolbar(player.getCellX(), player.getCellY(), toolbar, player, level, networkManager, gameSettings, renderer);
		int mouseX, mouseY = 0;
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			UseItemFromToolbar(gameSettings.mouseCellPos.x, gameSettings.mouseCellPos.y, toolbar, player, level, networkManager, gameSettings, renderer);
		}
		player.placeItemPos.x = gameSettings.mouseCellPos.x;
		player.placeItemPos.y = gameSettings.mouseCellPos.y;
		gameSettings.displayMouse = true;
	}


	if (state[SDL_SCANCODE_M])
	{
		if(gameSettings.useNetworking)
			networkManager.MapNetworkUpdate(level);
	}
	if (state[SDL_SCANCODE_I])
	{
		if (SDL_GetTicks() / 1000.0 > inventoryTimeout + 100)
		{
			inventoryTimeout = SDL_GetTicks() / 1000.0;
			
		}
		// Close panel
		if (player.InventoryPanel.getDispalayInventory())
		{
			gameSettings.displayMouse = false;
			player.InventoryPanel.setDisplayInventory(false);
			player.InventoryPanel.getInventoryIcons().erase(player.InventoryPanel.getInventoryIcons().begin(), player.InventoryPanel.getInventoryIcons().end());
		}
		//Open Panel
		else
		{
			gameSettings.displayMouse = true;
			player.InventoryPanel.CreateInventory(renderer, player.inventory);
			player.InventoryPanel.setDisplayInventory(true);
		}
	}
	if (state[SDL_SCANCODE_C])
	{
		if (player.craftingUI.getDispalayCrafting())
		{
			gameSettings.displayMouse = false;
			player.craftingUI.setDisplayCrafting(false);
		}
		else
		{
			gameSettings.displayMouse = true;
			player.craftingUI.setDisplayCrafting(true);
		}
	}
	
}


//TODO: Re Implement This.
void UserInput::ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type)
{
	//Check if cell is in bounds
	glm::vec2 chunkPos;
	glm::vec2 actionPos;

	/*
	for (int playerPosX = playerX - cellSize * 2; playerPosX < playerX + cellSize * 2; playerPosX += cellSize)
	{
		for (int playerPosY = playerY - cellSize * 2; playerPosY < playerY + cellSize * 2; playerPosY += cellSize)
		{
			// Calculate the positions around the player to account for changeing of chunks
			int x = playerX / cellSize;
			int y = playerY / cellSize;
			chunkPos.x = (playerPosX / cellSize) / level.getChunkSize();
			chunkPos.y = (playerPosY / cellSize) / level.getChunkSize();


			if (level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isTree)
			{
				Item item;
				item.isWOOD;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isTree = false;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isStoneWall = true;
				level.World[chunkPos.x][chunkPos.y].tiles[actionPos.x][actionPos.y]->isWalkable = true;
				agentManager.allAgents[agentManager.GetAgentNumberFomID(playerName)].inventory.add(item);
			}
		}
	}
	*/
}

void UserInput::UseItemFromToolbar(int xPos, int yPos, ToolBar& toolbar, Player& player, Level& level, NetworkManager& networkManager, GameSettings& gameSettings, SDL_Renderer* renderer)
{
	// AXE
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isWOODAXE)
	{
		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
			{
				if (level.getCell(xPos + x, yPos + y)->isTree)
				{
					//dump celldata of where the player has changed the cell
					level.getCell(xPos + x, yPos + y)->isTree = false;
					level.getCell(xPos + x, yPos + y)->isDirt = true;
					level.getCell(xPos + x, yPos + y)->isWalkable = true;
					std::string seralisedData = level.getCell(xPos + x, yPos + y)->getCellData().dump();
					std::cout << seralisedData << std::endl;
					if (gameSettings.useNetworking)
						networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
					

					for (int i = 0; i < gameSettings.amountOfWoodInTrees; i++)
					{
						Item wood;
						wood.type.Resource = Item::ItemType::isWOOD;
						player.inventory.add(wood);
					}
						

				}
			}
	}
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isPICKAXE)
	{
		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
				if (level.getCell(xPos, yPos)->isRock)
					{
						level.getCell(xPos, player.getCellY())->isRock = false;

						for (int i = 0; i < gameSettings.amountOfStoneInRocks; i++)
						{
							Item stone;
							stone.type.Resource = Item::ItemType::isSTONE;
							player.inventory.add(stone);
						}
					}
	}
	// HOE
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isHOE)
	{
		//level.getCell(xPos + x, yPos + y)->isTree = false;
		if (level.getCell(xPos, yPos)->isDirt == false)
		{
			level.getCell(xPos, yPos)->isDirt = true;
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.getCell(xPos, yPos)->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
	// SCYTHE
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isSCYTHE)
	{
		if (level.getCell(xPos, yPos)->isWheat)
		{
			if (level.getCell(xPos, yPos)->seedsStage == Cell::seedsGrowthStage::PlantStageFour)
			{
				Item wheat;
				wheat.type.Food = Item::ItemType::isWHEAT;
				player.inventory.add(wheat);
			}
			level.getCell(xPos, yPos)->isWheat = false;
			level.getCell(xPos, yPos)->seedsStage = Cell::seedsGrowthStage::PlantStageZero;
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.getCell(xPos, yPos)->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
	// Wheat SEEDS
	if (toolbar.getSelectedItem().type.Food == Item::ItemType::isSEEDS)
	{
		if (level.getCell(xPos, yPos)->isDirt && !level.getCell(xPos, yPos)->isWheat)
		{
			level.getCell(xPos, yPos)->isWheat = true;
			level.getCell(xPos, yPos)->seedsStage = Cell::seedsGrowthStage::PlantStageOne;
			//dump celldata of where the player has changed the cell
			std::string seralisedData = level.getCell(xPos, yPos)->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}

	// FISHING ROD
	if (toolbar.getSelectedItem().type.Tool == Item::ItemType::isFISHINGROD)
	{
		if (level.getCell(player.getCellX() + 2, player.getCellY())->isWater)
		{
			level.getCell(player.getCellX() + 2, player.getCellY())->isFishingBob = true;
		}
		/*
		if (level.getCell(player.getCellX() + 2, player.getCellY())->isWater)
		// Cast Line Right
		else if (level.getCell(player.getCellX() - 2, player.getCellY())->isWater)
			// Cast Line Left
		else if (level.getCell(player.getCellX(), player.getCellY() - 2)->isWater)
			// Cast line up
		else if (level.getCell(player.getCellX(), player.getCellY() + 2)->isWater)
			// Cast line down
			*/
	}
	

	// Place wood on ground
	if (toolbar.getSelectedItem().type.Resource == Item::ItemType::isWOOD)
	{
		//PlaceItemTexture.render(renderer, gameSettings.mouseCellPos.x, gameSettings.mouseCellPos.y, level.getCellSize(), level.getCellSize());
		if (level.getCell(xPos, yPos)->isWood == false)
		{
			level.getCell(xPos, yPos)->isWood = true;
			
			player.inventory.remove(toolbar.getToolbarSelection());
			toolbar.removeToolbarItem(toolbar.getToolbarSelection());
			std::string seralisedData = level.getCell(xPos, yPos)->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
	if (toolbar.getSelectedItem().type.Resource == Item::ItemType::isSTONEWALL)
	{
		if (level.getCell(xPos, yPos)->isStoneWall == false)
		{
			level.getCell(xPos, yPos)->isStoneWall = true;

			player.inventory.remove(toolbar.getToolbarSelection());
			toolbar.removeToolbarItem(toolbar.getToolbarSelection());
			std::string seralisedData = level.getCell(xPos, yPos)->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
	if (toolbar.getSelectedItem().type.Resource == Item::ItemType::isWOODFENCE)
	{
		if (level.getCell(xPos, yPos)->isWoodFence == false)
		{
			level.getCell(xPos, yPos)->isWoodFence = true;

			player.inventory.remove(toolbar.getToolbarSelection());
			toolbar.removeToolbarItem(toolbar.getToolbarSelection());
			std::string seralisedData = level.getCell(xPos, yPos)->getCellData().dump();
			std::cout << seralisedData << std::endl;
			if (gameSettings.useNetworking)
				networkManager.sendTCPMessage("[CellData]" + seralisedData + "\n");
		}
	}
	
}