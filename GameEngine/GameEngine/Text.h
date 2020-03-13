#pragma once
#include "Singletons/AssetManager.h"

class Text
{
private:
	SDL_Rect position;
	String text;
	String font;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
public:
	Text(Vec2 pos, String t, String id, SDL_Color colour);
	void SetSurface();
	void Draw();
};

