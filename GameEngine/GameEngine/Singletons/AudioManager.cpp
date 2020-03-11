#include "AudioManager.h"
#include "../MessageException.h"
#include "Debug.h"

AudioManager* AudioManager::ptr;
/*
Starts AudioManager variables and Mixer
*/
AudioManager::AudioManager() {
	assetManager = AssetManager::getPtr();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		Debug::GetPtr()->LogError("Mixer Initialize Error");
	}
}
/*
@returns pointer to this object
*/
AudioManager* AudioManager::getPtr() {
	if (!ptr) {
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(AudioManager));
		ptr = new(buf) AudioManager();
	}
	return ptr;
}
/*
Starts a song
@param id: id of the song
@param loops: number of loops
	-1 for infinite
	0 for none
*/
void AudioManager::PlayMusic(String id, int loops) {
	try {
		Mix_PlayMusic(assetManager->GetMusic(id), loops);
	}
	catch (MessageException e) {
		Debug::GetPtr()->LogError(e.what());
	}
}
/*
Pauses current song
*/
void AudioManager::PauseMusic() {
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}
/*
Restarts current song
*/
void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}
/*
Plays a SoundEffect
*/
void AudioManager::PlaySFX(String id, int loops, int channel) {
	try {
		Mix_PlayChannel(channel, assetManager->GetSFX(id), loops);
	}
	catch (MessageException e) {
		Debug::GetPtr()->LogError(e.what());
	}
}
/*
Changes the volume of the music
*/
int AudioManager::VolumeMusic(int vol) {
	return Mix_VolumeMusic(vol); // Use MIX_MAX_VOLUME as a base
}

AudioManager::~AudioManager() {
	assetManager = NULL;
	Mix_Quit();
}