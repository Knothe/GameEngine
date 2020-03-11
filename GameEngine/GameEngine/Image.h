#pragma once
#include <SDL.h>
#include "Vec2.h"
#include "String.h"

class Image
{
private:
	SDL_Texture* image;
	Vec2 size;
	int totalFrames;
	int actualFrame;

public:
	void Load(String id);
	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();
	int GetFrame();
	int GetTotalFrames();
	void NextFrame();
	Vec2 GetSize();
};

