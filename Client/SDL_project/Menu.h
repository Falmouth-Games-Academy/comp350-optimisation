#pragma once
#include "Player.h"
#include "Texture.h"
#include "Camera.h"
#include "Button.h"
#include "GameSettings.h"
class Menu
{
public:
	//! Constructor
	Menu();
	//! Destroctor
	~Menu();

	//! Run main menu loop
	void MainMenu(GameSettings& gameSettings,Level& level, Camera& camera, Player& player, SDL_Renderer* renderer);

	//! Run character screen loop
	void CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, SDL_Renderer* renderer);

	// Set mouse pointer size
	int setCursorSize(int newCursorSize) { return menuCursorSize = newCursorSize; }
private:
	//! To end main menu while loop
	bool displayMainMenu = true;
	//! To end character menu while loop
	bool displayCharacterMenu = true;
	//! Texture locations
	std::string menuTextures = "Resources\\Sprites\\Menu\\";
	std::string colourTextures = "Resources\\Sprites\\Colours\\";

	//! mouse pos and initial cursor size
	int mouseX, mouseY;
	int menuCursorSize = 30;
	bool showColourWheel = false;

	int r = 0;
	int g = 0;
	int b = 0;
	bool changeHair = false, changeEyes = false;
	SDL_Color getColourWheelvalue(SDL_Renderer* renderer, int x, int y);

	//! Stores the menus background texture
	Texture menuBackground;
	Texture rgbWheel;
	//SDL_Surface rgbWheel;

	Texture rgb;

	//! Cursor texture
	Texture cursor;
};

