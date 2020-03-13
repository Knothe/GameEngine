#include "Image.h"
#include "Singletons/AssetManager.h"
#include "Singletons/Debug.h"
#include "Singletons/Platform.h"
#include "MessageException.h"

/*
Loads a simple image
@param n: name of the image file
*/
void Image::Load(String id) {
	try {
		image = AssetManager::getPtr()->GetTextureData(id, size, totalFrames);
	}
	catch (MessageException e) {
		Debug::GetPtr()->LogError(e.what());
	}
	catch (int e) {
		Debug::GetPtr()->LogError(e);
	}
	actualFrame = 0;
}
/*
@return texture of the image
*/
SDL_Texture* Image::GetTexture() {
	return image;
}
/*
@return height of the texture
*/
int Image::GetHeight() {
	return size.y;
}
/*
@return lenght of the texture
*/
int Image::GetWidth() {
	return size.x;
}
/*
@return current frame
*/
int Image::GetFrame() {
	return actualFrame;
}
/*
Moves animation to the next frame
*/
void Image::NextFrame() {
	actualFrame++;
	if (actualFrame == totalFrames)
		actualFrame = 0;
}
/*
@return vector with the size of the texture
*/
Vec2 Image::GetSize() {
	return size;
}
/*
@return total number of frames
*/
int Image::GetTotalFrames() {
	return totalFrames;
}