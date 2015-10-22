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

#include <Kairy/System/InputManager.h>
#include <Kairy/Scene/SceneManager.h>

NS_KAIRY_BEGIN

//=============================================================================

static std::unique_ptr<InputManager> s_sharedInputManager = nullptr;

//=============================================================================

InputManager* InputManager::getInstance()
{
	if (!s_sharedInputManager)
	{
		s_sharedInputManager.reset(new InputManager());
	}

	return s_sharedInputManager.get();
}

//=============================================================================

InputManager::KeyState::KeyState()
	: pressed(false)
	, released(false)
	, repeated(false)
	, holdTime(0.0f)
{
}

//=============================================================================

bool InputManager::isKeyDown(Keys key)
{
	return _keys[(int)key].pressed;
}

//=============================================================================

bool InputManager::isKeyDown(std::initializer_list<Keys> keys)
{
	for (auto& key : keys)
	{
		if (isKeyDown(key))
			return true;
	}

	return false;
}

//=============================================================================

bool InputManager::isKeyUp(Keys key)
{
	return !_keys[(int)key].pressed;
}

//=============================================================================

bool InputManager::isKeyUp(std::initializer_list<Keys> keys)
{
	for (auto& key : keys)
	{
		if (isKeyUp(key))
			return true;
	}

	return false;
}

//=============================================================================

bool InputManager::isKeyReleased(Keys key)
{
	return _keys[(int)key].released;
}

//=============================================================================

bool InputManager::isKeyReleased(std::initializer_list<Keys> keys)
{
	for (auto& key : keys)
	{
		if (isKeyReleased(key))
			return true;
	}

	return false;
}

//=============================================================================

bool InputManager::isKeyJustPressed(Keys key)
{
	KeyState& keyState = _keys[(int)key];
	return keyState.pressed && !keyState.repeated;
}

//=============================================================================

bool InputManager::isKeyJustPressed(std::initializer_list<Keys> keys)
{
	for (auto& key : keys)
	{
		if (isKeyJustPressed(key))
			return true;
	}

	return false;
}

//=============================================================================

bool InputManager::isKeyHeld(Keys key)
{
	return _keys[(int)key].repeated;
}

//=============================================================================

bool InputManager::isKeyHeld(std::initializer_list<Keys> keys)
{
	for (auto& key : keys)
	{
		if (isKeyHeld(key))
			return true;
	}

	return false;
}

//=============================================================================

bool InputManager::isKeyHeld(Keys key, float time, bool resetTimer)
{
	KeyState& keyState = _keys[(int)key];
	bool held = keyState.repeated && keyState.holdTime >= time;

	if (resetTimer && held)
	{
		keyState.holdTime = 0.0f;
	}

	return held;
}

//=============================================================================

float InputManager::get3DSliderState()
{
#ifdef _3DS
	return (*(float*)0x1FF81080);
#else
	return 0.0f;
#endif // _3DS
}

//=============================================================================

void InputManager::update(float dt)
{
#ifdef _3DS
	hidScanInput();

	u32 keys = hidKeysHeld();

	updateKey(Keys::A, keys & KEY_A, dt);
	updateKey(Keys::B, keys & KEY_B, dt);
	updateKey(Keys::Select, keys & KEY_SELECT, dt);
	updateKey(Keys::Start, keys & KEY_START, dt);

	updateKey(Keys::DPadRight, keys & KEY_DRIGHT, dt);
	updateKey(Keys::DPadLeft, keys & KEY_DLEFT, dt);
	updateKey(Keys::DPadUp, keys & KEY_DUP, dt);
	updateKey(Keys::DPadDown, keys & KEY_DDOWN, dt);

	updateKey(Keys::L, keys & KEY_L, dt);
	updateKey(Keys::R, keys & KEY_R, dt);
	updateKey(Keys::X, keys & KEY_X, dt);
	updateKey(Keys::Y, keys & KEY_Y, dt);
	updateKey(Keys::ZL, keys & KEY_ZL, dt);
	updateKey(Keys::ZR, keys & KEY_ZR, dt);

	updateKey(Keys::CStickRight, keys & KEY_CSTICK_RIGHT, dt);
	updateKey(Keys::CStickLeft, keys & KEY_CSTICK_LEFT, dt);
	updateKey(Keys::CStickUp, keys & KEY_CSTICK_UP, dt);
	updateKey(Keys::CStickDown, keys & KEY_CSTICK_DOWN, dt);

	updateKey(Keys::CPadRight, keys & KEY_CPAD_RIGHT, dt);
	updateKey(Keys::CPadLeft, keys & KEY_CPAD_LEFT, dt);
	updateKey(Keys::CPadUp, keys & KEY_CPAD_UP, dt);
	updateKey(Keys::CPadDown, keys & KEY_CPAD_DOWN, dt);

	updateKey(Keys::Right, keys & KEY_RIGHT, dt);
	updateKey(Keys::Left, keys & KEY_LEFT, dt);
	updateKey(Keys::Up, keys & KEY_UP, dt);
	updateKey(Keys::Down, keys & KEY_DOWN, dt);

	touchPosition tp;
	Vec2 position(-1, -1);
	hidTouchRead(&tp);
	bool touched = keys & KEY_TOUCH;

	if (touched)
		position = Vec2((float)tp.px, (float)tp.py);

	updateTouch(touched, position, dt);

#else
	updateKey(Keys::A, _glfwKeys[GLFW_KEY_A], dt);
	updateKey(Keys::B, _glfwKeys[GLFW_KEY_S], dt);
	updateKey(Keys::Select, _glfwKeys[GLFW_KEY_N], dt);
	updateKey(Keys::Start, _glfwKeys[GLFW_KEY_M], dt);

	updateKey(Keys::DPadRight, _glfwKeys[GLFW_KEY_H], dt);
	updateKey(Keys::DPadLeft, _glfwKeys[GLFW_KEY_F], dt);
	updateKey(Keys::DPadUp, _glfwKeys[GLFW_KEY_T], dt);
	updateKey(Keys::DPadDown, _glfwKeys[GLFW_KEY_G], dt);

	updateKey(Keys::L, _glfwKeys[GLFW_KEY_Q], dt);
	updateKey(Keys::R, _glfwKeys[GLFW_KEY_W], dt);
	updateKey(Keys::X, _glfwKeys[GLFW_KEY_Z], dt);
	updateKey(Keys::Y, _glfwKeys[GLFW_KEY_X], dt);
	updateKey(Keys::ZL, _glfwKeys[GLFW_KEY_E], dt);
	updateKey(Keys::ZR, _glfwKeys[GLFW_KEY_L], dt);

	updateKey(Keys::CStickRight, _glfwKeys[GLFW_KEY_L], dt);
	updateKey(Keys::CStickLeft, _glfwKeys[GLFW_KEY_J], dt);
	updateKey(Keys::CStickUp, _glfwKeys[GLFW_KEY_I], dt);
	updateKey(Keys::CStickDown, _glfwKeys[GLFW_KEY_K], dt);

	updateKey(Keys::CPadRight, _glfwKeys[GLFW_KEY_6], dt);
	updateKey(Keys::CPadLeft, _glfwKeys[GLFW_KEY_4], dt);
	updateKey(Keys::CPadUp, _glfwKeys[GLFW_KEY_8], dt);
	updateKey(Keys::CPadDown, _glfwKeys[GLFW_KEY_5], dt);

	updateKey(Keys::Right, _glfwKeys[GLFW_KEY_RIGHT], dt);
	updateKey(Keys::Left, _glfwKeys[GLFW_KEY_LEFT], dt);
	updateKey(Keys::Up, _glfwKeys[GLFW_KEY_UP], dt);
	updateKey(Keys::Down, _glfwKeys[GLFW_KEY_DOWN], dt);
#endif // _3DS
}

//=============================================================================

#ifndef _3DS
void InputManager::setGlfwKey(int key, bool pressed)
{
	_glfwKeys[key] = pressed;
}
#endif // _3DS

//=============================================================================

void InputManager::updateKey(Keys key, bool pressed, float dt)
{
	KeyState& keyState = _keys[(int)key];

	if (pressed)
	{
		if (keyState.pressed)
		{
			keyState.repeated = true;
			keyState.holdTime += dt;
		}
		else
		{
			keyState.pressed = true;
			SceneManager::getInstance()->onKeyDown(key, dt);
		}
	}
	else if (keyState.released)
	{
		keyState.released = false;
	}
	else if (keyState.pressed)
	{
		keyState = KeyState();
		keyState.released = true;
		SceneManager::getInstance()->onKeyUp(key, dt);
	}
}

//=============================================================================

void InputManager::updateTouch(bool pressed, Vec2 position, float dt)
{
	if (pressed)
	{
		if (_touchDown)
		{
			if (_touchPosition != position)
			{
				SceneManager::getInstance()->onTouchMoved(position, dt);
			}
		}
		else
		{
			SceneManager::getInstance()->onTouchDown(position, dt);
		}

		_prevTouchPosition = _touchPosition;
		_touchPosition = position;
	}
	else if(_touchDown)
	{
		SceneManager::getInstance()->onTouchUp(_touchPosition, dt);
	}

	_touchDown = pressed;
}

//=============================================================================

NS_KAIRY_END
