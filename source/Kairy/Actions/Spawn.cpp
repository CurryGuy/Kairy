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

#include <Kairy/Actions/Spawn.h>

NS_KAIRY_BEGIN

//=============================================================================

Spawn::Spawn(const std::vector<std::shared_ptr<Action>>& actions)
{
	_actions = actions;
}

//=============================================================================

void Spawn::start(Node* target)
{
	Action::start(target);

	for (auto& action : _actions)
	{
		action->start(target);
	}
}

//=============================================================================

std::shared_ptr<Spawn> Spawn::create(const std::vector<std::shared_ptr<Action>>& actions)
{
	return std::make_shared<Spawn>(actions);
}

//======================================================================

std::shared_ptr<Spawn> Spawn::create(const std::initializer_list<std::shared_ptr<Action>>& actions)
{
	return std::make_shared<Spawn>(actions);
}

//======================================================================

Spawn::Spawn(const std::initializer_list<std::shared_ptr<Action>>& actions)
	: _actions(actions.begin(), actions.end())
{
}

//=============================================================================

void Spawn::update(float dt)
{
	bool allDone = true;

	for (auto& action : _actions)
	{
		if (!action->isDone())
		{
			action->update(dt);
			allDone = false;
		}
	}

	if(allDone)	
	{
		stop();
	}
}

//=============================================================================

NS_KAIRY_END
