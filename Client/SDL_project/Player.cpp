#include "stdafx.h"
#include "Player.h"


Player::Player() : characterIdleTexture(characterTextureLocation + "idle.png"), 
shortHairTexture(clothesTextureLocation + "hair1.png"), longHairTexture(clothesTextureLocation + "hair2.png"),
eyesTexture(characterTextureLocation + "eyesAnim.png"), walkTexture(characterTextureLocation + "walk.png"), sideBlinkTexture(characterTextureLocation + "sideBlink.png"),
jacketTexture(clothesTextureLocation + "Jacket.png"), jeansTexture(clothesTextureLocation + "Legs.png")
{
}


Player::~Player()
{
}

void Player::RenderPlayer(SDL_Renderer* renderer, Camera& camera)
{
	walkHorizontalAnimation.maxFrames = 4;
	walkVerticalAnimation.maxFrames = 2;
	idleAnimation.maxFrames = 4;
	walkVerticalAnimation.setFrameRate(150);
	blinkAnimation.maxFrames = 4;
	blinkAnimation.setFrameRate(200);
	blinkAnimation.oscillate = true;


	if (isPlayerMoving())
	{
		walkHorizontalAnimation.OnAnimate();
		walkVerticalAnimation.OnAnimate();
	}
	else
	{
		idleAnimation.OnAnimate();
	}

	// Fixed a weird bug
	renderOffset.x = getX() - camera.getX();
	renderOffset.y = getY() - camera.getY();

	// Alter clothes colors
	shortHairTexture.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
	longHairTexture.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
	jacketTexture.alterTextureColour(JacketColour.r, JacketColour.g, JacketColour.b);
	jeansTexture.alterTextureColour(JeansColour.r, JeansColour.g, JeansColour.b);
	eyesTexture.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
	sideBlinkTexture.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);


	/// RENDER ROTATIONS ///
	//Walk Down
	if (getTargetRotation() == 0 || getTargetRotation() == 360)
	{
		if (isPlayerMoving())
		{
			walkTexture.renderAnim(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 2, renderOffset.x, renderOffset.y, pixelSize, getSize());
			renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 2, renderOffset.x, renderOffset.y, pixelSize, getSize());
		}
			
		else
		{
			walkTexture.renderAnim(renderer, pixelSize * 3, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize());
			renderCharacterClothes(renderer, pixelSize * 3, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize());
		}
			
		eyesTexture.renderAnim(renderer, blinkAnimation.getCurrentFrame() * pixelSize, pixelSize * 2, renderOffset.x, renderOffset.y, pixelSize, getSize());
		//renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 2, renderOffset.x, renderOffset.y, pixelSize, getSize());
	}
	// Walk Left
	else if (getTargetRotation() == 90)
	{
		walkTexture.renderAnim(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, pixelSize, renderOffset.x, renderOffset.y, pixelSize, getSize());
		sideBlinkTexture.renderAnim(renderer, blinkAnimation.getCurrentFrame() * pixelSize, pixelSize, renderOffset.x, renderOffset.y, pixelSize, getSize());
		renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, pixelSize, renderOffset.x, renderOffset.y, pixelSize, getSize());
	}
	// Walk Right
	else if (getTargetRotation() == 270)
	{
		walkTexture.renderAnim(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, 0, renderOffset.x, renderOffset.y, pixelSize, getSize());
		sideBlinkTexture.renderAnim(renderer, blinkAnimation.getCurrentFrame() * pixelSize, 0, renderOffset.x, renderOffset.y, pixelSize, getSize());
		renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, 0, renderOffset.x, renderOffset.y, pixelSize, getSize());
	}
	else if (getTargetRotation() == 180)
	{
		walkTexture.renderAnim(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize());
		renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize());
	}
}

void Player::renderCharacterClothes(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize)
{


	//Render leg wear
	switch (PlayerClothes.leg)
	{
	case Clothing::chinos:

		break;

	case Clothing::jeans:
		jeansTexture.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize);
		break;

	case Clothing::skirt:

		break;
	}

	//Render body
	switch (PlayerClothes.body)
	{
	case Clothing::jacket:
		jacketTexture.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize);
		break;
	case Clothing::dress:

		break;

	case Clothing::tshirt:
		jacketTexture.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize);

		break;
	}

	//Render head wear texture
	switch (PlayerClothes.head)
	{
	case Clothing::shortHair:
		shortHairTexture.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize);
		break;
	case Clothing::longHair:
		longHairTexture.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize);
		break;
	}
}
json Player::getPlayerJson()
{
	json playerData;
	playerData["PlayerData"]["name"] = getID();
	playerData["PlayerData"]["rotation"] = getTargetRotation();
	playerData["PlayerData"]["X"] = getX();
	playerData["PlayerData"]["Y"] = getY();
	playerData["PlayerData"]["isMoving"] = isPlayerMoving();
	playerData["PlayerData"]["headWear"] = PlayerClothes.head;
	playerData["PlayerData"]["hairColour"]["r"] = gethairColour().r;
	playerData["PlayerData"]["hairColour"]["g"] = gethairColour().g;
	playerData["PlayerData"]["hairColour"]["b"] = gethairColour().b;
	playerData["PlayerData"]["eyeColour"]["r"] = getEyeColour().r;
	playerData["PlayerData"]["eyeColour"]["g"] = getEyeColour().g;
	playerData["PlayerData"]["eyeColour"]["b"] = getEyeColour().b;
	playerData["PlayerData"]["bodyWear"] = PlayerClothes.body;
	playerData["PlayerData"]["bodyColour"]["r"] = getJacketColour().r;
	playerData["PlayerData"]["bodyColour"]["g"] = getJacketColour().g;
	playerData["PlayerData"]["bodyColour"]["b"] = getJacketColour().b;
	playerData["PlayerData"]["legWear"] = PlayerClothes.leg;
	playerData["PlayerData"]["legColour"]["r"] = getJeansColour().r;
	playerData["PlayerData"]["legColour"]["g"] = getJeansColour().g;
	playerData["PlayerData"]["legColour"]["b"] = getJeansColour().b;

	return playerData;
}

