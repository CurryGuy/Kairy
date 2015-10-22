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

#ifndef KAIRY_GRAPHICS_NODE_H_INCLUDED
#define KAIRY_GRAPHICS_NODE_H_INCLUDED

#include <Kairy/Math/Transform.h>
#include <Kairy/Util/Radians.h>
#include <Kairy/Actions/Action.h>
#include "Drawable.h"

NS_KAIRY_BEGIN

class Scene;

class Node : public Updatable, public Drawable
{
public:

	Node(void);

	virtual ~Node(void);

	inline void setPosition(float x, float y);

	inline void setPosition(const Vec2& position);

	inline void setPositionX(float x);

	inline void setPositionY(float y);

	inline Vec2 getPosition() const;

	inline float getPositionX() const;

	inline float getPositionY() const;

	inline Rect getBoundingBox() const;

	inline Transform getParentTransform() const;

	inline Transform getTransform() const;

	inline Transform getCombinedTransform() const;

	inline void setTransform(const Transform& transform);

	inline virtual void setScaleX(float scaleX);

	inline virtual void setScaleY(float scaleY);

	inline virtual void setScale(float scale);

	inline virtual float getScale() const;

	inline virtual float getScaleX() const;

	inline virtual float getScaleY() const;

	inline virtual void setCenter(float x, float y);

	inline virtual void setCenter(const Vec2& center);

	inline virtual Vec2 getCenter() const;

	inline virtual void setAngle(float angle);

	inline void setAngleRad(float radians);

	inline virtual float getAngle() const;

	inline float getAngleRad() const;

	inline virtual void setSkew(float skewX, float skewY);

	inline virtual void setSkewX(float skew);

	inline void setSkewXRadians(float radians);

	inline virtual void setSkewY(float skew);

	inline void setSkewYRadians(float radians);

	inline virtual float getSkewX() const;

	inline virtual float getSkewY() const;

	inline float getSkewXRadians() const;

	inline float getSkewYRadians() const;

	inline void setFlipX(bool flipped);

	inline void setFlipY(bool flipped);

	inline void flipX();

	inline void flipY();

	inline bool isFlipX() const;

	inline bool isFlipY() const;

	inline virtual void setSize(const Vec2& size);

	inline virtual Vec2 getSize() const;

	inline virtual Vec2 getSizeScaled() const;

	inline std::string getName() const;

	inline void setName(const std::string& name);

	inline int getTag() const;

	inline void setTag(int tag);

	inline void* getUserdata() const;

	inline void setUserdata(void* userdata);

	inline int getZOrder() const;

	inline void setZOrder(int zOrder);

	inline Scene* getScene() const;

	virtual void updateTransform();

	inline Node* getParent();

	virtual void addChild(const std::shared_ptr<Node>& child);

	virtual void addChild(const std::shared_ptr<Node>& child, int zOrder);

	virtual void addChild(const std::shared_ptr<Node>& child, int zOrder, int tag);

	virtual void addChild(const std::shared_ptr<Node>& child, int zOrder,
		const std::string& name);

	inline std::vector<std::shared_ptr<Node>>& getChildren();

	virtual Node* getChildByName(const std::string& name) const;

	virtual Node* getChildByTag(int tag) const;

	inline Uint32 getChildrenCount() const;

	inline virtual void clearChildren();

	virtual void removeChildByTag(int tag);

	virtual void removeChildByName(const std::string& name);

	virtual void removeChild(Node* child);

	void removeFromParent();

	virtual void draw(void) override;

	virtual void update(float dt) override;

	virtual void onTouchDown(const Vec2& position, float dt) {};

	virtual void onTouchUp(const Vec2& position, float dt) {};

	virtual void onTouchMoved(const Vec2& position, float dt) {};

	virtual void runAction(const std::shared_ptr<Action>& action);

	void stopAllActions();

	void stopAllActionsByTag(int tag);

	void stopActionByTag(int tag);

	void stopActionByName(const std::string& name);

	Uint32 getRunningActions() const;

	Action* getActionByName(const std::string& name);

	Action* getActionByTag(int tag);

protected:
	friend class Scene;

	void sortByZOrder();

	Transform _transform;
	bool _transformUpdated;
	
	Vec2 _position;
	Vec2 _size;
	float _scaleX;
	float _scaleY;
	float _angle;
	float _skewX;
	float _skewY;
	bool _flipX;
	bool _flipY;
	Vec2 _center;
	std::string _name;
	int _tag;
	void* _userdata;
	
	int _zOrder;
	int _addCounter;
	
	Node* _parent;
	Scene* _scene;
	
	std::vector<std::shared_ptr<Node>> _children;
	std::vector<std::shared_ptr<Action>> _actions;
	std::vector<Uint32> _actionsDone;

#ifndef _3DS
	GLuint _vao;
	GLuint _vbo;
#endif // _3DS
};

#include "Node.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_NODE_H_INCLUDED
