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

#include <Kairy/Actions/Sequence.h>

NS_KAIRY_BEGIN

//=============================================================================

Sequence::Sequence(const std::vector<std::shared_ptr<Action>>& actions)
	: Action()
{
	_actions = actions;
}

//=============================================================================

void Sequence::start(Node* target)
{
	Action::start(target);

	_curAction = 0;

	if (!_actions.empty())
	{
		_actions.front()->start(_target);
	}
}

//=============================================================================

std::shared_ptr<Sequence> Sequence::create(const std::vector<std::shared_ptr<Action>>& actions)
{
	return std::make_shared<Sequence>(actions);
}

//======================================================================

std::shared_ptr<Sequence> Sequence::create(const std::initializer_list<std::shared_ptr<Action>>& actions)
{
	return std::make_shared<Sequence>(actions);
}

//======================================================================

Sequence::Sequence(const std::initializer_list<std::shared_ptr<Action>>& actions)
	: Action()
	, _actions(actions.begin(), actions.end())
{
}

//=============================================================================

void Sequence::update(float dt)
{
	if (_curAction == _actions.size())
	{
		stop();
	}
	else
	{
		auto& action = _actions[_curAction];

		if (action->isDone())
		{
			_curAction++;

			if (_curAction < _actions.size())
			{
				_actions[_curAction]->start(_target);
			}
		}
		else
		{
			action->update(dt);
		}
	}
}

//=============================================================================

NS_KAIRY_END
