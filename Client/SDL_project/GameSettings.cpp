#include "stdafx.h"
#include "GameSettings.h"


GameSettings::GameSettings()
{
	//Calculate and correct fps
}


GameSettings::~GameSettings()
{
}

void GameSettings::getScreenResolution()
{

	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

		int should_be_zero = SDL_GetCurrentDisplayMode(i, &currentDisplay);

		if (should_be_zero != 0)
			SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

		else
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, currentDisplay.w, currentDisplay.h, currentDisplay.refresh_rate);
		break;
	}
	WINDOW_HEIGHT = currentDisplay.h;
	WINDOW_WIDTH = currentDisplay.w;

}

void GameSettings::CalculateFramesPerSecond()
{
	
	avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	std::cout << avgFPS << std::endl;
	countedFrames++;

}


//TODO: Create a mapdata json file for singleplayer
void GameSettings::savePlayerSettings(Player& player)
{
	
	json playerData = player.getPlayerJson();

	playerSave.open(playerSavePath);
	playerSave << playerData.dump();
	std::cout << "Saved Player settings." << std::endl;
	playerSave.close();
}

void GameSettings::saveLevelData(Level& level)
{
	json levelData;
	json array;
	
	std::cout << "Level Saving.." << std::endl;
	//TODO: calculate explored area
	for (int x = level.xMinExplored + level.getChunkSize(); x < level.xMaxExplored - level.getChunkSize(); x++)
	{
		for (int y = level.yMinExplored + level.getChunkSize(); y < level.yMaxExplored - level.getChunkSize(); y++)
		{
			std::cout << x << " out of " << level.xMaxExplored << std::endl;
			array.push_back(level.getCell(x, y)->getCellData());
		}
	}
	levelData["Level"] = array;

	levelSave.open(levelSavePath);
	levelSave << levelData.dump();
	std::cout << "Level Saved." << std::endl;
	levelSave.close();
}

//TODO: Load game from save
Level GameSettings::loadGameFromSave(Level& level)
{
	Level levelToReturn;
	std::string line;
	std::ifstream readGameSave(levelSavePath);
	if (readGameSave.is_open())
	{
		while (std::getline(readGameSave, line))
		{
			json jsonData = json::parse(line.begin(), line.end());;

			json mapData = jsonData.at("Level");

			// Range-based for loop to iterate through the map data
			for (auto& element : mapData)
			{


				Cell newCell;
				newCell = level.GetCellFromJson(element);
				level.SetCell(newCell.getX(), newCell.getY(), newCell);
			}
		}
	}


	return levelToReturn;
}


Player GameSettings::getPlayerFromSave()
{
	Player existingPlayer;
	std::string line;
	std::ifstream readPlayerSave(playerSavePath);
	if (readPlayerSave.is_open())
	{
		while (std::getline(readPlayerSave, line))
		{
			//saveData = line;
			json jsonData = json::parse(line.begin(), line.end());;
			json playerData = jsonData.at("PlayerData");

				// Player movement
				int x = playerData.at("X").get<int>();
				int y = playerData.at("Y").get<int>();
				int rotation = playerData.at("rotation").get<int>();
				std::string name = playerData.at("name").get<std::string>();
				bool isMoving = playerData.at("isMoving").get<bool>();

				// Player clothes
				int headWear;
				int bodyWear;
				int legWear;

				// Check to see if the data is there
				if (playerData.count("headWear") > 0)
				{
					headWear = playerData.at("headWear").get<int>();
				}
				if (playerData.count("headWear") > 0)
				{
					bodyWear = playerData.at("bodyWear").get<int>();
				}
				if (playerData.count("headWear") > 0)
				{
					legWear = playerData.at("legWear").get<int>();
				}
				
				json hairColour = playerData.at("hairColour");
				int hr = hairColour.at("r").get<int>();
				int hg = hairColour.at("g").get<int>();
				int hb = hairColour.at("b").get<int>();
				json eyeColour = playerData.at("eyeColour");
				int er = eyeColour.at("r").get<int>();
				int eg = eyeColour.at("g").get<int>();
				int eb = eyeColour.at("b").get<int>();
				json bodyColour = playerData.at("bodyColour");
				int br = bodyColour.at("r").get<int>();
				int bg = bodyColour.at("g").get<int>();
				int bb = bodyColour.at("b").get<int>();
				json legsColour = playerData.at("legColour");
				int lr = legsColour.at("r").get<int>();
				int lg = legsColour.at("g").get<int>();
				int lb = legsColour.at("b").get<int>();
				
				existingPlayer.setEyeColour(er, eg, eb);
				existingPlayer.setHairColour(hr, hg, hb);
				existingPlayer.setJacketColour(br, bg, bb);
				existingPlayer.setJeansColour(lr, lg, lb);

				existingPlayer.PlayerClothes.head = (Player::Clothing::HeadWear)headWear;
				existingPlayer.PlayerClothes.body = (Player::Clothing::BodyWear)bodyWear;
				existingPlayer.PlayerClothes.leg = (Player::Clothing::LegWear)legWear;
				existingPlayer.setPlayerMoving(isMoving);
		}
		
		readPlayerSave.close();
	}
	return existingPlayer;
}