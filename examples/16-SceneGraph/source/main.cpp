// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

class TestScene : public Scene
{
public:
	bool onCreate() override
	{
		// Create a Sprite shared_ptr
		_sprite = std::make_shared<Sprite>("assets/sprite.png");
		// Create the sprite bounds rect
		_bounds = std::make_shared<RectangleShape>(_sprite->getSize());
		_bounds->setColor(Color::Transparent);
		_bounds->setOutlineColor(Color::Blue);
		
		// Add the rectangle to the sprite
		_sprite->addChild(_bounds);
		
		// Center the sprite position
		_sprite->setPosition((getScreenSize(Screen::Top) -
			_sprite->getSize()) / 2.0f);
		
		// Add the sprite on the top screen
		addChild(_sprite);
		
		// Add a red triangle to the bottom screen
		auto triangle = std::make_shared<TriangleShape>(Vec2(-30, 30), Vec2(0, 0), Vec2(30, 30));
		triangle->setPosition((getScreenSize(Screen::Bottom) - triangle->getSize()) / 2.0f);
		triangle->setColor(Color::Red);
		addChildBot(triangle);
		
		return true;
	}
	
	void draw()
	{
		// You can manually draw things too
		_device->setTargetScreen(Screen::Bottom);
		_device->startFrame();
		_sprite->draw();
		_device->endFrame();
	}

	void update(float dt)
	{
	}

	void onKeyDown(Keys key, float dt)
	{
	}

private:
	std::shared_ptr<Sprite> _sprite;
	std::shared_ptr<RectangleShape> _bounds;
};

//=============================================================================

int main(int argc, char* argv[])
{
	auto device = RenderDevice::getInstance();
	auto audio = AudioDevice::getInstance();

	device->init();
	audio->init();

	device->setQuitOnStart(true);

	std::unique_ptr<Scene> scene(new TestScene());

	SceneManager::getInstance()->changeScene(scene);

	while (device->isRunning())
	{
		SceneManager::getInstance()->update(device->getDeltaTime());
		SceneManager::getInstance()->draw();

		device->swapBuffers();
	}

	audio->destroy();
	device->destroy();

	return EXIT_SUCCESS;
}

//=============================================================================
