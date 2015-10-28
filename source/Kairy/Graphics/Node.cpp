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

#include <Kairy/Graphics/Node.h>

NS_KAIRY_BEGIN

//=============================================================================

Node::Node()
	: _transformUpdated(true)
	, _position(Vec2::Zero)
	, _size(Vec2::Zero)
	, _scaleX(1.0f)
	, _scaleY(1.0f)
	, _angle(0.0f)
	, _skewX(0.0f)
	, _skewY(0.0f)
	, _flipX(false)
	, _flipY(false)
	, _center(Vec2::Middle)
	, _userdata(nullptr)
	, _zOrder(-1)
	, _addCounter(0)
	, _parent(nullptr)
	, _scene(nullptr)
	, _touchEnabled(false)
	, _touchCallback(nullptr)
#ifndef _3DS
	, _vao(0)
	, _vbo(0)
#endif // _3DS
{
}

//=============================================================================

Node::~Node()
{
	removeFromParent();

#ifndef _3DS
	if (_vao != 0)
	{
		glDeleteVertexArrays(1, &_vao);
	}

	if (_vbo != 0)
	{
		glDeleteBuffers(1, &_vbo);
	}
#endif // _3DS
}

//=============================================================================

void Node::updateTransform()
{
	if (_transformUpdated)
	{
		auto centerInPixels = _center * _size;

		auto translation = Transform::createTranslation(_position);
		auto scale = Transform::createScale(_scaleX, _scaleY);
		auto rotation = Transform::createTranslation(centerInPixels) *
			Transform::createRotation(util::deg_to_rad(_angle)) *
			Transform::createTranslation(-centerInPixels);
		auto skew = Transform::createSkewX(util::deg_to_rad(_skewX)) *
			Transform::createSkewY(util::deg_to_rad(_skewY));

		if (_flipX)
			scale.setValue(0, 0, scale.getValue(0, 0) * -1.0f);

		if (_flipY)
			scale.setValue(1, 1, scale.getValue(1, 1) * -1.0f);

		_transform = translation * scale * rotation * skew;

		_transformUpdated = false;
	}
}

//=============================================================================

void Node::addChild(const std::shared_ptr<Node>& child)
{
	addChild(child, _addCounter++);
}

//=============================================================================

void Node::addChild(const std::shared_ptr<Node>& child, int zOrder)
{
	_children.push_back(child);
	_children.back()->_parent = this;
	_children.back()->_zOrder = zOrder;
	
	sortByZOrder();
}

//=============================================================================

void Node::addChild(const std::shared_ptr<Node>& child, int zOrder, int tag)
{
	_children.push_back(child);
	_children.back()->_parent = this;
	_children.back()->_zOrder = zOrder;
	_children.back()->_tag = tag;

	sortByZOrder();
}

//=============================================================================

void Node::addChild(const std::shared_ptr<Node>& child, int zOrder, const std::string & name)
{
	_children.push_back(child);
	_children.back()->_parent = this;
	_children.back()->_zOrder = zOrder;
	_children.back()->_name = name;

	sortByZOrder();
}

//=============================================================================

Node* Node::getChildByName(const std::string& name) const
{
	for(auto& child : _children)
	{
		if(child->getName() == name)
			return child.get();
	}
	
	return nullptr;
}

//=============================================================================

Node* Node::getChildByTag(int tag) const
{
	for(auto& child : _children)
	{
		if(child->getTag() == tag)
			return child.get();
	}
	
	return nullptr;
}

//=============================================================================

void Node::removeChildByTag(int tag)
{
	std::vector<Uint32> toRemove;
	
	for(Uint32 i = 0; i < _children.size(); ++i)
	{
		if(_children[i]->getTag() == tag)
			toRemove.push_back(i);
	}
	
	for(auto& index : toRemove)
	{
		_children.erase(_children.begin() + index);
	}
}

//=============================================================================

void Node::removeChildByName(const std::string& name)
{
	std::vector<Uint32> toRemove;
	
	for(Uint32 i = 0; i < _children.size(); ++i)
	{
		if(_children[i]->getName() == name)
			toRemove.push_back(i);
	}
	
	for(auto& index : toRemove)
	{
		_children.erase(_children.begin() + index);
	}
}

//=============================================================================

void Node::removeChild(Node* node)
{
	for(Uint32 i = 0; i < _children.size(); ++i)
	{
		if(_children[i].get() == node)
		{
			_children.erase(_children.begin() + i);
			break;
		}
	}
}

//=============================================================================

void Node::removeFromParent()
{
	if(_parent)
	{
		_parent->removeChild(this);
		_parent = nullptr;
	}
}

//=============================================================================

void Node::draw()
{
	updateTransform();

	for(auto& child : _children)
	{
		child->draw();
	}
}

//=============================================================================

void Node::update(float dt)
{
	if (!_actionsDone.empty())
	{
		for (auto& index : _actionsDone)
		{
			_actions.erase(_actions.begin() + index);
		}

		_actionsDone.clear();
	}

	for (Uint32 i = 0; i < _actions.size(); ++i)
	{
		_actions[i]->update(dt);

		if (_actions[i]->isDone())
		{
			_actionsDone.push_back(i);
		}
	}

	for(auto& child : _children)
	{
		child->update(dt);
	}
}

//=============================================================================

bool Node::onTouchDown(const Vec2 & position, float dt)
{
	if (_touchEnabled)
	{
		bool touched = getBoundingBox().containsPoint(position);

		if (touched)
		{
			if (_touchCallback)
				_touchCallback(position, TouchType::Down);

			for (auto& child : _children)
			{
				child->onTouchDown(position, dt);
			}
		}

		return touched;
	}

	return false;
}

//=============================================================================

void Node::onTouchUp(const Vec2 & position, float dt)
{
	if (_touchCallback)
		_touchCallback(position, TouchType::Up);

	for (auto& child : _children)
	{
		child->onTouchUp(position, dt);
	}
}

//=============================================================================

void Node::onTouchMoved(const Vec2 & position, float dt)
{
	if (_touchCallback)
		_touchCallback(position, TouchType::Moved);

	for (auto& child : _children)
	{
		child->onTouchMoved(position, dt);
	}
}

//=============================================================================

void Node::setTouchCallback(const TouchCallback & callback)
{
	_touchCallback = callback;
}

//=============================================================================

void Node::stopAllActions()
{
	for (auto& action : _actions)
	{
		action->stop();
	}
}

//=============================================================================

void Node::stopAllActionsByTag(int tag)
{
	for (auto& action : _actions)
	{
		if (action->getTag() == tag)
			action->stop();
	}
}

//=============================================================================

void Node::stopActionByTag(int tag)
{
	for (auto& action : _actions)
	{
		if (action->getTag() == tag)
		{
			action->stop();
			break;
		}
	}
}

//=============================================================================

void Node::stopActionByName(const std::string & name)
{
	for (auto& action : _actions)
	{
		if (action->getName() == name)
		{
			action->stop();
			break;
		}
	}
}

//=============================================================================

Uint32 Node::getRunningActions() const
{
	return _actions.size();
}

//=============================================================================

Action* Node::getActionByName(const std::string& name)
{
	for (auto& action : _actions)
	{
		if (action->getName() == name)
			return action.get();
	}

	return nullptr;
}

//=============================================================================

Action* Node::getActionByTag(int tag)
{
	for (auto& action : _actions)
	{
		if (action->getTag() == tag)
			return action.get();
	}

	return nullptr;
}

//=============================================================================

void Node::sortByZOrder()
{
	std::sort(_children.begin(), _children.end(),
		[](std::shared_ptr<Node>& a, std::shared_ptr<Node>& b)
	{
		return a->getZOrder() < b->getZOrder();
	});
}

//=============================================================================


void Node::runAction(const std::shared_ptr<Action>& action)
{
	_actions.push_back(action);
	_actions.back()->start(this);
}

//=============================================================================

NS_KAIRY_END
