#pragma once
#include "Player.h"
#include "Timer.h"
class GameSettings
{
public:
	GameSettings();
	~GameSettings();


	//! initial window settings
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;

	void savePlayerSettings(Player& player);
	void saveLevelData(Level& level);
	Level loadGameFromSave(Level& level);
	Player getPlayerFromSave();

	//! Get screen resolution
	void getScreenResolution();
	//! Calculate FPS
	void CalculateFramesPerSecond();

	//Timer used to update the caption
	Timer fpsTimer;
	float getAverageFPS() { return avgFPS; }
	bool displayFPS = false;


	int amountOfWoodInTrees = 3;
	int amountOfStoneInRocks = 3;

	//! Whether the game is fullscreen
	bool fullscreen = false;
	bool displayMouse = false;
	int mousePointerSize = 25;
	bool mainMenu = true;

	glm::vec2 mouseCellPos;

	//TODO: implement UI scaling
	float UIScale = 1.0;

	//! Whether the game uses networking and false if singleplayer
	bool useNetworking = false;

	//! Whether the game will save the game when it closes
	bool saveLevelOnExit = true;
	bool savePlayerOnExit = true;
	//! Whether the game is running or not
	bool running = true;
	//! stores screen resolution
	SDL_DisplayMode currentDisplay;
	
	
private:

	std::ofstream playerSave;
	std::ofstream levelSave;

	std::string levelSavePath = "Resources\\SaveData\\levelData.txt";
	std::string playerSavePath = "Resources\\SaveData\\playerData.txt";

	//The frames per second timer
	//Timer used to calculate the frames per second
	int frame = 0;
	//Start counting frames per second
	int countedFrames = 0;
	float avgFPS = 0;

};

