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

#ifndef KAIRY_SCENE_SCENE_MANAGER_H_INCLUDED
#define KAIRY_SCENE_SCENE_MANAGER_H_INCLUDED

#include "Scene.h"
#include <stack>

NS_KAIRY_BEGIN

class SceneManager
{
public:

	static SceneManager* getInstance();

	virtual ~SceneManager();

	bool changeScene(const std::shared_ptr<Scene>& scene);

	bool popScene();

	bool popScene(std::shared_ptr<Scene>& poppedScene);

	bool pushScene(const std::shared_ptr<Scene>& scene);

	Scene* getCurrentScene() const;

	void draw();
	
	void update(float dt);
	
	SceneManager& operator=(const SceneManager&) = delete;
	
private:
	friend class RenderDevice;
	friend class InputManager;

	void onKeyDown(Keys key, float dt);

	void onKeyUp(Keys key, float dt);

	void onTouchDown(Vec2 position, float dt);
	
	void onTouchMoved(Vec2 position, float dt);
	
	void onTouchUp(Vec2 position, float dt);

private:
	SceneManager(void) = default;
	SceneManager(const SceneManager&) = default;

	std::stack<std::shared_ptr<Scene>> _sceneStack;
};

NS_KAIRY_END

#endif // KAIRY_SCRENE_SCENE_MANAGER_H_INCLUDED
