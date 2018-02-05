#include "stdafx.h"
#include "Texture.h"
#include "InitialisationError.h"

/*
Texture class that manages the rendering of textures in the game
*/
Texture::Texture(const std::string& fileName)
	: fileName(fileName), texture(nullptr)
{
}


Texture::~Texture()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int width, int height)
{
	if (!texture)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());


		if (!texture)
		{
			throw InitialisationError("IMG_LoadTexture failed");
		}
	}

	SDL_Rect dest;
	dest.x = x - width / 2;
	dest.y = y - height / 2;
	dest.w = width;
	dest.h = height;
	
	SDL_RenderCopy(renderer, texture, nullptr, &dest);
}
void Texture::renderRotation(SDL_Renderer* renderer, int x, int y, int width, int height, int angle)
{
	if (!texture)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());


		if (!texture)
		{
			throw InitialisationError("IMG_LoadTexture failed");
		}
	}

	SDL_Rect dest;
	dest.x = x - width / 2;
	dest.y = y - height / 2;
	dest.w = width;
	dest.h = height;

	SDL_RenderCopyEx(renderer, texture, nullptr, &dest, angle, 0, SDL_FLIP_NONE);
}
void Texture::renderAnim(SDL_Renderer* renderer, int sourceX, int sourceY, int destX, int destY, int pixelSize, int renderSize)
{
	if (!texture)
	{
		texture = IMG_LoadTexture(renderer, fileName.c_str());


		if (!texture)
		{
			throw InitialisationError("IMG_LoadTexture failed");
		}
	}
	SDL_Rect srcrect = { sourceX, sourceY, pixelSize, pixelSize };
	SDL_Rect dstrect = { destX, destY, pixelSize, pixelSize };
	dstrect.w = renderSize;
	dstrect.h = renderSize;
	dstrect.x = destX  - dstrect.w / 2;
	dstrect.y = destY - dstrect.h / 2;


	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void Texture::alterTransparency(int transparencyLevel)
{
	SDL_SetTextureAlphaMod(texture, transparencyLevel);
}

void Texture::alterTextureColour(int r, int g, int b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}
