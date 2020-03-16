#include "Text.h"
#include "Singletons/Platform.h"
#include "MessageException.h"
#include "Singletons/Debug.h"
/*
Initializes variables
@param pos: position of this text
@param t: message of the text
@param id: id of the font
@param colour: colour of the text
*/
Text::Text(Vec2 pos, String t, String id, SDL_Color colour) :
	text(t), font(id), textColour(colour)
{
	position.x = pos.x;
	position.y = pos.y;
	SetSurface();
}
/*
Sets the surface (SDL_RECT)
*/
void Text::SetSurface() {
	try {

		SDL_Surface* surf = TTF_RenderText_Blended(AssetManager::getPtr()->GetFont(font), text.toString().c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Platform::renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, NULL, NULL, &position.w, &position.h);
	}
	catch (int e) {
		Debug::GetPtr()->LogError(e);
	}
}
/*
Draws the text
*/
void Text::Draw() {
	SDL_RenderCopy(Platform::renderer, labelTexture, nullptr, &position);
}