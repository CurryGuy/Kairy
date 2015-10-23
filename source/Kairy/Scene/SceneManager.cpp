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

#include <Kairy/Scene/SceneManager.h>
#include <Kairy/Graphics/RenderDevice.h>

NS_KAIRY_BEGIN

//=============================================================================

static std::unique_ptr<SceneManager> s_sharedSceneManager = nullptr;

//=============================================================================

SceneManager* SceneManager::getInstance()
{
	if (!s_sharedSceneManager)
	{
		s_sharedSceneManager.reset(new SceneManager());
	}

	return s_sharedSceneManager.get();
}

//=============================================================================

SceneManager::~SceneManager()
{
	int size = int(_sceneStack.size());
	for (int i = 0; i < size; ++i)
		popScene();
}

//=============================================================================

bool SceneManager::changeScene(std::unique_ptr<Scene>& scene)
{
	if (!scene)
		return false;

	if (!scene->onCreate())
		return false;

	if (_sceneStack.empty())
		_sceneStack.push(std::move(scene));
	else
		_sceneStack.top() = std::move(scene);

	return true;
}

//=============================================================================

bool SceneManager::popScene()
{
	if (_sceneStack.empty())
		return false;

	_sceneStack.top()->onDestroy();
	_sceneStack.pop();

	return true;
}

//=============================================================================

bool SceneManager::popScene(std::unique_ptr<Scene>& poppedScene)
{
	if (_sceneStack.empty())
		return false;

	_sceneStack.top()->onDestroy();
	poppedScene = std::move(_sceneStack.top());
	_sceneStack.pop();

	return true;
}

//=============================================================================

bool SceneManager::pushScene(std::unique_ptr<Scene>& scene)
{
	if (!scene)
		return false;

	if (!scene->onCreate())
		return false;
	
	_sceneStack.push(std::move(scene));

	return true;
}

//=============================================================================

Scene * SceneManager::getCurrentScene() const
{
	if (_sceneStack.empty())
		return nullptr;
	
	return _sceneStack.top().get();
}

//=============================================================================

void SceneManager::update(float dt)
{
	auto scene = getCurrentScene();

	if (scene)
	{	
		for (auto& child : scene->getChildren())
		{
			child->update(dt);
		}

		for (auto& child : scene->getChildrenBot())
		{
			child->update(dt);
		}

		scene->update(dt);
	}
}

//=============================================================================

void SceneManager::draw()
{
	auto scene = getCurrentScene();

	if (scene)
	{
		auto& device = scene->_device;
		auto prevScreen = device->getTargetScreen();		
		
		scene->updateTransform();

		/*if (scene->getChildrenCount() > 0)
		{*/
			device->setTargetScreen(Screen::Top);
			device->clear(scene->getColor());
			device->startFrame();

			for (auto& child : scene->getChildren())
			{
				child->draw();
			}

			device->endFrame();
		//}

		/*if (scene->getChildrenCountBot() > 0)
		{*/
			device->setTargetScreen(Screen::Bottom);
			device->clear(scene->getColorBot());
			device->startFrame();

			for (auto& child : scene->getChildrenBot())
			{
				child->draw();
			}

			device->endFrame();
		//}

		device->setTargetScreen(prevScreen);

		scene->draw();
	}
}

//=============================================================================

void SceneManager::onKeyDown(Keys key, float dt)
{
	auto scene = getCurrentScene();
	if (scene)
		scene->onKeyDown(key, dt);
}

//=============================================================================

void SceneManager::onKeyUp(Keys key, float dt)
{
	auto scene = getCurrentScene();
	if (scene)
		scene->onKeyUp(key, dt);
}

//=============================================================================

void SceneManager::onTouchDown(Vec2 position, float dt)
{
	auto scene = getCurrentScene();

	if (scene)
	{
		scene->onTouchDown(position, dt);

		for (auto& child : scene->_childrenBot)
		{
			child->onTouchDown(position, dt);
		}
	}
}

//=============================================================================

void SceneManager::onTouchMoved(Vec2 position, float dt)
{
	auto scene = getCurrentScene();

	if (scene)
	{
		scene->onTouchMoved(position, dt);

		for (auto& child : scene->_childrenBot)
		{
			child->onTouchMoved(position, dt);
		}
	}
}

//=============================================================================

void SceneManager::onTouchUp(Vec2 position, float dt)
{
	auto scene = getCurrentScene();

	if (scene)
	{
		scene->onTouchUp(position, dt);

		for (auto& child : scene->_childrenBot)
		{
			child->onTouchUp(position, dt);
		}
	}
}

//=============================================================================

NS_KAIRY_END
