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

#ifndef TMX_GRAPHICS_ANIMATION_H_INCLUDED
#define TMX_GRAPHICS_ANIMATION_H_INCLUDED

#include <Kairy/System/Time.h>
#include <Kairy/Math/Rect.h>
#include <Kairy/Updatable.h>

NS_KAIRY_BEGIN

class Animation : public Updatable
{
public:

	enum class Type
	{
		Loop,
		PlayOnce,
		Reverse,
		ReverseLoop,
		PingPong
	};

	Animation(void);

	Animation(const Rect& region, const Vec2& frameSize,
		const Time& delay, Type type = Type::Loop);

	Animation(const std::vector<Rect>& frames,
		const Time& delay, Type type = Type::Loop);

	void setFrames(const std::vector<Rect>& frames);

	void setFrames(const Rect& region, const Vec2& frameSize);

	inline void clear(void) { _frames.clear(); }

	inline void addFrame(const Rect& frame) { _frames.push_back(frame); }

	inline void setDelay(const Time& delay) { _delay = delay; }

	inline Time getDelay() const { return _delay; }

	inline Type getType() const { return _type;  }

	inline bool hasPlayedOnce() const { return _playedOnce; }

	int getFrameIndex() const;

	Rect getCurrentFrame() const;

	Rect getFrame(int index) const;

	int getFramesCount() const { return (int)_frames.size();  }

	void setFrameIndex(int index) { _frameIndex = index;  }

	void pause();

	void stop();

	void start();

	void update(float dt) override;

	inline std::vector<Rect>& getFrames() { return _frames; }

public:
	Type _type;
	std::vector<Rect> _frames;
	Time _delay;
	float _animTime;
	int _frameIndex;
	bool _playedOnce;
	bool _paused;
	bool _stopped;
	bool _forward;
};

NS_KAIRY_END

#endif // TMX_GRAPHICS_ANIMATION_H_INCLUDED
