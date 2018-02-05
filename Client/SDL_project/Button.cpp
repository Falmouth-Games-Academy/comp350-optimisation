#include "stdafx.h"
#include "Button.h"


Button::Button(std::string newText) : buttonText("Ostrich"), text(newText), buttonBackground(buttonTextureLocation + "Grey.png")
{
}
Button::Button(std::string newText, std::string backgroundType) : buttonText("Ostrich"), text(newText), buttonBackground(buttonTextureLocation + backgroundType + ".png")
{

}

Button::~Button()
{
	
}
bool Button::isPressed()
{
	if (isActivated)
	{
		isActivated = false;
		return true;
	}
	else
		return false;
}

void Button::render(SDL_Renderer* renderer, int x, int y, int width, int height)
{
	
	// Set object variables
	SDL_GetMouseState(&tx, &ty);
	if (SDL_GetTicks() / 1000.0 > timeButtonWasPressed + buttonTimeout)
	{
		isActivated = false;
		timeout = false;
		timeButtonWasPressed = 0;
	}

		setX(x), setY(y), setWidth(width), setHeight(height);
		if (tx > getX() - (getWidth() / 2) && tx < getX() + (getWidth() / 2) && ty > getY() - (getHeight() / 2) && ty < getY() + (getHeight() / 2) && !timeout)
		{
			if(mouseOverIncreaseSize)
				setWidth(getWidth() + mouseOverSizeInrease), setHeight(getHeight() + mouseOverSizeInrease);

			// Activate the button if it has been pressed
			if (SDL_GetMouseState(&tx, &ty) & SDL_BUTTON(SDL_BUTTON_LEFT) && !timeout)
			{
				isActivated = true;
				timeButtonWasPressed = SDL_GetTicks() / 1000.0;
				timeout = true;
			}
		}
		
	//Render background
	buttonBackground.alterTransparency(200);
	buttonBackground.render(renderer, getX(), getY(), getWidth(), getHeight());
	
	buttonIcon.setX(getX());
	buttonIcon.setY(getY());
	buttonIcon.setHeight(getHeight());
	buttonIcon.setWidth(getWidth());
	buttonIcon.RenderIcon(renderer);

	// Reduce the size again after rendering if mouse over increase is on 
	if (mouseOverIncreaseSize)
		setWidth(getWidth() - mouseOverSizeInrease), setHeight(getHeight() - mouseOverSizeInrease);
	// If the button has text, render it in the center of the button
	if (text.size() > 0)
		buttonText.render(renderer, text, getX() - (getWidth() / 2), getY() - (getHeight() / 2), getWidth(), getHeight(), buttonTextColour);
}

