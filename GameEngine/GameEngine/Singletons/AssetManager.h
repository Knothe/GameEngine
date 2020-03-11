#pragma once
#include <SDL.h>
#undef main

#include "../DataStructure/Tree.h"
#include "../Vec2.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "../String.h"

struct ImageValues {
	SDL_Texture* image;
	Vec2 size;
	int frames;
	ImageValues(SDL_Texture* img, Vec2 s, int f) : image(img), size(s), frames(f) {

	}

};

class AssetManager
{
private:
	AssetManager();
	static AssetManager* ptr;
	Tree<String, ImageValues*> textureTree;
	Tree<String, Mix_Music*> mMusic;
	Tree<String, Mix_Chunk*> mSFX;
	Tree<String, TTF_Font*> fontTree;
public:
	static AssetManager* getPtr();
	void AddTexture(String fileName, String id, int frames);
	SDL_Texture* GetTextureData(String id, Vec2& size, int& frames);
	void AddMusic(String fileName, String id);
	void AddSfx(String fileName, String id);
	Mix_Music* GetMusic(String id);
	Mix_Chunk* GetSFX(String id);
	void AddFont(String fileName, String id, int size);
	TTF_Font* GetFont(String id);
	~AssetManager();
};

