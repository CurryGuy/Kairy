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

#ifndef KAIRY_GRAPHICS_EMITTER_H_INCLUDED
#define KAIRY_GRAPHICS_EMITTER_H_INCLUDED

#include <Kairy/Updatable.h>
#include "Sprite.h"
#include "Particle.h"
#include "CircleShape.h"

NS_KAIRY_BEGIN

class Emitter : public Updatable, public Drawable
{
public:

	Emitter(void);

	inline void setNumParticles(int particles);

	inline int getNumParticles() const;

	inline void setDuration(float duration);

	inline float getDuration() const;

	inline void setPosition(const Vec2& position);

	inline void setPosition(float x, float y);

	inline void setPositionX(float x);

	inline void setPositionY(float y);

	inline Vec2 getPosition() const;

	inline float getPositionX() const;

	inline float getPositionY() const;

	inline void setPositionVar(const Vec2& positionVar);

	inline void setPositionVar(float x, float y);

	inline Vec2 getPositionVar() const;

	inline void setLifeTime(const Time& lifeTime);

	inline Time getLifeTime() const;

	inline void setLifeTimeVar(const Time& lifeTimeVar);

	inline Time getLifeTimeVar(void) const;

	inline void setGravity(const Vec2& gravity);

	inline Vec2 getGravity() const;

	inline void setSpeed(const Vec2& speed);

	inline Vec2 getSpeed() const;

	inline void setSpeedVar(float speedVar);

	inline float getSpeedVar() const;

	inline void setRotation(float rotation);

	inline float getRotation() const;

	inline void setRotationVar(float rotationVar);

	inline float getRotationVar() const;

	inline void setRotationSpeed(float rotationSpeed);

	inline float getRotationSpeed() const;

	inline void setRotationSpeedVar(float rotationSpeedVar);

	inline float getRotationSpeedVar() const;

	inline void setStartSize(float startSize);

	inline float getStartSize() const;

	inline void setStartSizeVar(float startSizeVar);

	inline float getStartSizeVar() const;

	inline void setEndSize(float endSize);

	inline float getEndSize() const;

	inline void setEndSizeVar(float endSizeVar);

	inline float getEndSizeVar() const;

	inline void setScale(float scale);

	inline float getScale() const;

	inline void setScaleVar(float scaleVar);

	inline float getScaleVar() const;

	inline void setStartColor(const Color& startColor);

	inline void setEndColor(const Color& endColor);

	inline Color getStartColor() const;

	inline Color getEndColor() const;

	inline void setTextureIndex(int textureIndex);

	inline int getTextureIndex() const;

	inline void setTextureIndexVar(int textureIndexVar);

	inline int getTextureIndexVar() const;

	void addTexture(const std::string& filename,
		Texture::Location location = Texture::Location::Default);

	void addTexture(const byte* data, Uint32 dataSize,
		Texture::Location location = Texture::Location::Default);

	void addTexture(const byte* pixels, int width, int height,
		Texture::Location location = Texture::Location::Default);

	inline void clearTextures();

	void update(float dt) override;

	void draw() override;

private:
	void resetParticle(Particle& particle);
	void drawParticle(const Particle& particle);
	void updateParticle(Particle& particle, float dt);

	std::vector<Particle> _particles;
	float _duration;
	Vec2 _position;
	Vec2 _positionVar;
	Time _lifeTime;
	Time _lifeTimeVar;
	Vec2 _gravity;
	Vec2 _speed;
	float _speedVar;
	float _rotation;
	float _rotationVar;
	float _rotationSpeed;
	float _rotationSpeedVar;
	float _startSize;
	float _startSizeVar;
	float _endSize;
	float _endSizeVar;
	float _scale;
	float _scaleVar;
	Color _startColor;
	Color _endColor;
	int _textureIndex;
	int _textureIndexVar;
	std::vector<std::unique_ptr<Sprite>> _textures;
	CircleShape _circleShape;
};

#include "Emitter.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_EMITTER_H_INCLUDED
