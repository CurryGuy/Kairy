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

#include <Kairy/Graphics/Emitter.h>
#include <Kairy/System/Random.h>

NS_KAIRY_BEGIN

//=============================================================================

Emitter::Emitter(void)
	: _duration(-1)
	, _position(Vec2::Zero)
	, _positionVar(Vec2::Zero)
	, _lifeTime(Time::seconds(1))
	, _lifeTimeVar(Time::Zero)
	, _gravity(Vec2::Zero)
	, _speed(Vec2::UnitY)
	, _speedVar(0.0f)
	, _rotation(0.0f)
	, _rotationVar(0.0f)
	, _rotationSpeed(0.0f)
	, _rotationSpeedVar(0.0f)
	, _startSize(10.0f)
	, _startSizeVar(0.0f)
	, _endSize(10.0f)
	, _endSizeVar(0.0f)
	, _scale(1.0f)
	, _scaleVar(0.0f)
	, _startColor(Color::White)
	, _endColor(Color::White)
	, _textureIndex(-1)
	, _textureIndexVar(0)
{
	_circleShape.setSegments(40);
	_particles.resize(100);
}

//=============================================================================

void Emitter::update(float dt)
{
	for (auto& particle : _particles)
	{
		updateParticle(particle, dt);
	}
}

//=============================================================================

void Emitter::draw()
{
	for (auto& particle : _particles)
	{
		drawParticle(particle);
	}
}

//=============================================================================

void Emitter::resetParticle(Particle& particle)
{
	auto random = Random::getInstance();
	auto randomSign = [random]() {
		return random->nextFloat() * (random->nextBoolean() ? 1.0f : -1.0f);
	};

	particle = Particle(Time::seconds(_lifeTime.asSeconds() + _lifeTimeVar.asSeconds() * randomSign()));

	particle.setPosition(_position + _positionVar * randomSign());
	particle.setRotation(_rotation + _rotationVar * randomSign());
	particle.setRotationSpeed(_rotationSpeed + _rotationSpeedVar * randomSign());
	particle.setScale(_scale + _scaleVar * randomSign());
	particle.setTextureIndex(_textureIndex + int(_textureIndexVar * randomSign()));
	particle.setVelocity(_speed + _speedVar * randomSign());
}

//=============================================================================

void Emitter::drawParticle(const Particle& particle)
{
	if (_textures.empty())
	{
		float delta = particle._curLife.asSeconds() / particle._life.asSeconds();

		_circleShape.setPosition(particle.getPosition());
		_circleShape.setRadius(_startSize + _endSize * delta);
		_circleShape.setColor(particle.getColor());
		_circleShape.setAngle(particle.getRotation());
		_circleShape.setScale(particle.getScale());

		_circleShape.draw();
	}
}

//=============================================================================

void Emitter::updateParticle(Particle& particle, float dt)
{
	if (particle.getCurrentTime() >= particle.getLifeTime())
	{
		resetParticle(particle);
	}
	else
	{
		float delta = particle._curLife.asSeconds() / particle._life.asSeconds();

		particle._position += particle._velocity * dt;
		particle._curLife = particle._curLife + Time::seconds(dt);
		particle._rotation += particle._rotationSpeed * dt;
		particle._color = _startColor.mix(_endColor, delta);
	}
}

//=============================================================================

NS_KAIRY_END
