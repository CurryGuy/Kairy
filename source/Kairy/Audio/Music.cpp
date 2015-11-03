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

#include <Kairy/Audio/Music.h>
#include <Kairy/Audio/AudioDevice.h>
#include <Kairy/Util/Clamp.h>
#include <Kairy/Util/Endian.h>
#include "stb_vorbis.h"

#ifdef _3DS
#define TICKS_PER_SEC 268111856.0
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

Music::Music(void)
	: _audio(AudioDevice::getInstance())
	, _channels(0)
	, _bitsPerSample(0)
	, _channelL(-1)
	, _channelR(-1)
	, _loop(true)
	, _paused(false)
	, _stopped(true)
	, _volume(1.0f)
	, _pan(0.0f)
	, _vorbisStream(nullptr)
	, _wavStream(nullptr)
	, _playingThread([this](void*) { while(!_stopped) update(); })
{
	_samplesBuffer.resize(BUFFER_SIZE);

#ifndef _3DS
	alGenBuffers(NUM_BUFFERS, _alBuffers);
	alGenSources(1, &_alSource);
#endif // _3DS
}

//=============================================================================

Music::Music(const std::string & filename)
	: Music()
{
	load(filename);
}

//=============================================================================

Music::~Music()
{
	unload();

#ifndef _3DS
	alDeleteBuffers(NUM_BUFFERS, _alBuffers);
	alDeleteSources(1, &_alSource);
#endif // _3DS
}

//=============================================================================

bool Music::load(const std::string & filename)
{
	unload();

	_wavStream = fopen(filename.c_str(), "rb");

	if (!_wavStream)
	{
		return false;
	}

	char signature[4];

	fread(signature, 1, 4, _wavStream);

	if (signature[0] == 'R' &&
		signature[1] == 'I' &&
		signature[2] == 'F' &&
		signature[3] == 'F')
	{
		byte intBuffer[4];

		fseek(_wavStream, 22, SEEK_SET);
		fread(intBuffer, 1, 2, _wavStream);
		_channels = util::bytesToUshortLE(intBuffer);

		fseek(_wavStream, 24, SEEK_SET);
		fread(intBuffer, 1, 4, _wavStream);
		_sampleRate = util::bytesToUintLE(intBuffer);

		fseek(_wavStream, 34, SEEK_SET);
		fread(intBuffer, 1, 2, _wavStream);
		_bitsPerSample = util::bytesToUshortLE(intBuffer);

		if ((_channels != 1 && _channels != 2) ||
			(_bitsPerSample != 8 && _bitsPerSample != 16))
		{
			fclose(_wavStream);
			_wavStream = nullptr;
			return false;
		}

		fseek(_wavStream, 44, SEEK_SET);
	}
	else
	{
		fclose(_wavStream);
		_wavStream = nullptr;

		stb_vorbis* stream = stb_vorbis_open_filename(filename.c_str(), nullptr, nullptr);

		if (!stream)
		{
			return false;
		}

		stb_vorbis_info info = stb_vorbis_get_info(stream);

		_vorbisStream = stream;
		_channels = info.channels;
		_sampleRate = info.sample_rate;
		_bitsPerSample = 16;
	}

#ifndef _3DS
	if (_bitsPerSample == 8)
	{
		_alFormat = _channels == 1 ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
	}
	else
	{
		_alFormat = _channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	}
#endif // _3DS

	return true;
}

//=============================================================================

void Music::unload()
{
	stop();

	if (_vorbisStream)
	{
		stb_vorbis_close((stb_vorbis*)_vorbisStream);
		_vorbisStream = nullptr;
	}

	if (_wavStream)
	{
		fclose(_wavStream);
		_wavStream = nullptr;
	}

	_channels = 0;
	_bitsPerSample = 0;
	_sampleRate = 0;
}

//=============================================================================

void Music::setVolume(float volume)
{
	_volume = util::clamp(volume, 0.0f, 1.0f);

#ifndef _3DS
	alSourcef(_alSource, AL_GAIN, _volume);
#endif // _3DS
}

//=============================================================================

void Music::setLoop(bool loop)
{
	_loop = loop;
}

//=============================================================================

void Music::setPan(float pan)
{
	_pan = util::clamp(pan, -1.0f, 1.0f);

#ifndef _3DS
	ALfloat sourcePosition[] = { _pan, 0.0f, 0.0f };
	alSourcei(_alSource, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcefv(_alSource, AL_POSITION, sourcePosition);
#endif // _3DS
}

//=============================================================================

void Music::play()
{
	if (!_audio->isInitialized() ||
		_audio->getFreeChannelsCount() < getChannels() ||
		(!_vorbisStream && !_wavStream) || isPlaying())
		return;

	_playingThread.join();

#ifdef _3DS
	auto freeChannels = _audio->getFreeChannels();

	_channelL = freeChannels[0];
	if (getChannels() == 2)
		_channelR = freeChannels[1];

	u32 flags = SOUND_REPEAT;

	if (getBitsPerSample() == 8)
	{
		flags |= SOUND_FORMAT_8BIT;
	}
	else
	{
		flags |= SOUND_FORMAT_16BIT;
	}

	if (getChannels() == 1)
	{
		_leftBuffer = (u8*)linearAlloc(BUFFER_SIZE);
	}
	else
	{
		_leftBuffer = (u8*)linearAlloc(BUFFER_SIZE / 2);
		_rightBuffer = (u8*)linearAlloc(BUFFER_SIZE / 2);
	}

	Uint32 ret;

	if (_vorbisStream)
	{
		ret = stb_vorbis_get_samples_short_interleaved(
			(stb_vorbis*)_vorbisStream,
			_channels,
			(short*)_leftBuffer,
			BUFFER_SIZE / sizeof(short));
		ret = ret * sizeof(short) * _channels;
	}
	else
	{
		ret = fread(_leftBuffer, 1, BUFFER_SIZE, _wavStream);
	}

	if (ret < BUFFER_SIZE)
	{
		memset(&_leftBuffer[ret], 0, BUFFER_SIZE - ret);
	}

	const Uint32 size = ret / getChannels();

	separateChannels();

	csndPlaySound(_channelL, flags, _sampleRate, _volume, _pan,
		_leftBuffer, _leftBuffer, size);

	u8 playing = 0;
	csndIsPlaying(_channelL, &playing);

	if (!playing)
	{
		CSND_SetPlayState(_channelL, 1);
	}

	if (getChannels() == 2)
	{
		csndPlaySound(_channelR, flags, _sampleRate, _volume, _pan,
			_rightBuffer, _rightBuffer, size);
		
		csndIsPlaying(_channelR, &playing);

		if (!playing)
		{
			CSND_SetPlayState(_channelR, 1);
		}
	}

	CSND_UpdateInfo(true);

	_startTicks = svcGetSystemTick();
	
	_samplesMul = double(_sampleRate) * (_bitsPerSample / 8.0) / TICKS_PER_SEC;
	_bufferPos = ret;
	
#else
	for (int i = 0; i < NUM_BUFFERS; ++i)
	{
		Uint32 ret;

		if (_vorbisStream)
		{
			ret = stb_vorbis_get_samples_short_interleaved(
				(stb_vorbis*)_vorbisStream,
				_channels,
				(short*)&_samplesBuffer[0],
				BUFFER_SIZE / sizeof(short));
			ret = ret * sizeof(short) * _channels;
		}
		else
		{
			ret = fread(&_samplesBuffer[0], 1, BUFFER_SIZE, _wavStream);
		}

		alBufferData(_alBuffers[i], _alFormat, _samplesBuffer.data(),
			ret, _sampleRate);
	}

	alSourceQueueBuffers(_alSource, NUM_BUFFERS, _alBuffers);
	alSourcePlay(_alSource);

#endif // _3DS

	_audio->acquireChannels(getChannels());
	_audio->addPlayingMusic(this);

	_stopped = false;
	_paused = false;

	_playingThread.start();
}

//=============================================================================

void Music::pause()
{
	if (isPlaying())
	{
#ifdef _3DS
		CSND_SetPlayState(_channelL, 0);
		
		if (getChannels() == 2)
			CSND_SetPlayState(_channelR, 0);
		
		CSND_UpdateInfo(false);
#else
		alSourcePause(_alSource);
#endif // _3DS
		_paused = true;
	}
}

//=============================================================================

void Music::stop()
{
	if (isPlaying())
	{
		_stopped = true;

#ifdef _3DS
		CSND_SetPlayState(_channelL, 0);

		if (getChannels() == 2)
			CSND_SetPlayState(_channelR, 0);
		
		CSND_UpdateInfo(true);
		
		linearFree(_leftBuffer);
		if(getChannels() == 2)
			linearFree(_rightBuffer);
		
		_leftBuffer = nullptr;
		_rightBuffer = nullptr;
#else
		alSourceStop(_alSource);
		ALint processed = 0;
		alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &processed);
		ALuint buffers[NUM_BUFFERS];
		alSourceUnqueueBuffers(_alSource, processed, buffers);
#endif // _3DS

		_audio->releaseChannels(getChannels());
		_audio->removePlayingMusic(this);
	}
}

//=============================================================================

void Music::resume()
{
	if(!_audio->isInitialized())
		return;
	
	if (_paused)
	{
#ifdef _3DS
		CSND_SetPlayState(_channelL, 1);

		if (getChannels() == 2)
			CSND_SetPlayState(_channelR, 1);

		CSND_UpdateInfo(false);
#else
		alSourcePlay(_alSource);
#endif // _3DS
		_paused = false;
	}
	else if(_stopped)
	{
		play();
	}
}

//=============================================================================

bool Music::isPlaying() const
{
	return !_stopped && !_paused;
}

//=============================================================================

void Music::update()
{
	if ((!_vorbisStream && !_wavStream))
		return;

#ifdef _3DS
	double samplePos = double(svcGetSystemTick() - _startTicks) * _samplesMul;
	
	if(samplePos >= (double(_bufferPos) / double(_channels)))
	{
		Uint32 ret;

		if (_vorbisStream)
		{
			ret = stb_vorbis_get_samples_short_interleaved(
				(stb_vorbis*)_vorbisStream,
				_channels,
				(short*)&_samplesBuffer[0],
				BUFFER_SIZE / sizeof(short));
			ret = ret * sizeof(short) * _channels;
		}
		else
		{
			ret = fread(&_samplesBuffer[0], 1, BUFFER_SIZE, _wavStream);
		}

		if (ret < BUFFER_SIZE)
		{
			if (_loop)
			{
				if (_vorbisStream)
					stb_vorbis_seek_start((stb_vorbis*)_vorbisStream);
				else
					fseek(_wavStream, 44, SEEK_SET);
				_bufferPos = 0;
				_startTicks = svcGetSystemTick();
			}
			else
			{
				stop();
				return;
			}
			
			memset(&_samplesBuffer[ret], 0, BUFFER_SIZE - ret);
		}
		
		separateChannels();
		
		_bufferPos += ret;
	}
#else

	ALint processed = 0;
	alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &processed);

	if (processed <= 0)
	{
		return;
	}

	while (processed--)
	{
		Uint32 ret;

		if (_vorbisStream)
		{
			ret = stb_vorbis_get_samples_short_interleaved(
				(stb_vorbis*)_vorbisStream,
				_channels,
				(short*)&_samplesBuffer[0],
				BUFFER_SIZE / sizeof(short));
			ret = ret * sizeof(short) * _channels;
		}
		else
		{
			ret = fread(&_samplesBuffer[0], 1, BUFFER_SIZE, _wavStream);
		}

		if (ret < BUFFER_SIZE)
		{
			if (_loop)
			{
				if (_vorbisStream)
					stb_vorbis_seek_start((stb_vorbis*)_vorbisStream);
				else
					fseek(_wavStream, 44, SEEK_SET);
			}
			else
			{
				stop();
				break;
			}
		}

		ALuint buffer = 0;

		alSourceUnqueueBuffers(_alSource, 1, &buffer);
		alBufferData(buffer, _alFormat, _samplesBuffer.data(), ret, _sampleRate);
		alSourceQueueBuffers(_alSource, 1, &buffer);

		ALint source_state = 0;
		alGetSourcei(_alSource, AL_SOURCE_STATE, &source_state);
		
		if (source_state != AL_PLAYING)
			alSourcePlay(_alSource);
	}
#endif // _3DS
}

#ifdef _3DS

bool Music::separateChannels(void)
{
	if (_channels == 1)
	{
		memcpy(_leftBuffer, _samplesBuffer.data(), BUFFER_SIZE);
	}
	else
	{
		constexpr Uint32 halfSize = BUFFER_SIZE >> 1;

		if (_bitsPerSample == 8)
		{
			Uint32 pos = 0;
			for (Uint32 i = 0; i < halfSize; i += 2)
			{
				_leftBuffer[pos] = _samplesBuffer[i + 0];
				_leftBuffer[pos] = _samplesBuffer[i + 1];
				pos++;
			}
		}
		else
		{
			constexpr Uint32 halfHalfSize = halfSize >> 1;

			for (Uint32 i = 0; i < halfHalfSize; ++i)
			{
				_leftBuffer[i * 2 + 0] = _samplesBuffer[i * 4 + 0];
				_leftBuffer[i * 2 + 1] = _samplesBuffer[i * 4 + 1];
				_rightBuffer[i * 2 + 0] = _samplesBuffer[i * 4 + 2];
				_rightBuffer[i * 2 + 1] = _samplesBuffer[i * 4 + 3];
			}
		}
	}

	return true;
}

#endif // _3DS

//=============================================================================

NS_KAIRY_END
