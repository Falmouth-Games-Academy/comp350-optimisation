#include "stdafx.h"
#include "ToolBar.h"


ToolBar::ToolBar() : selectionTexture("Resources\\Sprites\\Toolbar\\grey.png"), playerHunger(toolbarTextureLocation + "PlayerHunger.png")
{
	
}


ToolBar::~ToolBar()
{
}
Item& ToolBar::getSelectedItem()
{
	if(toolbarSelection >= toolbarIcons.size())
		return toolbarIcons.at(0)->getIconItem();
	else
		return toolbarIcons.at(toolbarSelection)->getIconItem();
}

bool ToolBar::removeToolbarItem(int index)
{
	if (index < toolbarIcons.size())
	{
		toolbarIcons.erase(toolbarIcons.begin() + index);
		return true;
	}
	else
		return false;
}

void ToolBar::UpdateAndRenderToolbar(SDL_Renderer* renderer, Player& player, GameSettings& gameSettings)
{
	selectionTexture.alterTransparency(150);

	if (toolbarRender)
		for each (auto &icon in toolbarIcons)
			icon->RenderIcon(renderer);

	// IF the inventory has changed reCreate the toolbar
	//TODO: optimise this
	if (numOfItems != player.inventory.getCurrentSize())
	{
		toolbarIcons.erase(toolbarIcons.begin(), toolbarIcons.end());
		createToolbar(player, gameSettings);
		numOfItems = player.inventory.getCurrentSize();
	}

	// Toolbar selection texture
	if (toolbarSelection >= toolbarIcons.size())
		toolbarSelection = 0;
	if (toolbarSelection < 0)
		toolbarSelection = toolbarIcons.size();
	
	if (toolbarSelection < toolbarIcons.size() && toolbarSelection >= 0)
		selectionTexture.render(renderer, toolbarIcons[toolbarSelection]->getX(), toolbarIcons[toolbarSelection]->getY(), toolbarIcons[toolbarSelection]->getWidth(), toolbarIcons[toolbarSelection]->getHeight());
}

void ToolBar::createToolbar(Player& player, GameSettings& gameSettings)
{
	int WW = gameSettings.WINDOW_WIDTH;
	int WH = gameSettings.WINDOW_HEIGHT;
	
	for (int i = 1; i <= numberOfIcons; i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);
		int startX = WW / 2 - (WW / 4);
		int iconSize = WW / 25;
			
		sharedIcon->setX(startX + (i * iconSize));
		sharedIcon->setY(WH - iconSize);
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		toolbarIcons.push_back(sharedIcon);
	}
	for (int i = 0; i < player.inventory.getCurrentSize(); i++)
	{
		if (i < toolbarIcons.size() && i >= 0 && i < player.inventory.getCurrentSize())
			toolbarIcons[i]->setIconItem(player.inventory.get(i));

	}
}

