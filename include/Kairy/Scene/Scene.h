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

#ifndef KAIRY_SCENE_SCENE_H_INCLUDED
#define KAIRY_SCENE_SCENE_H_INCLUDED

#include <Kairy/Graphics/Node.h>
#include <Kairy/System/InputManager.h>

NS_KAIRY_BEGIN

class Scene : public Node
{
public:

	Scene(void);

	virtual ~Scene(void);

	virtual bool onCreate() { return true; };

	virtual void onDestroy() {};

	virtual void draw(void) {};

	virtual void update(float dt) {};

	virtual void onKeyDown(Keys key, float dt) {};

	virtual void onKeyUp(Keys key, float dt) {};

	virtual void onTouchDown(Vec2 position, float dt) {};

	virtual void onTouchMoved(Vec2 position, float dt) {};

	virtual void onTouchUp(Vec2 position, float dt) {};

	inline void setColorBot(const Color& colorBot) { _colorBot = colorBot; }

	inline Color getColorBot() const { return _colorBot; }

	Vec2 getScreenSize(Screen screen) const;

	Vec2 getTopScreenSize() const;

	Vec2 getBotScreenSize() const;

	virtual void addChild(const std::shared_ptr<Node>& child) override;

	virtual void addChild(const std::shared_ptr<Node>& child, int zOrder) override;

	virtual void addChild(const std::shared_ptr<Node>& child, int zOrder, int tag) override;

	virtual void addChild(const std::shared_ptr<Node>& child, int zOrder,
		const std::string& name) override;

	void addChildBot(const std::shared_ptr<Node>& child);

	void addChildBot(const std::shared_ptr<Node>& child, int zOrder);

	void addChildBot(const std::shared_ptr<Node>& child, int zOrder, int tag);

	void addChildBot(const std::shared_ptr<Node>& child, int zOrder, const std::string& name);

	void addChild(const std::shared_ptr<Node>& child, Screen screen);

	void addChild(const std::shared_ptr<Node>& child, int zOrder, Screen screen);
	
	void addChild(const std::shared_ptr<Node>& child, int zOrder, int tag, Screen screen);

	void addChild(const std::shared_ptr<Node>& child, int zOrder,
		const std::string& name, Screen screen);

	virtual Node* getChildByName(const std::string& name) const override;

	virtual Node* getChildByTag(int tag) const override;

	void clearChildrenBot();

	Uint32 getChildrenCountBot() const;

	inline std::vector<std::shared_ptr<Node>>& getChildrenBot() { return _childrenBot; }

	virtual void removeChildByTag(int tag) override;

	virtual void removeChildByName(const std::string& name) override;

	virtual void removeChild(Node* child) override;

	void sortByZOrderBot();

protected:

	InputManager* _input;

	Color _colorBot;
	int _addCounterBot;
	std::vector<std::shared_ptr<Node>> _childrenBot;

private:
	friend class SceneManager;
};

NS_KAIRY_END

#endif // KAIRY_SCRENE_SCENE_H_INCLUDED
