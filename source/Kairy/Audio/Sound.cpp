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

#include <Kairy/Audio/Sound.h>
#include <Kairy/Audio/AudioDevice.h>
#include <Kairy/Util/Clamp.h>
#include <Kairy/System/ResourceManager.h>

NS_KAIRY_BEGIN

//=============================================================================

Sound::Sound(void)
	: _audio(AudioDevice::getInstance())
	, _channelL(-1)
	, _channelR(-1)
	, _loop(false)
	, _stopped(true)
	, _paused(false)
	, _volume(1.0f)
	, _pan(0.0f)
#ifndef _3DS
	, _alBuffer(0)
	, _alSource(0)
#endif // _3DS
{
#ifndef _3DS
	alGenSources(1, &_alSource);
	alGenBuffers(1, &_alBuffer);
#endif // _3DS
}

//=============================================================================

Sound::Sound(const std::string & filename)
	: Sound()
{
	loadFromFile(filename);
}

//=============================================================================

Sound::Sound(const byte * buffer, Uint32 bufferSize)
	: Sound()
{
	loadFromMemory(buffer, bufferSize);
}

//=============================================================================

Sound::Sound(const std::string & zipfile, const std::string & filename)
	: Sound()
{
	loadFromZip(zipfile, filename);
}

//=============================================================================

Sound::~Sound()
{
	unload();
	
#ifndef _3DS
if (_alSource != 0)
{
	alSourcei(_alSource, AL_BUFFER, 0);
	alDeleteSources(1, &_alSource);
}

if (_alBuffer != 0)
{
	alDeleteBuffers(1, &_alBuffer);
}
#endif // _3DS
}

//=============================================================================

bool Sound::loadFromFile(const std::string & filename)
{
	unload();

	if (!_audio->isInitialized())
	{
		return false;
	}

	if (!_data.load(filename))
	{
		return false;
	}

#ifdef _3DS
	return true;
#else
	return setupFromData();
#endif // _3DS
}

//=============================================================================

bool Sound::loadFromMemory(const byte * buffer, Uint32 bufferSize)
{
	unload();

	if (!_audio->isInitialized())
	{
		return false;
	}

	if (!_data.load(buffer, bufferSize))
	{
		return false;
	}

#ifdef _3DS
	return true;
#else
	return setupFromData();
#endif // _3DS
}

//=============================================================================

bool Sound::loadFromZip(const std::string & zipfile, const std::string & filename)
{
	unload();

	if (!_audio->isInitialized())
	{
		return false;
	}

	if (!_data.load(zipfile, filename))
	{
		return false;
	}

#ifdef _3DS
	return true;
#else
	return setupFromData();
#endif // _3DS
}

//=============================================================================

void Sound::unload()
{
	stop();

	_data.clear();
}

//=============================================================================

void Sound::setVolume(float volume)
{
	_volume = util::clamp(volume, 0.0f, 1.0f);
	
	if(!_audio->isInitialized())
		return;
	
#ifdef _3DS
	u32 vol = CSND_VOL(_volume, _pan);
	CSND_SetVol(_channelL, vol, vol);
	if(getChannels() == 2)
		CSND_SetVol(_channelR, vol, vol);
#else
	alSourcef(_alSource, AL_GAIN, _volume);
#endif // _3DS
}

//=============================================================================

void Sound::setLoop(bool loop)
{
	_loop = loop;
	
	if(!_audio->isInitialized())
		return;

#ifdef _3DS
	u32 val = loop ? SOUND_REPEAT : SOUND_ONE_SHOT;
	CSND_SetLooping(_channelL, val);
	if(getChannels() == 2)
		CSND_SetLooping(_channelR, val);
#else
	alSourcei(_alSource, AL_LOOPING, _loop ? AL_TRUE : AL_FALSE);
#endif // _3DS
}

//=============================================================================

void Sound::setPan(float pan)
{
	_pan = util::clamp(pan, -1.0f, 1.0f);
	
	if(!_audio->isInitialized())
		return;

#ifdef _3DS
	u32 vol = CSND_VOL(_volume, _pan);
	CSND_SetVol(_channelL, vol, vol);
	if(getChannels() == 2)
		CSND_SetVol(_channelR, vol, vol);
#else
	ALfloat sourcePosition[] = { _pan, 0.0f, 0.0f };
	alSourcei(_alSource, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcefv(_alSource, AL_POSITION, sourcePosition);
#endif // _3DS
}

//=============================================================================

void Sound::play()
{
	if (!_audio->isInitialized() ||
		!_stopped ||
		_audio->getFreeChannelsCount() < getChannels())
	{
		return;
	}

#ifdef _3DS
	_channelL = -1;
	_channelR = -1;
	
	auto freeChannels = _audio->getFreeChannels();

	_channelL = freeChannels[0];
	if (getChannels() == 2)
		_channelR = freeChannels[1];

	u32 flags = _loop ? SOUND_REPEAT : SOUND_ONE_SHOT;

	if (_data.getBitsPerSample() == 8)
		flags |= SOUND_FORMAT_8BIT;
	else
		flags |= SOUND_FORMAT_16BIT;
	
	u32* dataLeft = (u32*)_data.getDataLeft();
	u32* dataRight = (u32*)_data.getDataRight();
	Uint32 dataSizeLeft = _data.getDataSizeLeft();
	Uint32 dataSizeRight = _data.getDataSizeRight();

	u8 playing = 0;
	
	csndPlaySound(_channelL, flags, _data.getSampleRate(), _volume, _pan,
			dataLeft, dataLeft, dataSizeLeft);
	csndIsPlaying(_channelL, &playing);
	
	if(!playing)
		CSND_SetPlayState(_channelL, 1);
	
	if (getChannels() == 2)
	{
		csndPlaySound(_channelR, flags, _data.getSampleRate(), _volume, _pan,
			dataRight, dataRight, dataSizeRight);
		
		csndIsPlaying(_channelR, &playing);
		
		if(!playing)
			CSND_SetPlayState(_channelR, 1);
	}

	CSND_UpdateInfo(true);

#else
	alSourcePlay(_alSource);
#endif // _3DS

	_stopped = false;
	_paused = false;
	
	_audio->acquireChannels(getChannels());
	_audio->addPlayingSound(this);
}

//=============================================================================

void Sound::pause()
{
	if(!_audio->isInitialized())
		return;
	
	if (isPlaying())
	{
#ifdef _3DS
		CSND_SetPlayState(_channelL, 0);
		
		if(getChannels() == 2)
			CSND_SetPlayState(_channelR, 0);

		CSND_UpdateInfo(false);
#else
		alSourcePause(_alSource);
#endif // _3DS
		_paused = true;
	}
}

//=============================================================================

void Sound::stop()
{
	if(!_audio->isInitialized())
		return;
	
	if (!_stopped)
	{
#ifdef _3DS
		CSND_SetPlayState(_channelL, 0);

		if(getChannels() == 2)
			CSND_SetPlayState(_channelR, 0);
		
		CSND_UpdateInfo(false);
#else
		alSourceStop(_alSource);
#endif // _3DS
		_stopped = true;

		_channelL = -1;
		_channelR = -1;
		
		_audio->releaseChannels(getChannels());
		_audio->removePlayingSound(this);
	}
}

//=============================================================================

void Sound::resume()
{
	if(!_audio->isInitialized())
		return;
	
	if (_paused)
	{
#ifdef _3DS
		CSND_SetPlayState(_channelL, 1);

		if(getChannels() == 2)
			CSND_SetPlayState(_channelR, 1);
		
		CSND_UpdateInfo(false);
#else
		alSourcePlay(_alSource);
#endif // _3DS
		_paused = false;
	}
	else if (_stopped)
	{
		play();
	}
}

//=============================================================================

bool Sound::isPlaying() const
{
	return !_stopped && !_paused;
}

//=============================================================================

#ifndef _3DS
bool Sound::setupFromData()
{	
	ALenum format;

	if (_data.getBitsPerSample() == 8)
	{
		format = _data.getChannels() == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
	}
	else
	{
		format = _data.getChannels() == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	}

	alSourcef(_alSource, AL_PITCH, 1.0f);
	alSourcef(_alSource, AL_GAIN, _volume);
	alSourcei(_alSource, AL_LOOPING, _loop ? AL_TRUE : AL_FALSE);

	ALfloat sourcePosition[] = { _pan, 0.0f, 0.0f };
	alSourcei(_alSource, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcefv(_alSource, AL_POSITION, sourcePosition);

	alBufferData(_alBuffer, format, _data.getDataLeft(),
		_data.getDataSizeLeft(), _data.getSampleRate());
	alSourcei(_alSource, AL_BUFFER, _alBuffer);

	return true;
}

#endif // _3DS

//=============================================================================

NS_KAIRY_END
