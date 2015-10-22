/******************************************************************************
*
* Copyright (C) 2015 Nanni
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*****************************************************************************/

#include <Kairy/Audio/AudioDevice.h>
#include <Kairy/Audio/Sound.h>
#include <Kairy/Audio/Music.h>

NS_KAIRY_BEGIN

//=============================================================================

static std::unique_ptr<AudioDevice> s_sharedAudioDevice = nullptr;

//=============================================================================

AudioDevice * AudioDevice::getInstance()
{
	if (!s_sharedAudioDevice)
	{
		s_sharedAudioDevice.reset(new AudioDevice());
	}

	return s_sharedAudioDevice.get();
}

//=============================================================================

AudioDevice::AudioDevice(void)
	: _initialized(false)
	, _playingChannels(0)
#ifndef _3DS
	, _alDevice(nullptr)
	, _alContext(nullptr)
#endif // _3DS
{
}

//=============================================================================

AudioDevice::~AudioDevice()
{
#ifndef _3DS
	if (_alContext)
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(_alContext);
		_alContext = nullptr;
	}

	if (_alDevice)
	{
		alcCloseDevice(_alDevice);
		_alDevice = nullptr;
	}
#endif // _3DS
}

//=============================================================================

bool AudioDevice::init()
{
	if (_initialized)
	{
		return true;
	}

	destroy();

#ifdef _3DS
	csndInit();
#else
	_alDevice = alcOpenDevice(nullptr);

	if (!_alDevice)
	{
		return false;
	}

	_alContext = alcCreateContext(_alDevice, nullptr);

	if (!_alContext)
	{
		destroy();
		return false;
	}

	if (!alcMakeContextCurrent(_alContext))
	{
		destroy();
		return false;
	}

#endif // _3DS

	_initialized = true;

	return true;
}

//=============================================================================

void AudioDevice::destroy()
{
	if(!_initialized)
		return;
	
	for(auto& sound : _playingSounds)
	{
		if(sound)
		{
			//sound->stop();
		}
	}
	
	for(auto& music : _playingMusic)
	{
		if(music)
		{
			//music->stop();
		}
	}
	
	clearPlayingSounds();
	clearPlayingMusic();
	
#ifdef _3DS
	csndExit();
#endif // _3DS

	_initialized = false;
}

//=============================================================================

std::vector<int> AudioDevice::getFreeChannels()
{
	std::vector<int> freeChannels;
	
#ifdef _3DS
	for (int i = FIRST_CHANNEL; i < FIRST_CHANNEL + CHANNELS_COUNT; ++i)
	{
		u8 playing = 0;
		csndIsPlaying(i, &playing);

		if (!playing)
		{
			freeChannels.push_back(i);
		}
	}
#endif // _3DS
	
	return freeChannels;
}

//=============================================================================

int AudioDevice::getFreeChannelsCount() const
{
	return CHANNELS_COUNT - _playingChannels;
}

//=============================================================================

int AudioDevice::getPlayingSounds() const
{
	return (int)_playingSounds.size();
}

//=============================================================================

int AudioDevice::getPlayingMusic() const
{
	return (int)_playingMusic.size();
}

//=============================================================================

void AudioDevice::acquireChannels(int count)
{
	_playingChannels = std::min((int)CHANNELS_COUNT, _playingChannels + count);
}

//=============================================================================

void AudioDevice::releaseChannels(int count)
{
	_playingChannels = std::max(_playingChannels - count, 0);
}

//=============================================================================

void AudioDevice::addPlayingSound(Sound* sound)
{
	_playingSounds.push_back(sound);
}

//=============================================================================

void AudioDevice::addPlayingMusic(Music* music)
{
	_playingMusic.push_back(music);
}

//=============================================================================

void AudioDevice::removePlayingSound(Sound* sound)
{
	std::vector<Uint32> toRemove;
	
	for(Uint32 i = 0; i < _playingSounds.size(); ++i)
	{
		if(sound == _playingSounds[i])
			toRemove.push_back(i);
	}
	
	for(auto& index : toRemove)
	{
		_playingSounds.erase(_playingSounds.begin() + index);
	}
}

//=============================================================================

void AudioDevice::removePlayingMusic(Music* music)
{
	std::vector<Uint32> toRemove;
	
	for(Uint32 i = 0; i < _playingMusic.size(); ++i)
	{
		if(music == _playingMusic[i])
			toRemove.push_back(i);
	}
	
	for(auto& index : toRemove)
	{
		_playingMusic.erase(_playingMusic.begin() + index);
	}
}

//=============================================================================

void AudioDevice::clearPlayingSounds()
{
	_playingSounds.clear();
}

//=============================================================================

void AudioDevice::clearPlayingMusic()
{
	_playingMusic.clear();
}

//=============================================================================

NS_KAIRY_END
