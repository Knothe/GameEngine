#pragma once
#include <string>
#include <SDL.h>
#undef main
#include "../String.h"
#include "../Image.h"
#include "../Vec2.h"

class Platform
{
private:
	int width;
	int height;
	int scale;
	Uint16 frameTime;
	SDL_Window* window;

	Platform();
	static Platform* ptr;
	void RenderTexture(Image* image, int x, int y, int frame);
	void ReadInit();
	void Initialize(int sizeX, int sizeY, int s, int f, String name);
	void DrawPoint(Vec2 v);
	void DrawPoint(int x, int y);
public:
	static SDL_Renderer* renderer;
	void RenderClear();
	void RenderPresent();
	void RenderImage(Image* image, int x, int y);
	void RenderImage(Image* image, Vec2 pos);
	void RenderImage(Image* image, Vec2 pos, int frame);

	void DrawRect(int x, int y, int w, int h);
	void DrawRect(Vec2 pos, Vec2 size);
	void DrawCircle(Vec2 position, int radius);

	static Platform* GetPtr();
	int GetScale();
	Uint16 GetFrameTime();
	Vec2 GetSize();
	int GetWidth();
	int GetHeight();
	void Close();
	~Platform();
};

