#include "stdafx.h"
#include "Icon.h"


Icon::Icon() : WoodAxeTexture(iconTextureLocation + "axe.png"), PickAxeTexture(iconTextureLocation + "pickAxe.png"), hoeTexture(iconTextureLocation + "hoe.png"), seedsTexture(iconTextureLocation + "seeds.png"), ScytheTexture(iconTextureLocation + "scythe.png"), WheatTexture(iconTextureLocation + "wheat.png"),
FishingRodTexture(iconTextureLocation + "fishingPole.png"), WateringCanTexture(iconTextureLocation + "wateringCan.png"),
WoodTexture(iconTextureLocation + "wood.png"), StoneTexture(iconTextureLocation + "stone.png"), IconBackgroundTexture(iconTextureLocation + "IconBackground.png"),
WoodFenceTexture(iconTextureLocation + "FenceWood.png"), StoneFenceTexture(iconTextureLocation + "FenceStone.png")
{
}


Icon::~Icon()
{
}

void Icon::RenderIcon(SDL_Renderer* renderer)
{

	if (renderBackground)
	{
		IconBackgroundTexture.alterTransparency(150);
		IconBackgroundTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
	}
	switch (iconItem.type.Tool)
	{
	case Item::ItemType::isWOODAXE:
		WoodAxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isPICKAXE:
		PickAxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isHOE:
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isSCYTHE:
		ScytheTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isFISHINGROD:
		FishingRodTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isWATERINGCAN:
		WateringCanTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	}
	switch (iconItem.type.Food)
	{
	case Item::ItemType::isSEEDS:
		seedsTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isWHEAT:
		WheatTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	}
	switch (iconItem.type.Resource)
	{
	case Item::ItemType::noResource:
		
		break;
	case Item::ItemType::isWOOD:
		WoodTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isSTONE:
		StoneTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isSTONEWALL:
		StoneFenceTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	case Item::ItemType::isWOODFENCE:
		WoodFenceTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		break;
	
	}

	/*
	if(this->iconItem.type.isAxe)
		AxeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
	else if (this->iconItem.type.isHoe)
		hoeTexture.render(renderer, getX(), getY(), getWidth(), getHeight());
		*/
}