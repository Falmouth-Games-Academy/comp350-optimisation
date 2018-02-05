#pragma once
#include "GUI.h"
#include "Level.h"
#include "Icon.h"
#include "GameSettings.h"
#include "Texture.h"


class ToolBar : public GUI
{
public:
	ToolBar();
	~ToolBar();

	Item& getSelectedItem();
	
	//! Function that renders the toolbar
	void ToolBar::UpdateAndRenderToolbar(SDL_Renderer* renderer, Player& player, GameSettings& gameSettings);

	std::vector<std::shared_ptr<Icon>> toolbarIcons;

	//! Remove item from toolbar
	bool removeToolbarItem(int index);

	void createToolbar(Player& player, GameSettings& gameSettings);

	int getToolbarSelection() { return toolbarSelection; }
	int setToolbarSelection(int newSelection) { return toolbarSelection = newSelection; }

	int numOfItems;

private:
	Texture selectionTexture;
	std::string toolbarTextureLocation = "Resources\\Sprites\\Toolbar\\";
	int toolbarSelection = 0;
	int numberOfIcons = 10;
	bool toolbarRender = true;

	Texture playerHunger;
	
	

};

