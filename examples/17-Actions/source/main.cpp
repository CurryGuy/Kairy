// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

class TestScene : public Scene
{
public:
	bool onCreate() override
	{
		auto sprite = Sprite::create("assets/Sprite.png");
		
		sprite->setPosition((getScreenSize(Screen::Top) - sprite->getSize()) / 2.0f);
		
		// Create an action that rotates the sprite by 120 degrees in 1 second
		auto rotateAction = RotateBy::create(1.0f, 120.0f);
		// Create a RepeatForever action wich will repeat forever the rotation
		auto repeatForever = RepeatForever::create(rotateAction);
		
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
