#include "Platform.h"
#include "GameManager.h"
#include "SDL_ttf.h"
#include "StackAllocator.h"
#include "Debug.h"
#include "../MessageException.h"
#include "../FileManipulation.h"

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
	try {
		FileManipulation file("init.ini", true);
		int x = file.GetValueFloat("x");
		int y = file.GetValueInt("y");
		int s = file.GetValueInt("scale");
		float f = file.GetValueFloat("frameTime");
		String name = file.GetValueString("name");
		language = file.GetValueString("language");
		Initialize(x, y, s, f, name);
	}
	catch (...) {
		Initialize();
	}
	isActive = true;
}

void Platform::Initialize() {
	language = String("English");
	String initFile;
	
	initFile += "[int]\n";
	initFile += "x : 200\n";
	initFile += "y : 600\n";
	initFile += "scale : 1\n";
	initFile += "\n[float]\n";
	initFile += "frameTime : 1\n";
	initFile += "\n[string]\n";
	initFile += "name : Program\n";
	initFile += "language : English";

	FileManipulation f;
	f.createFile("init.ini", initFile);
	Initialize(200, 600, 1, 1, "Program");

}

bool Platform::GetActive() {
	return isActive;
}

void Platform::Initialize(int sizeX, int sizeY, int s, int f, String name) {
	width = sizeX;
	height = sizeY;
	scale = s;
	frameTime = 1000/f;
	std::string n = name.toString();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		Debug::GetPtr()->LogError("SDL_INIT initializing error");
		return;
	}

	window = SDL_CreateWindow(n.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		Debug::GetPtr()->LogError("Window initialize error");
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		Debug::GetPtr()->LogFatalError(101);
		return;
	}
	nextTime = SDL_GetTicks();
	lastTime = nextTime;
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
	pos = pos - (size / 2);

	rect.x = pos.x * scale;
	rect.y = pos.y * scale;
	rect.w = size.x * scale;
	rect.h = size.y * scale;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}

void Platform::DrawCircle(Vec2 position, int radius) {
	position = position * scale;
	radius = radius * scale;
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
Checks Event for keyboard and mouse
@param keysDown: pointer for vector for all the keys pressed
@param keysDown: pointer for vector for all the keys up
@param mouseData: pointer to mouse data
*/
void Platform::CheckEvent(List<int>* keysDown, MouseData* mouseData) {
	mouseData->ResetClicks();
	keysDown->clear();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN:
			keysDown->push_back(e.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			mouseData->position.x = e.motion.x;
			mouseData->position.y = e.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)		mouseData->leftButton = true;
			if (e.button.button == SDL_BUTTON_RIGHT)	mouseData->rightButton = true;
			break;
		}
	}
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
	dstrect.w = image->GetWidth() * scale;
	dstrect.h = image->GetHeight() * scale;
	dstrect.x = x * scale - (dstrect.w / 2);
	dstrect.y = y * scale - (dstrect.h / 2);
	
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

String Platform::GetLanguage() {
	return language;
}

void Platform::NextFrame() {
	Uint32 currentTime = SDL_GetTicks();

	while (currentTime < nextTime) {
		currentTime = SDL_GetTicks();
	}

	lastTime = currentTime;
	nextTime = currentTime + frameTime;
}

/*
Closes the program
*/
void Platform::Close() {
	SDL_Quit();
	isActive = false();
}

Platform::~Platform() {

}