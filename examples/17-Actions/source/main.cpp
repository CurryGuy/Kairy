// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

class TestScene : public Scene
{
public:
	bool onCreate() override
	{
		auto sprite = std::make_shared<Sprite>("assets/Sprite.png");
		
		sprite->setPosition((getScreenSize(Screen::Top) - sprite->getSize()) / 2.0f);
		
		// Create an action that rotates the sprite by 120 degrees in 1 second
		auto rotateAction = std::make_shared<RotateBy>(1.0f, 120.0f);
		// Create a RepeatForever action wich will repeat forever the rotation
		auto repeatForever = std::make_shared<RepeatForever>(rotateAction);
		
		sprite->runAction(repeatForever);
		
		addChild(sprite);
		
		return true;
	}
private:
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
