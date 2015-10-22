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

//=============================================================================

inline void Node::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setPosition(const Vec2 & position)
{
	_position = position;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setPositionX(float x)
{
	_position.x = x;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setPositionY(float y)
{
	_position.y = y;
	_transformUpdated = true;
}

//=============================================================================

inline Vec2 Node::getPosition() const
{
	return _position;
}

//=============================================================================

inline float Node::getPositionX() const
{
	return _position.x;
}

//=============================================================================

inline float Node::getPositionY() const
{
	return _position.y;
}

//=============================================================================

inline Rect Node::getBoundingBox() const
{
	return getCombinedTransform().transformRect(Rect(Vec2::Zero, getSize()));
}

//=============================================================================

inline Transform Node::getParentTransform() const
{
	if(_parent)
	{
		return _parent->getCombinedTransform();
	}
	
	return Transform();
}

//=============================================================================

inline Transform Node::getTransform() const
{
	return _transform;
}

//=============================================================================

inline Transform Node::getCombinedTransform() const
{
	return getParentTransform() * getTransform();
}

//=============================================================================

inline void Node::setTransform(const Transform& transform)
{
	_transform = transform;
}

//=============================================================================

inline void Node::setScaleX(float scaleX)
{
	_scaleX = scaleX;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setScaleY(float scaleY)
{
	_scaleY = scaleY;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setScale(float scale)
{
	_scaleX = scale;
	_scaleY = scale;
	_transformUpdated = true;
}

//=============================================================================

inline float Node::getScale() const
{
	return std::max(_scaleX, _scaleY);
}

//=============================================================================

inline float Node::getScaleX() const
{
	return _scaleX;
}

//=============================================================================

inline float Node::getScaleY() const
{
	return _scaleY;
}

//=============================================================================

inline void Node::setCenter(float x, float y)
{
	_center.x = x;
	_center.y = y;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setCenter(const Vec2 & center)
{
	_center = center;
	_transformUpdated = true;
}

//=============================================================================

inline Vec2 Node::getCenter() const
{
	return _center;
}

//=============================================================================

inline void Node::setAngle(float angle)
{
	_angle = angle;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setAngleRad(float radians)
{
	_angle = util::rad_to_deg(radians);
	_transformUpdated = true;
}

//=============================================================================

inline float Node::getAngle() const
{
	return _angle;
}

//=============================================================================

inline float Node::getAngleRad() const
{
	return util::deg_to_rad(_angle);
}

//=============================================================================

inline void Node::setSkew(float skewX, float skewY)
{
	_skewX = skewX;
	_skewY = skewY;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setSkewX(float skew)
{
	_skewX = skew;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setSkewXRadians(float radians)
{
	_skewX = util::rad_to_deg(radians);
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setSkewY(float skew)
{
	_skewY = skew;
	_transformUpdated = true;
}

//=============================================================================

inline void Node::setSkewYRadians(float radians)
{
	_skewY = util::rad_to_deg(radians);
	_transformUpdated = true;
}

//=============================================================================

inline float Node::getSkewX() const
{
	return _skewX;
}

//=============================================================================

inline float Node::getSkewY() const
{
	return _skewY;
}

//=============================================================================

inline float Node::getSkewXRadians() const
{
	return util::deg_to_rad(_skewX);
}

//=============================================================================

inline float Node::getSkewYRadians() const
{
	return util::deg_to_rad(_skewY);
}

//=============================================================================

inline void Node::setFlipX(bool flipped)
{
	_flipX = flipped;
}

//=============================================================================

inline void Node::setFlipY(bool flipped)
{
	_flipY = flipped;
}

//=============================================================================

inline void Node::flipX()
{
	_flipX = !_flipX;
}

//=============================================================================

inline void Node::flipY()
{
	_flipY = !_flipY;
}

//=============================================================================

inline bool Node::isFlipX() const
{
	return _flipX;
}

//=============================================================================

inline bool Node::isFlipY() const
{
	return _flipY;
}

//=============================================================================

inline void Node::setSize(const Vec2& size)
{
	_size = size;
	_transformUpdated = true;
}

//=============================================================================

inline Vec2 Node::getSize() const
{
	return _size;
}

//=============================================================================

inline Vec2 Node::getSizeScaled() const
{
	return Vec2(_size.x * _scaleX, _size.y * _scaleY);
}

//=============================================================================

inline std::string Node::getName() const
{
	return _name;
}

//=============================================================================

inline void Node::setName(const std::string& name)
{
	_name = name;
}

//=============================================================================

inline int Node::getTag() const
{
	return _tag;
}

//=============================================================================

inline void Node::setTag(int tag)
{
	_tag = tag;
}

//=============================================================================

inline void* Node::getUserdata() const
{
	return _userdata;
}

//=============================================================================

inline void Node::setUserdata(void* userdata)
{
	_userdata = userdata;
}

//=============================================================================

inline int Node::getZOrder() const
{
	return _zOrder;
}

//=============================================================================

inline void Node::setZOrder(int zOrder)
{
	_zOrder = zOrder;

	if (_parent)
		_parent->sortByZOrder();
}

//=============================================================================

inline Scene* Node::getScene() const
{
	return _scene;
}

//=============================================================================

inline Node* Node::getParent()
{
	return _parent;
}

//=============================================================================

inline std::vector<std::shared_ptr<Node>>& Node::getChildren()
{
	return _children;
}

//=============================================================================

inline Uint32 Node::getChildrenCount() const
{
	return _children.size();
}

//=============================================================================

inline void Node::clearChildren()
{
	for(auto& child : _children)
	{
		child->_parent = nullptr;
	}
	
	_children.clear();
	_addCounter = 0;
}

//=============================================================================
