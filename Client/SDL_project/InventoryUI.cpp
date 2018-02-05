#include "stdafx.h"
#include "InventoryUI.h"


InventoryUI::InventoryUI() : backgroundTexture("Resources\\Sprites\\Toolbar\\InventoryBackground.png"), selectionTexture("Resources\\Sprites\\Toolbar\\InventoryBackground.png")
{
}


InventoryUI::~InventoryUI()
{
}

void InventoryUI::RenderInventory(SDL_Renderer* renderer, Inventory& inventory)
{
	int mX, mY = 0;
	if (displayInventory)
	{
		if (SDL_GetMouseState(&mX, &mY))
		{
		}
		if (numOfInventoryIcons != inventory.getCurrentSize())
		{
			inventoryIcons.erase(inventoryIcons.begin(), inventoryIcons.end());
			CreateInventory(renderer, inventory);
			numOfInventoryIcons = inventory.getCurrentSize();
		}
		else
		{
			backgroundTexture.alterTransparency(150);
			backgroundTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
			
		}
		// Render icons then selection texture over
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		for each (auto &icon in inventoryIcons)
		{
			icon->RenderIcon(renderer);
			if (mX > icon->getX() - (icon->getWidth() / 2) && mX < icon->getX() + (icon->getWidth() / 2))
				if (mY > icon->getY() - (icon->getHeight() / 2) && mY < icon->getY() + (icon->getHeight() / 2))
				{
					selectionTexture.alterTextureColour(selectionColour.r, selectionColour.g, selectionColour.b);
					selectionTexture.alterTransparency(150);
					selectionTexture.render(renderer, icon->getX(), icon->getY(), icon->getWidth(), icon->getHeight());

					// IF selected
					if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_LEFT) && state[SDL_SCANCODE_LSHIFT])
					{

			
					}
				}
			
		}
	}
}
void InventoryUI::CreateInventory(SDL_Renderer* renderer, Inventory& inventory)
{
	int x = getX() - getWidth() / 2 + iconSize;
	int y = getY() - getHeight() / 2 + iconSize * 2;
	for (int i = 0; i < inventory.getCapacity(); i++)
	{
		Icon icon;
		auto sharedIcon = std::make_shared<Icon>(icon);

		if (x > getX() + getWidth() / 2 - iconSize)
		{
			x = getX() - getWidth() / 2 + iconSize;
			y += iconSize;
		}
		sharedIcon->setX(x);
		sharedIcon->setY(y);
		sharedIcon->setWidth(iconSize);
		sharedIcon->setHeight(iconSize);
		sharedIcon->renderBackground = true;
		inventoryIcons.push_back(sharedIcon);
		x += iconSize;
	}

	for (int i = 0; i < inventory.getCurrentSize(); i++)
		inventoryIcons[i]->setIconItem(inventory.get(i));
}