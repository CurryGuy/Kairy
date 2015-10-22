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

#ifndef KAIRY_AUDIO_SOUND_H_INCLUDED
#define KAIRY_AUDIO_SOUND_H_INCLUDED

#include "SoundData.h"

NS_KAIRY_BEGIN

class AudioDevice;

class Sound
{
public:

	Sound(void);

	Sound(const std::string& filename);

	Sound(const byte* buffer, Uint32 bufferSize);

	Sound(const std::string& zipfile, const std::string& filename);

	virtual ~Sound();

	bool loadFromFile(const std::string& filename);

	bool loadFromMemory(const byte* buffer, Uint32 bufferSize);

	bool loadFromZip(const std::string& zipfile, const std::string& filename);

	void unload();

	inline Uint16 getChannels() const { return _data.getChannels(); }

	inline Uint32 getSampleRate() const { return _data.getSampleRate(); }

	void setVolume(float volume);

	inline float getVolume() const { return _volume; }

	void setLoop(bool loop);

	inline bool getLoop() const { return _loop; }

	void setPan(float pan);

	inline float getPan() const { return _pan; }

	void play();
	
	void pause();
	
	void stop();

	void resume();

	bool isPlaying() const;

private:
	AudioDevice* _audio;

	SoundData _data;

	int _channelL;
	int _channelR;
	bool _loop;
	bool _stopped;
	bool _paused;
	float _volume;
	float _pan;

	std::string _resourceName;

#ifndef _3DS
	bool setupFromData();

	ALuint _alBuffer;
	ALuint _alSource;
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_AUDIO_SOUND_H_INCLUDED
