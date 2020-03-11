#include "Platform.h"
#include "GameManager.h"
#include "SDL_ttf.h"
#include "StackAllocator.h"
#include "Debug.h"
#include <iostream>
#include <fstream>

using std::ifstream;

Platform* Platform::ptr;
SDL_Renderer* Platform::renderer;
/*
If the object isn't started, starts it
@return this pointer
*/
Platform* Platform::GetPtr() {
	if (!ptr) {
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(Platform));
		ptr = new(buf) Platform();
	}
	return ptr;
}
/*
Sets up the Window
*/
Platform::Platform() {
	ReadInit();
	Initialize(864, 640, 3, 70, "");
}

void Platform::Initialize(int sizeX, int sizeY, int s, int f, String name) {
	width = sizeX;
	height = sizeY;
	scale = s;
	frameTime = f;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		Debug::GetPtr()->LogError("SDL_INIT initializing error");
		return;
	}

	window = SDL_CreateWindow(name.GetChar(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		Debug::GetPtr()->LogError("Window initialize error");
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		Debug::GetPtr()->LogError("Renderer initialize error");
		SDL_Quit();
		return;
	}
}

void Platform::ReadInit() {
	ifstream file;
	file.open("matchEngine.ini", std::ios::out);
	if (!file.fail()) {
		file >> width >> height;
	}
	else {
		std::cout << ".ini file not found" << std::endl;
		std::cout << "Starting with default values" << std::endl;
		width = 864;
		height = 640;
	}
	file.close();
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
}

/*
Draws an empty rectangle
@param x: position in x
@param y: position in y
@param w: width of the rect
@param h: height of the rect
*/
void Platform::DrawRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x * scale;
	rect.y = y * scale;
	rect.w = w * scale;
	rect.h = h * scale;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}
/*
Draws an empty rectangle
*/
void Platform::DrawRect(Vec2 pos, Vec2 size) {
	SDL_Rect rect;
	rect.x = pos.x * scale;
	rect.y = pos.y * scale;
	rect.w = size.x * scale;
	rect.h = size.y * scale;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}

void Platform::DrawCircle(Vec2 position, int radius) {
	int x = 0;
	int y = radius;
	int p = 1 - radius;
	do {
		if (p <= 0) {
			x = x + 1;
			p = p + (2 * x) + 3;
		}
		else if (p > 0) {
			x = x + 1;
			y = y - 1;
			p = (2 * x) - (2 * y) + 5 + p;
		}
		DrawPoint(x + position.x, y + position.y);
		DrawPoint(x + position.x, -y + position.y);
		DrawPoint(-x + position.x, y + position.y);
		DrawPoint(-x + position.x, -y + position.y);
		DrawPoint(y + position.x, x + position.y);
		DrawPoint(y + position.x, -x + position.y);
		DrawPoint(-y + position.x, x + position.y);
		DrawPoint(-y + position.x, -x + position.y);
	} while (x <= y);
}
/*
Draws a point on screen
@param v: position
*/
void Platform::DrawPoint(Vec2 v) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(renderer, v.x, v.y);
}

void Platform::DrawPoint(int x, int y) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(renderer, x, y);
}
/*
Clears the Screen
*/
void Platform::RenderClear() {
	SDL_SetRenderDrawColor(renderer, 9, 0, 0, 255);
	SDL_RenderClear(renderer);
}
/*
Presents everything rendered on screen
*/
void Platform::RenderPresent() {
	SDL_RenderPresent(renderer);
}
/*
Translates data for RenderTexture
@param image: pointer to image to render
@param x: position in x
@param y: position in y
*/
void Platform::RenderImage(Image* image, int x, int y) {
	RenderTexture(image, x, y, image->GetFrame());
}
/*
Translates data for RenderTexture
@param image: pointer to image to render
@param pos: position
*/
void Platform::RenderImage(Image* image, Vec2 pos) {
	RenderTexture(image, pos.x, pos.y, image->GetFrame());
}
/*
Translates data for RenderTexture
@param image: pointer to image to render
@param pos: position
@param frame: frame to draw
*/
void Platform::RenderImage(Image* image, Vec2 pos, int frame) {
	RenderTexture(image, pos.x, pos.y, frame);
}
/*
Renders the texture with RenderCopyEx
@param image: pointer to image to render
@param x: position in x
@param y: position in y
@param frame: frame to draw
*/
void Platform::RenderTexture(Image* image, int x, int y, int frame) {
	SDL_Rect dstrect;
	dstrect.x = x * scale;
	dstrect.y = y * scale;
	dstrect.w = image->GetWidth() * scale;
	dstrect.h = image->GetHeight() * scale;
	SDL_Rect srcrect;
	srcrect.x = frame * image->GetWidth();
	srcrect.y = 0;
	srcrect.w = image->GetWidth();
	srcrect.h = image->GetHeight();
	//	SDL_RenderCopyEx(renderer, image->GetTexture(), &srcrect, &dstrect, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderCopy(renderer, image->GetTexture(), &srcrect, &dstrect);
}
/*
@return scale for every image
*/
int Platform::GetScale() {
	return scale;
}
/*
@return time each frame draws
*/
Uint16 Platform::GetFrameTime() {
	return frameTime;
}
/*
@return size of the screen
*/
Vec2 Platform::GetSize() {
	return Vec2(width, height);
}
/*
@return width of the screen
*/
int Platform::GetWidth() {
	return width;
}
/*
@return height of the screen
*/
int Platform::GetHeight() {
	return height;
}
/*
Closes the program
*/
void Platform::Close() {
	delete GameManager::getPtr();
	SDL_Quit();
}

Platform::~Platform() {

}