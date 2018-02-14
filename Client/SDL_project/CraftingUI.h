#pragma once
#include "GUI.h"
#include "Button.h"
#include "Inventory.h"
#include "Icon.h"
class CraftingUI :
	public GUI
{
public:
	//! Constructor
	CraftingUI();
	//! Destructor 
	~CraftingUI();
	//! Get and set Icon sizes
	int getIconSize() { return craftingIconSize; }
	int setIconSize(int newSize) { return craftingIconSize = newSize; }
	//! Function to render the menu
	void renderCraftingMenu(SDL_Renderer* renderer, Inventory& playerInventory);
	//! Function that handles what happens when the user presses one of the buttons in the menu
	void CraftingButtonFunctionality(Button& button, Inventory& playerInventory);
	//! Set whether the window is being displayed
	bool getDispalayCrafting() { return displayCrafing; }
	bool setDisplayCrafting(bool newIn) { return displayCrafing = newIn; }
	//! Number of fences that are created when crafting button is clicked
	int numberOfFencesCreatedFromOneResource = 2;
private:
	bool displayCrafing = false;
	int numberOfCraftingItems = 0;
	int craftingIconSize = 25;
	//! Vector of pointers to buttons
	std::vector<std::shared_ptr<Button>> CraftingButtons;
	//! Location of textures
	std::string backgroundTextureLocation = "Resources\\Sprites\\\Toolbar\\";
	//! Background texture for the menu
	Texture backgroundTexture;
	//! Inventory for the crafting list
	Inventory CraftingInventoryList;
	
};

