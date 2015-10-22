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

#include <Kairy/Scene/Scene.h>

NS_KAIRY_BEGIN

//=============================================================================

Scene::Scene(void)
	: Node()
{
	_input = InputManager::getInstance();
	_color = Color::Transparent;
	_colorBot = Color::Transparent;
	_addCounterBot = 0;
}

//=============================================================================

Scene::~Scene(void)
{
}

//=============================================================================

void Scene::removeChild(Node * child)
{
	Node::removeChild(child);

	if (child)
	{
		for (Uint32 i = 0; i < _childrenBot.size(); ++i)
		{
			if (_childrenBot[i].get() == child)
			{
				_childrenBot.erase(_childrenBot.begin() + i);
				break;
			}
		}
	}
}

//=============================================================================

void Scene::sortByZOrderBot()
{
	std::sort(_childrenBot.begin(), _childrenBot.end(),
		[](std::shared_ptr<Node>& a, std::shared_ptr<Node>& b)
	{
		return a->getZOrder() < b->getZOrder();
	});
}

//=============================================================================

Node * Scene::getChildByName(const std::string & name) const
{
	for (auto& child : _children)
	{
		if (child->getName() == name)
			return child.get();
	}

	for (auto& child : _childrenBot)
	{
		if (child->getName() == name)
			return child.get();
	}

	return nullptr;
}

//=============================================================================

Node * Scene::getChildByTag(int tag) const
{
	for (auto& child : _children)
	{
		if (child->getTag() == tag)
			return child.get();
	}

	for (auto& child : _childrenBot)
	{
		if (child->getTag() == tag)
			return child.get();
	}

	return nullptr;
}

//=============================================================================

void Scene::clearChildrenBot()
{
	for (auto& child : _childrenBot)
	{
		child->_parent = nullptr;
	}

	_childrenBot.clear();
	_addCounterBot = 0;
}

//=============================================================================

Uint32 Scene::getChildrenCountBot() const
{
	return _childrenBot.size();
}

//=============================================================================

void Scene::removeChildByTag(int tag)
{
	Node::removeChildByTag(tag);

	std::vector<Uint32> toRemove;

	for (Uint32 i = 0; i < _childrenBot.size(); ++i)
	{
		if (_childrenBot[i]->getTag() == tag)
			toRemove.push_back(i);
	}

	for (auto& index : toRemove)
	{
		_childrenBot.erase(_childrenBot.begin() + index);
	}
}

//=============================================================================

void Scene::removeChildByName(const std::string & name)
{
	std::vector<Uint32> toRemove;

	for (Uint32 i = 0; i < _childrenBot.size(); ++i)
	{
		if (_childrenBot[i]->getName() == name)
			toRemove.push_back(i);
	}

	for (auto& index : toRemove)
	{
		_childrenBot.erase(_childrenBot.begin() + index);
	}
}

//=============================================================================

Vec2 Scene::getScreenSize(Screen screen) const
{
	if (screen == Screen::Top)
	{
		return Vec2(TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT);
	}
	else
	{
		return Vec2(BOTTOM_SCREEN_WIDTH, BOTTOM_SCREEN_HEIGHT);
	}
}

//=============================================================================

Vec2 Scene::getTopScreenSize() const
{
	return Vec2(TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT);
}

//=============================================================================

Vec2 Scene::getBotScreenSize() const
{
	return Vec2(BOTTOM_SCREEN_WIDTH, BOTTOM_SCREEN_HEIGHT);
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child)
{
	addChild(child, _addCounter++);
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, int zOrder)
{
	if (child)
	{
		_children.push_back(child);
		_children.back()->_parent = this;
		_children.back()->_scene = this;
		_children.back()->_zOrder = zOrder;

		sortByZOrder();
	}
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, int zOrder, int tag)
{
	if (child)
	{
		_children.push_back(child);
		_children.back()->_parent = this;
		_children.back()->_scene = this;
		_children.back()->_zOrder = zOrder;
		_children.back()->_tag = tag;

		sortByZOrder();
	}
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, int zOrder, const std::string & name)
{
	if (child)
	{
		_children.push_back(child);
		_children.back()->_parent = this;
		_children.back()->_scene = this;
		_children.back()->_zOrder = zOrder;
		_children.back()->_name = name;

		sortByZOrder();
	}
}

//=============================================================================

void Scene::addChildBot(const std::shared_ptr<Node>& child)
{
	addChildBot(child, _addCounterBot++);
}

//=============================================================================

void Scene::addChildBot(const std::shared_ptr<Node>& child, int zOrder)
{
	if (child)
	{
		_childrenBot.push_back(child);
		_childrenBot.back()->_parent = this;
		_childrenBot.back()->_scene = this;
		_childrenBot.back()->_zOrder = zOrder;

		sortByZOrderBot();
	}
}

//=============================================================================

void Scene::addChildBot(const std::shared_ptr<Node>& child, int zOrder, int tag)
{
	if (child)
	{
		_childrenBot.push_back(child);
		_childrenBot.back()->_parent = this;
		_childrenBot.back()->_scene = this;
		_childrenBot.back()->_zOrder = zOrder;
		_childrenBot.back()->_tag = tag;

		sortByZOrderBot();
	}
}

//=============================================================================

void Scene::addChildBot(const std::shared_ptr<Node>& child, int zOrder, const std::string & name)
{
	if (child)
	{
		_childrenBot.push_back(child);
		_childrenBot.back()->_parent = this;
		_childrenBot.back()->_scene = this;
		_childrenBot.back()->_zOrder = zOrder;
		_childrenBot.back()->_name = name;

		sortByZOrderBot();
	}
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, Screen screen)
{
	if (screen == Screen::Top)
		Node::addChild(child);
	else
		addChildBot(child);
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, int zOrder, Screen screen)
{
	if (screen == Screen::Top)
		Node::addChild(child, zOrder);
	else
		addChildBot(child, zOrder);
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, int zOrder, int tag, Screen screen)
{
	if (screen == Screen::Top)
		Node::addChild(child, zOrder, tag);
	else
		addChildBot(child, zOrder, tag);
}

//=============================================================================

void Scene::addChild(const std::shared_ptr<Node>& child, int zOrder,
	const std::string & name, Screen screen)
{
	if (screen == Screen::Top)
		Node::addChild(child, zOrder, name);
	else
		addChildBot(child, zOrder, name);
}

//=============================================================================

NS_KAIRY_END
