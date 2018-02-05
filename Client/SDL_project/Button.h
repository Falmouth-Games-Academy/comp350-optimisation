#pragma once
#include "GUI.h"
#include "TextUI.h"
#include "Icon.h"
class Button : public GUI
{
public:
	//! Constructor (takes in text for the button) Leave " "" "  for no text
	Button(std::string newText);
	Button(std::string newText, std::string backgroundType);
	//! Destructor
	~Button();
	//! Render the button
	void render(SDL_Renderer* renderer, int x, int y, int width, int height);

	//! Change the buttons text
	std::string setText(std::string newText) { return text = newText; }

	//! If the button should increase size when mouseover
	bool setMouseOverIncreaseSize(int yayOrNay) { return mouseOverIncreaseSize = yayOrNay; }
	int setSizeIncrease(int newSize) { return mouseOverSizeInrease = newSize; }

	//! If the button has been pressed
	bool isPressed();

	Icon getIconItem() { return buttonIcon; }
	Icon setIconItem(Icon newIcon) { return buttonIcon = newIcon; }
	Item setButtonIconItem(Item newItem) { return buttonIcon.setIconItem(newItem); }
	Item getButtonIconItem() { return buttonIcon.getIconItem(); }

private:
	Icon buttonIcon;
	//! Buttons text
	std::string text;
	float timeButtonWasPressed = 0;
	float buttonTimeout = 0.2;
	//! mouse position
	int tx, ty;
	//! if the button is active
	bool isActivated = false;
	bool timeout = false;

	bool mouseOverIncreaseSize = true;
	int mouseOverSizeInrease = 5;
	//! buttons texture location
	std::string buttonTextureLocation = "Resources\\Sprites\\GUI\\buttonTextures\\";
	SDL_Color buttonTextColour = { 255, 255, 255 };
	TextUI buttonText;
	Texture buttonBackground;
};

