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

#ifndef KAIRY_ACTIONS_ANIMATE_H_INCLUDED
#define KAIRY_ACTIONS_ANIMATE_H_INCLUDED

#include "Action.h"
#include <Kairy/Graphics/Animation.h>

NS_KAIRY_BEGIN

class Sprite;

class Animate : public Action
{
public:

	Animate(const Animation& animation);

	virtual void start(Node* target) override;

	virtual void stop() override;

	virtual void update(float dt) override;

	inline Animation& getAnimation() { return _animation; }

private:
	Sprite* _sprite;
	Animation _animation;
};

NS_KAIRY_END

#endif // KAIRY_ACTIONS_ANIMATE_H_INCLUDED
