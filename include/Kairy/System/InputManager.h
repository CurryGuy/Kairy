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

#ifndef KAIRY_SYSTEM_INPUT_MANAGER_H_INCLUDED
#define KAIRY_SYSTEM_INPUT_MANAGER_H_INCLUDED

#include <Kairy/Math/Vec2.h>

NS_KAIRY_BEGIN

enum class Keys
{
	A,
	B,
	Select,
	Start,
	DPadRight,
	DPadLeft,
	DPadUp,
	DPadDown,
	L,
	R,
	X,
	Y,
	ZL,
	ZR,
	CStickRight,
	CStickLeft,
	CStickUp,
	CStickDown,
	CPadRight,
	CPadLeft,
	CPadUp,
	CPadDown,
	Right,
	Left,
	Up,
	Down,

	Last = Down
};

class InputManager
{
public:

	static InputManager* getInstance();

	virtual ~InputManager(void) = default;

	bool isKeyDown(Keys key);

	bool isKeyDown(std::initializer_list<Keys> keys);

	bool isKeyUp(Keys key);

	bool isKeyUp(std::initializer_list<Keys> keys);

	bool isKeyReleased(Keys key);

	bool isKeyReleased(std::initializer_list<Keys> keys);

	bool isKeyJustPressed(Keys key);

	bool isKeyJustPressed(std::initializer_list<Keys> keys);

	bool isKeyHeld(Keys key);

	bool isKeyHeld(std::initializer_list<Keys> keys);

	bool isKeyHeld(Keys key, float time, bool resetTimer = false);

	inline bool isTouchDown() const { return _touchDown; }

	inline bool isTouchUp() const { return !_touchDown; }

	inline Vec2 getTouchPosition() const { return _touchPosition; }

	float get3DSliderState();

	void update(float dt);

#ifndef _3DS
	void setGlfwKey(int key, bool pressed);
#endif // _3DS

private:

	InputManager(void) = default;
	InputManager(const InputManager&) = default;

	void updateKey(Keys key, bool pressed, float dt);
	void updateTouch(bool pressed, Vec2 position, float dt);

    struct KeyState
    {
        KeyState();

        bool pressed;
        bool released;
        bool repeated;
        float holdTime;
    };

	KeyState _keys[(int)Keys::Last + 1];
	bool _touchDown{ false };
	Vec2 _touchPosition{ -1, -1 };
	Vec2 _prevTouchPosition{ -1, -1 };

#ifndef _3DS
	friend class RenderDevice;
	bool _glfwKeys[65535]{ false };
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_INPUT_MANAGER_H_INCLUDED
