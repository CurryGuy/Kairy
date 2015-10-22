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

#include <Kairy/Audio/SoundData.h>
#include <Kairy/Util/Endian.h>
#include <Kairy/Util/Zip.h>
#include "stb_vorbis.h"

NS_KAIRY_BEGIN

//=============================================================================

SoundData::SoundData()
	: _dataLeft(nullptr)
	, _dataRight(nullptr)
	, _dataSizeLeft(0)
	, _dataSizeRight(0)
	, _channels(0)
	, _sampleRate(0)
	, _bitsPerSample(0)
{
}

//=============================================================================

SoundData::~SoundData()
{
	clear();
}

//=============================================================================

bool SoundData::load(const std::string & filename)
{
	byte signature[4];
	bool isWav = false;

	FILE* fp = fopen(filename.c_str(), "rb");

	if (!fp)
	{
		return false;
	}

	fread(signature, 1, 4, fp);
	fclose(fp);

	if (signature[0] == 'R' &&
		signature[1] == 'I' &&
		signature[2] == 'F' &&
		signature[3] == 'F')
	{
		isWav = true;
	}

	return isWav ? loadWav(filename) : loadOgg(filename);
}

//=============================================================================

bool SoundData::load(const std::string & zipfile, const std::string & filename)
{
	std::vector<byte> data;

	if (!util::GetZipFileData(zipfile, filename, data))
	{
		return false;
	}

	return load(data.data(), data.size());
}

//=============================================================================

bool SoundData::load(const byte * buffer, Uint32 bufferSize)
{
	if (!buffer || bufferSize == 0)
	{
		return false;
	}

	if (buffer[0] == 'R' &&
		buffer[1] == 'I' &&
		buffer[2] == 'F' &&
		buffer[3] == 'F')
	{
		return loadWav(buffer, bufferSize);
	}

	return loadOgg(buffer, bufferSize);
}

//=============================================================================

bool SoundData::loadWav(const std::string & filename)
{
	clear();

	FILE* fp = fopen(filename.c_str(), "rb");

	if (!fp)
	{
		return false;
	}

	byte signature[4];

	fread(signature, 1, 4, fp);

	if (signature[0] != 'R' ||
		signature[1] != 'I' ||
		signature[2] != 'F' ||
		signature[3] != 'F')
	{
		fclose(fp);
		return false;
	}

	Uint32 dataSize;
	Uint32 sampleRate;
	Uint16 channels;
	Uint16 bitsPerSample;

	byte intBuffer[4];

	fseek(fp, 40, SEEK_SET);
	fread(intBuffer, 1, 4, fp);

	dataSize = util::bytesToUintLE(intBuffer);

	fseek(fp, 22, SEEK_SET);
	fread(intBuffer, 1, 2, fp);

	channels = util::bytesToUshortLE(intBuffer);

	fseek(fp, 24, SEEK_SET);
	fread(intBuffer, 1, 4, fp);

	sampleRate = util::bytesToUintLE(intBuffer);

	fseek(fp, 34, SEEK_SET);
	fread(intBuffer, 1, 2, fp);

	bitsPerSample = util::bytesToUshortLE(intBuffer);

	if (dataSize == 0 ||
		(channels != 1 && channels != 2) ||
		(bitsPerSample != 8 && bitsPerSample != 16))
	{
		fclose(fp);
		return false;
	}

	std::vector<byte> rawData(dataSize);

	fseek(fp, 44, SEEK_SET);
	fread(&rawData[0], 1, dataSize, fp);
	fclose(fp);

	if (!separateChannels(rawData.data(), dataSize,
		channels, bitsPerSample))
	{
		return false;
	}

	_channels = channels;
	_bitsPerSample = bitsPerSample;
	_sampleRate = sampleRate;

	return true;
}

//=============================================================================

bool SoundData::loadWav(const byte * buffer, Uint32 bufferSize)
{
	clear();

	if (!buffer || bufferSize == 0)
	{
		return false;
	}

	if (buffer[0] != 'R' ||
		buffer[1] != 'I' ||
		buffer[2] != 'F' ||
		buffer[3] != 'F')
	{
		return false;
	}

	Uint32 dataSize;
	Uint32 sampleRate;
	Uint16 channels;
	Uint16 bitsPerSample;

	dataSize = util::bytesToUintLE(&buffer[40]);
	channels = util::bytesToUshortLE(&buffer[22]);
	sampleRate = util::bytesToUintLE(&buffer[24]);
	bitsPerSample = util::bytesToUshortLE(&buffer[34]);

	if (dataSize == 0 ||
		(channels != 1 && channels != 2) ||
		(bitsPerSample != 8 && bitsPerSample != 16))
	{
		return false;
	}

	std::vector<byte> rawData(dataSize);

	memcpy(&rawData[0], buffer + 44, dataSize);

	if (!separateChannels(rawData.data(), dataSize, channels, bitsPerSample))
	{
		return false;
	}

	_channels = channels;
	_bitsPerSample = bitsPerSample;
	_sampleRate = sampleRate;

	return true;
}

//=============================================================================

bool SoundData::loadOgg(const std::string & filename)
{
	clear();

	short* samples;
	int channels;
	int sample_rate;
	int len;

	len = stb_vorbis_decode_filename(filename.c_str(), &channels, &sample_rate, &samples);

	if (!samples)
	{
		return false;
	}

	Uint32 dataSize = Uint32(len * channels * 2);

	if (!separateChannels((byte*)samples, dataSize, channels, 16))
	{
		free(samples);
		return false;
	}

	free(samples);

	_channels = channels;
	_sampleRate = sample_rate;
	_bitsPerSample = 16;

	return true;
}

//=============================================================================

bool SoundData::loadOgg(const byte * buffer, Uint32 bufferSize)
{
	clear();

	short* samples;
	int channels;
	int sample_rate;
	int len;

	len = stb_vorbis_decode_memory(buffer, (int)bufferSize, &channels, &sample_rate, &samples);

	if (!samples)
	{
		return false;
	}

	Uint32 dataSize = Uint32(len * channels * 2);

	if (!separateChannels((byte*)samples, dataSize, channels, 16))
	{
		free(samples);
		return false;
	}

	free(samples);

	_channels = channels;
	_sampleRate = sample_rate;
	_bitsPerSample = 16;

	return true;
}

//=============================================================================

void SoundData::clear()
{
	if (_dataLeft)
	{
#ifdef _3DS
		linearFree(_dataLeft);
#else
		delete[] _dataLeft;
#endif // _3DS
		_dataLeft = nullptr;
	}

	if (_dataRight)
	{
#ifdef _3DS
		linearFree(_dataRight);
#else
		delete[] _dataRight;
#endif // _3DS
		_dataRight = nullptr;
	}

	_dataSizeLeft = 0;
	_dataSizeRight = 0;
	_channels = 0;
	_sampleRate = 0;
	_bitsPerSample = 0;
}

//=============================================================================

bool SoundData::separateChannels(byte * data, Uint32 dataSize,
	Uint16 channels, Uint16 bitsPerSample)
{
	if (!data || dataSize == 0)
	{
		return false;
	}

#ifdef _3DS

	if (channels == 1)
	{
		_dataLeft = (byte*)linearAlloc(dataSize);

		if (!_dataLeft)
		{
			return false;
		}

		memcpy(_dataLeft, data, dataSize);
		_dataSizeLeft = dataSize;
	}
	else
	{
		Uint32 halfSize = dataSize >> 1;

		_dataLeft = (byte*)linearAlloc(halfSize);

		if (!_dataLeft)
		{
			return false;
		}

		_dataRight = (byte*)linearAlloc(halfSize);

		if (!_dataRight)
		{
			linearFree(_dataLeft);
			return false;
		}

		if (bitsPerSample == 8)
		{
			Uint32 pos = 0;
			for (Uint32 i = 0; i < halfSize; i += 2)
			{
				_dataLeft[pos]  = data[i + 0];
				_dataRight[pos] = data[i + 1];
				pos++;
			}
		}
		else
		{
			Uint32 halfHalfSize = halfSize / 2;

			for (Uint32 i = 0; i < halfHalfSize; ++i)
			{
				_dataLeft[i * 2 + 0] = data[i * 4 + 0];
				_dataLeft[i * 2 + 1] = data[i * 4 + 1];
				_dataRight[i * 2 + 0] = data[i * 4 + 2];
				_dataRight[i * 2 + 1] = data[i * 4 + 3];
			}
		}

		_dataSizeLeft = halfSize;
		_dataSizeRight = halfSize;
	}

#else
	_dataLeft = new byte[dataSize];

	if (!_dataLeft)
	{
		return false;
	}

	memcpy(_dataLeft, data, dataSize);
	_dataSizeLeft = dataSize;
#endif // _3DS

	return true;
}

//=============================================================================

NS_KAIRY_END
