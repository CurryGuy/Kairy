// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

class TestScene : public Scene
{
public:
	bool onCreate() override
	{
		setColor(Color::Cyan);
		setColorBot(Color::Yellow);
		
		_dragging = false;
		
		_sprite = Sprite::create("assets/Sprite.png");
		addChildBot(_sprite);
		
		return true;
	}
	
	void onTouchDown(Vec2 position, float dt) override
	{
		if(_sprite->getBoundingBox().containsPoint(position))
		{
			_dragging = true;
		}
	}
	
	void onTouchMoved(Vec2 position, float dt) override
	{
		if(_dragging)
		{
			_sprite->setPosition(position - _sprite->getSize() / 2.0f);
		}
	}
	
	void onTouchUp(Vec2 position, float dt) override
	{
		_dragging = false;
	}
	
private:
	std::shared_ptr<Sprite> _sprite;
	bool _dragging;
};

//=============================================================================

int main(int argc, char* argv[])
{
	auto device = RenderDevice::getInstance();
	auto audio = AudioDevice::getInstance();
	auto sceneManager = SceneManager::getInstance();

	device->init();
	audio->init();

	device->setQuitOnStart(true);

	sceneManager->changeScene(std::make_shared<TestScene>());

	while (device->isRunning())
	{
		sceneManager->update(device->getDeltaTime());
		sceneManager->draw();

		device->swapBuffers();
	}

	audio->destroy();
	device->destroy();

	return EXIT_SUCCESS;
}

//=============================================================================
