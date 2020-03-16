#pragma once
#include <SDL.h>
#include "Component.h"
#include "Vec2.h"
#include "String.h"

class Image : public Component
{
private:
	SDL_Texture* image;
	Vec2 size;
	int totalFrames;
	int actualFrame;

public:

	Image(String t, String i, bool a);

	void Init();
	void Draw(Vec2 position);
	void Update();

	void Load(String id);
	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();
	int GetTotalFrames();
	Vec2 GetSize();
};

