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

#include <Kairy/Actions/Action.h>

NS_KAIRY_BEGIN

//=============================================================================

Action::Action()
	: _done(false)
	, _target(nullptr)
	, _tag(-1)
{
}

//=============================================================================

Action::~Action()
{
}

//=============================================================================

void Action::start(Node* target)
{
	_target = target;
	_done = false;
}

//=============================================================================

void Action::stop(void)
{
	step(1.0f);

	_target = nullptr;
	_done = true;
}

//=============================================================================

void Action::update(float dt)
{
}

//=============================================================================

void Action::step(float dt)
{
}

//=============================================================================

NS_KAIRY_END
