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

#include <Kairy/System/Thread.h>

NS_KAIRY_BEGIN

class AudioDevice;

class Music
{
public:

	enum
	{
		NUM_BUFFERS = 2,
		BUFFER_SIZE = 8 * 4096
	};

	Music(void);

	Music(const std::string& filename);

	virtual ~Music();

	bool load(const std::string& filename);

	void unload();

	inline Uint16 getChannels() const { return _channels; }

	inline Uint16 getBitsPerSample() const { return _bitsPerSample; }

	inline Uint32 getSampleRate() const { return _sampleRate; }

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
	void update();

	AudioDevice* _audio;

	Uint16 _channels;
	Uint16 _bitsPerSample;
	Uint32 _sampleRate;
	int _channelL;
	int _channelR;
	bool _loop;
	bool _paused;
	bool _stopped;
	float _volume;
	float _pan;

	void* _vorbisStream;
	FILE* _wavStream;

	std::vector<byte> _samplesBuffer;

	Thread _playingThread;

#ifdef _3DS
	bool separateChannels(void);

	byte* _leftBuffer;
	byte* _rightBuffer;
	u64 _startTicks;
	double _samplesMul;
	Uint32 _bufferPos;
#else
	ALuint _alBuffers[NUM_BUFFERS];
	ALuint _alSource;
	ALenum _alFormat;
#endif // _3DS
};

NS_KAIRY_END
