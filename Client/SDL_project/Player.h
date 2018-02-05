#pragma once
#include "Character.h"
#include "Animation.h"
#include "Items.h"
#include "GUI.h"
#include "InventoryUI.h"
#include "CraftingUI.h"
class Player : public Character
{
public:
	Player();
	~Player();
	
	//! Render the player
	void RenderPlayer(SDL_Renderer* renderer, Camera& camera);
	//! Renders the characters clothes
	void renderCharacterClothes(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize);

	json getPlayerJson();
	
	glm::vec2 renderOffset;
	glm::vec2 screenCenter;
	glm::vec2 placeItemPos;
	int xOffset, yOffset;

	//! Player clothes
	Clothing PlayerClothes;
	InventoryUI InventoryPanel;
	CraftingUI craftingUI;
	

	Animation getWalkAnimation() { return walkHorizontalAnimation; }
	SDL_Color gethairColour() { return hairColour; }
	SDL_Color getEyeColour() { return eyeColour; }
	SDL_Color getJacketColour() { return JacketColour; }
	SDL_Color getJeansColour() { return JeansColour; }
	int setHairColour(int r, int g, int b) { return hairColour.r = r, hairColour.g = g, hairColour.b = b; }
	int setEyeColour(int r, int g, int b) { return eyeColour.r = r, eyeColour.g = g, eyeColour.b = b; }
	int setJacketColour(int r, int g, int b) { return JacketColour.r = r, JacketColour.g = g, JacketColour.b = b; }
	int setJeansColour(int r, int g, int b) { return JeansColour.r = r, JeansColour.g = g, JeansColour.b = b; }
	Inventory inventory;
	
private:
	//! Json data to store player stats
	json playerJsondata;
	//! Whether the player is able to move
	bool playerCanMove = true;
	//! Pixel size of the player sprite in the spritesheet
	int pixelSize = 32;
	//! Default colours
	SDL_Color hairColour = { 255,255,255 };
	SDL_Color eyeColour = { 255,255,255 };
	SDL_Color JacketColour = { 255,255,255 };
	SDL_Color JeansColour = { 255,255,255 };
	//! Texture locations
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Sprites\\Character\\Clothes\\";

	//! Texture for the Character
	Texture characterIdleTexture;
	Texture walkTexture;
	Texture sideBlinkTexture;
	Texture shortHairTexture;
	Texture longHairTexture;
	Texture eyesTexture;
	
	//! Texture for the clothes
	Texture jacketTexture;
	Texture jeansTexture;
	
	//! Animations
	Animation walkHorizontalAnimation;
	Animation walkVerticalAnimation;
	Animation idleAnimation;
	Animation blinkAnimation;

	

};

