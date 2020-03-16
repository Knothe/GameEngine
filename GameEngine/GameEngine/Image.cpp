#include "Image.h"
#include "Singletons/AssetManager.h"
#include "Singletons/Debug.h"
#include "Singletons/Platform.h"
#include "MessageException.h"

Image::Image(String t, String i, bool a) : Component(t, i, a){

}
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

void Image::Init() {
	actualFrame = 0;
}

void Image::Update() {
	actualFrame++;
	if (actualFrame == totalFrames)
		actualFrame = 0;
}

void Image::Draw(Vec2 position) {
	Platform::GetPtr()->RenderImage(this, position, actualFrame);
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