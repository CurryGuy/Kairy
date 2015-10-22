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

inline void Emitter::setNumParticles(int particles)
{
	_particles.resize(particles);
}

//=============================================================================

inline int Emitter::getNumParticles() const
{
	return (int)_particles.size();
}

//=============================================================================

inline void Emitter::setDuration(float duration)
{
	_duration = duration;
}

//=============================================================================

inline float Emitter::getDuration() const
{
	return _duration;
}

//=============================================================================

inline void Emitter::setPosition(const Vec2 & position)
{
	_position = position;
}

//=============================================================================

inline void Emitter::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

//=============================================================================

inline void Emitter::setPositionX(float x)
{
	_position.x = x;
}

//=============================================================================

inline void Emitter::setPositionY(float y)
{
	_position.y = y;
}

//=============================================================================

inline Vec2 Emitter::getPosition() const
{
	return _position;
}

//=============================================================================

inline float Emitter::getPositionX() const
{
	return _position.x;
}

//=============================================================================

inline float Emitter::getPositionY() const
{
	return _position.y;
}

//=============================================================================

inline void Emitter::setPositionVar(const Vec2 & positionVar)
{
	_positionVar = positionVar;
}

//=============================================================================

inline void Emitter::setPositionVar(float x, float y)
{
	_positionVar.x = x;
	_positionVar.y = y;
}

//=============================================================================

inline Vec2 Emitter::getPositionVar() const
{
	return _positionVar;
}

//=============================================================================

inline void Emitter::setLifeTime(const Time & lifeTime)
{
	_lifeTime = lifeTime;
}

//=============================================================================

inline Time Emitter::getLifeTime() const
{
	return _lifeTime;
}

//=============================================================================

inline void Emitter::setLifeTimeVar(const Time & lifeTimeVar)
{
	_lifeTimeVar = lifeTimeVar;
}

//=============================================================================

inline Time Emitter::getLifeTimeVar(void) const
{
	return _lifeTimeVar;
}

//=============================================================================

inline void Emitter::setGravity(const Vec2 & gravity)
{
	_gravity = gravity;
}

//=============================================================================

inline Vec2 Emitter::getGravity() const
{
	return _gravity;
}

//=============================================================================

inline void Emitter::setSpeed(const Vec2 & speed)
{
	_speed = speed;
}

//=============================================================================

inline Vec2 Emitter::getSpeed() const
{
	return _speed;
}

//=============================================================================

inline void Emitter::setSpeedVar(float speedVar)
{
	_speedVar = speedVar;
}

//=============================================================================

inline float Emitter::getSpeedVar() const
{
	return _speedVar;
}

//=============================================================================

inline void Emitter::setRotation(float rotation)
{
	_rotation = rotation;
}

//=============================================================================

inline float Emitter::getRotation() const
{
	return _rotation;
}

//=============================================================================

inline void Emitter::setRotationVar(float rotationVar)
{
	_rotationVar = rotationVar;
}

//=============================================================================

inline float Emitter::getRotationVar() const
{
	return _rotationVar;
}

//=============================================================================

inline void Emitter::setRotationSpeed(float rotationSpeed)
{
	_rotationSpeed = rotationSpeed;
}

//=============================================================================

inline float Emitter::getRotationSpeed() const
{
	return _rotationSpeed;
}

//=============================================================================

inline void Emitter::setRotationSpeedVar(float rotationSpeedVar)
{
	_rotationSpeedVar = rotationSpeedVar;
}

//=============================================================================

inline float Emitter::getRotationSpeedVar() const
{
	return _rotationSpeedVar;
}

//=============================================================================

inline void Emitter::setStartSize(float startSize)
{
	_startSize = startSize;
}

//=============================================================================

inline float Emitter::getStartSize() const
{
	return _startSize;
}

//=============================================================================

inline void Emitter::setStartSizeVar(float startSizeVar)
{
	_startSizeVar = startSizeVar;
}

//=============================================================================

inline float Emitter::getStartSizeVar() const
{
	return _startSizeVar;
}

//=============================================================================

inline void Emitter::setEndSize(float endSize)
{
	_endSize = endSize;
}

//=============================================================================

inline float Emitter::getEndSize() const
{
	return _endSize;
}

//=============================================================================

inline void Emitter::setEndSizeVar(float endSizeVar)
{
	_endSizeVar = endSizeVar;
}

//=============================================================================

inline float Emitter::getEndSizeVar() const
{
	return _endSizeVar;
}

//=============================================================================

inline void Emitter::setScale(float scale)
{
	_scale = scale;
}

//=============================================================================

inline float Emitter::getScale() const
{
	return _scale;
}

//=============================================================================

inline void Emitter::setScaleVar(float scaleVar)
{
	_scaleVar = scaleVar;
}

//=============================================================================

inline float Emitter::getScaleVar() const
{
	return _scaleVar;
}

//=============================================================================

inline void Emitter::setStartColor(const Color & startColor)
{
	_startColor = startColor;
}

//=============================================================================

inline void Emitter::setEndColor(const Color & endColor)
{
	_endColor = endColor;
}

//=============================================================================

inline Color Emitter::getStartColor() const
{
	return _startColor;
}

//=============================================================================

inline Color Emitter::getEndColor() const
{
	return _endColor;
}

//=============================================================================

inline void Emitter::setTextureIndex(int textureIndex)
{
	_textureIndex = textureIndex;
}

//=============================================================================

inline int Emitter::getTextureIndex() const
{
	return _textureIndex;
}

//=============================================================================

inline void Emitter::setTextureIndexVar(int textureIndexVar)
{
	_textureIndexVar = textureIndexVar;
}

//=============================================================================

inline int Emitter::getTextureIndexVar() const
{
	return _textureIndexVar;
}

//=============================================================================

inline void Emitter::clearTextures()
{
	_textures.clear();
}

//=============================================================================
