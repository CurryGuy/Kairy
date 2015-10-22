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

#ifndef KAIRY_AUDIO_SOUND_DATA_H_INCLUDED
#define KAIRY_AUDIO_SOUND_DATA_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class SoundData
{
public:

	SoundData();

	virtual ~SoundData();

	bool load(const std::string& filename);

	bool load(const std::string& zipfile, const std::string& filename);

	bool load(const byte* buffer, Uint32 bufferSize);

	bool loadWav(const std::string& filename);

	bool loadWav(const byte* buffer, Uint32 bufferSize);

	bool loadOgg(const std::string& filename);

	bool loadOgg(const byte* buffer, Uint32 bufferSize);

	void clear();

	inline const byte* getDataLeft() const { return _dataLeft; }

	inline const byte* getDataRight() const { return _dataRight; }

	inline Uint32 getDataSizeLeft() const { return _dataSizeLeft; }

	inline Uint32 getDataSizeRight() const { return _dataSizeRight; }

	inline Uint16 getChannels() const { return _channels; }

	inline Uint16 getSampleRate() const { return _sampleRate; }

	inline Uint16 getBitsPerSample() const { return _bitsPerSample; }

private:
	bool separateChannels(byte* data, Uint32 dataSize,
		Uint16 channels, Uint16 bitsPerSample);

	byte* _dataLeft;
	byte* _dataRight;
	Uint32 _dataSizeLeft;
	Uint32 _dataSizeRight;
	Uint16 _channels;
	Uint16 _sampleRate;
	Uint16 _bitsPerSample;
};

NS_KAIRY_END

#endif // KAIRY_AUDIO_SOUND_DATA_H_INCLUDED
