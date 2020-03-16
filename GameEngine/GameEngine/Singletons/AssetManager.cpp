#include "SDL_image.h"
#include "AssetManager.h"
#include "Platform.h"
#include <fstream>
#include "../MessageException.h"
#include "Debug.h"
#include "StackAllocator.h"

using std::ofstream;
using std::ifstream;

AssetManager* AssetManager::ptr;

AssetManager::AssetManager() {
	if (TTF_Init())
		std::cout << "TTF_Init" << std::endl;
}
/*
If pointer is null, instanciates the object
@return pointer of this object
*/
AssetManager* AssetManager::getPtr() {
	if (!ptr) {
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(AssetManager));
		ptr = new(buf) AssetManager();
	}
	return ptr;
}
/*
Adds a texture to the tree
@param fileName: name of the texture to add
@param id: id for the position in tree
@param frames: frames in the texture
*/
void AssetManager::AddTexture(String fileName, String id, int frames) {
	try {
		if (textureTree.find(id))
			return;
		std::string name = "../../Assets/Images/" + fileName.toString();
		SDL_Surface* loadedSurface = IMG_Load(name.c_str());
		Vec2 size;
		size.x = loadedSurface->w / frames;
		size.y = loadedSurface->h;
		textureTree.insert(id,
			new ImageValues(SDL_CreateTextureFromSurface(Platform::renderer, loadedSurface),
				size, frames));
	}
	catch (std::exception e) {
		std::string s = "SDL Error: ";
		s += e.what();
		Debug::GetPtr()->LogError(s);
	}
	catch (int e) {
		Debug::GetPtr()->LogError(e);
	}

}
/*
Sets values in the image for image use
@param id: id of the image in tree
@param size: variable for the size of the image
@param frames: variable for the number of frames
@return pointer to the texture
*/
SDL_Texture* AssetManager::GetTextureData(String id, Vec2& size, int& frames) {
	ImageValues* img = textureTree.GetValue(id);
	if (img) {
		size = img->size;
		frames = img->frames;
		return img->image;
	}
	else
		throw 302;
}
/*
@param id: id of the music in tree
@return pointer to the Music variable
*/
Mix_Music* AssetManager::GetMusic(String id) {
	Mix_Music* music = mMusic.GetValue(id);
	if (music)
		return music;
	else 
		throw 303;
}
/*
@param id: id of the sfx in tree
@return pointer to the sfx variable
*/
Mix_Chunk* AssetManager::GetSFX(String id) {
	Mix_Chunk* sfx = mSFX.GetValue(id);
	if (sfx)
		return sfx;
	else 
		throw 304;
}
/*
Adds a song to the tree
@param fileName: name of the song file
@param id: id for the song in tree
*/
void  AssetManager::AddMusic(String fileName, String id) {
	if (mMusic.find(id))
		return;
	std::string name = "../../Assets/Music/" + fileName.toString();
	Mix_Music* m = Mix_LoadMUS(name.c_str());
	if (m)
		mMusic.insert(id, Mix_LoadMUS(name.c_str()));
	else {
		std::string s = "SDL Error: ";
		s += Mix_GetError();
		Debug::GetPtr()->LogError(s);
	}
}
/*
Adds a sfx to the tree
@param fileName: name of the sfx file
@param id: id for the sfx in tree
*/
void  AssetManager::AddSfx(String fileName, String id) {
	if (mSFX.find(id))
		return;
	std::string name = "../../Assets/SFX/" + fileName.toString();
	mSFX.insert(id, Mix_LoadWAV(name.c_str()));
}
/*
Adds a font to the tree
@param fileName: Name of the file
@param id: id of the Font
@param size: Size of the font
*/
void AssetManager::AddFont(String fileName, String id, int size) {
	if (fontTree.find(id))
		return;
	std::string name = "../../Assets/TTF/" + fileName.toString();
	TTF_Font* font = TTF_OpenFont(name.c_str(), size);
	if (font)
		fontTree.insert(id, font);
	else
		Debug::GetPtr()->LogError(305);
}
/*
@return font
*/
TTF_Font* AssetManager::GetFont(String id) {
	TTF_Font* t = fontTree.GetValue(id);
	if (t)
		return t;
	else
		throw 306;
}


AssetManager::~AssetManager() {
	TTF_Quit();
}

