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

#ifndef KAIRY_AUDIO_AUDIO_DEVICE_H_INCLUDED
#define KAIRY_AUDIO_AUDIO_DEVICE_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class Sound;
class Music;

class AudioDevice
{
public:
	enum
	{
		FIRST_CHANNEL = 8,
		CHANNELS_COUNT = 24
	};

	static AudioDevice* getInstance();

    bool init();

    void destroy();

    inline bool isInitialized() const { return _initialized; }

	inline int getPlayingChannels() { return _playingChannels; }
	
	std::vector<int> getFreeChannels();
	
	int getFreeChannelsCount() const;
	
	int getPlayingSounds() const;
	
	int getPlayingMusic() const;
	
	void acquireChannels(int count);
	
	void releaseChannels(int count);
	
	void addPlayingSound(Sound* sound);
	
	void addPlayingMusic(Music* music);
	
	void removePlayingSound(Sound* sound);
	
	void removePlayingMusic(Music* music);
	
	void clearPlayingSounds();
	
	void clearPlayingMusic();
	
	AudioDevice(const AudioDevice&) = delete;
	AudioDevice& operator=(const AudioDevice&) = delete;
	virtual ~AudioDevice();
	
private:
	
	AudioDevice(void);
	
	std::vector<Sound*> _playingSounds;
	std::vector<Music*> _playingMusic;

    bool _initialized;
	int _playingChannels;

#ifndef _3DS
	ALCdevice* _alDevice;
	ALCcontext* _alContext;
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_AUDIO_AUDIO_DEVICE_H_INCLUDED
