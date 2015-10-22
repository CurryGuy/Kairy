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

//=============================================================================

inline Particle::Particle(void)
	: _color(Color::White)
	, _scale(1.0f)
	, _position(Vec2::Zero)
	, _velocity(Vec2::Zero)
	, _rotation(0.0f)
	, _rotationSpeed(0.0f)
	, _textureIndex(-1)
	, _curLife(Time::Zero)
	, _life(Time::Zero)
{
}

//=============================================================================

inline Particle::Particle(const Time& life)
	: Particle()
{
	_life = life;
}

//=============================================================================

inline Color Particle::getColor() const
{
	return _color;
}

//=============================================================================

inline void Particle::setColor(const Color & color)
{
	_color = color;
}

//=============================================================================

inline void Particle::setColor(byte r, byte g, byte b, byte a)
{
	_color = Color(r, g, b, a);
}

//=============================================================================

inline void Particle::setOpacity(byte opacity)
{
	_color.a = opacity;
}

//=============================================================================

inline byte Particle::getOpacity() const
{
	return _color.a;
}

//=============================================================================

//=============================================================================

inline void Particle::setScale(float scale)
{
	_scale = scale;
}

//=============================================================================

inline float Particle::getScale() const
{
	return _scale;
}

//=============================================================================

inline void Particle::setPosition(const Vec2 & position)
{
	_position = position;
}

//=============================================================================

inline void Particle::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

//=============================================================================

inline void Particle::setPositionX(float x)
{
	_position.x = x;
}

//=============================================================================

inline void Particle::setPositionY(float y)
{
	_position.y = y;
}

//=============================================================================

inline Vec2 Particle::getPosition() const
{
	return _position;
}

//=============================================================================

inline float Particle::getPositionX() const
{
	return _position.x;
}

//=============================================================================

inline float Particle::getPositionY() const
{
	return _position.y;
}

//=============================================================================

inline void Particle::setVelocity(const Vec2 & velocity)
{
	_velocity = velocity;
}

//=============================================================================

inline void Particle::setVelocity(float x, float y)
{
	_velocity.x = x;
	_velocity.y = y;
}

//=============================================================================

inline void Particle::setVelocityX(float vx)
{
	_velocity.x = vx;
}

//=============================================================================

inline void Particle::setVelocityY(float vy)
{
	_velocity.y = vy;
}

//=============================================================================

inline Vec2 Particle::getVelocity() const
{
	return _velocity;
}

//=============================================================================

inline float Particle::getVelocityX() const
{
	return _velocity.x;
}

//=============================================================================

inline float Particle::getVelocityY() const
{
	return _velocity.y;
}

//=============================================================================

inline void Particle::setRotation(float rotation)
{
	_rotation = rotation;
}

//=============================================================================

inline float Particle::getRotation() const
{
	return _rotation;
}

//=============================================================================

inline void Particle::setRotationSpeed(float speed)
{
	_rotationSpeed = speed;
}

//=============================================================================

inline float Particle::getRotationSpeed() const
{
	return _rotationSpeed;
}

//=============================================================================

inline void Particle::setTextureIndex(int index)
{
	_textureIndex = index;
}

//=============================================================================

inline int Particle::getTextureIndex() const
{
	return _textureIndex;
}

//=============================================================================

inline Time Particle::getCurrentTime() const
{
	return _curLife;
}

//=============================================================================

inline Time Particle::getLifeTime() const
{
	return _life;
}

//=============================================================================
