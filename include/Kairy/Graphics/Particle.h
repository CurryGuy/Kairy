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

#ifndef KAIRY_GRAPHICS_PARTICLE_H_INCLUDED
#define KAIRY_GRAPHICS_PARTICLE_H_INCLUDED

#include <Kairy/Math/Vec2.h>
#include <Kairy/System/Time.h>
#include "Color.h"

NS_KAIRY_BEGIN

class Particle
{
public:

	inline Particle(void);

	inline Particle(const Time& life);

	inline Color getColor() const;

	inline void setColor(const Color& color);

	inline void setColor(byte r, byte g, byte b, byte a = Color::OPAQUE);

	inline void setOpacity(byte opacity);

	inline byte getOpacity() const;

	inline void setScale(float scale);

	inline float getScale() const;

	inline void setPosition(const Vec2& position);

	inline void setPosition(float x, float y);

	inline void setPositionX(float x);

	inline void setPositionY(float y);

	inline Vec2 getPosition() const;

	inline float getPositionX() const;

	inline float getPositionY() const;

	inline void setVelocity(const Vec2& velocity);

	inline void setVelocity(float x, float y);

	inline void setVelocityX(float vx);

	inline void setVelocityY(float vy);

	inline Vec2 getVelocity() const;

	inline float getVelocityX() const;

	inline float getVelocityY() const;

	inline void setRotation(float rotation);

	inline float getRotation() const;

	inline void setRotationSpeed(float speed);

	inline float getRotationSpeed() const;

	inline void setTextureIndex(int index);

	inline int getTextureIndex() const;

	inline Time getCurrentTime() const;

	inline Time getLifeTime() const;

private:
	friend class Emitter;

	Color _color;
	float _scale;
	Vec2 _position;
	Vec2 _velocity;
	float _rotation;
	float _rotationSpeed;
	int _textureIndex;
	Time _curLife;
	Time _life;
};

#include "Particle.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_PARTICLE_H_INCLUDED
