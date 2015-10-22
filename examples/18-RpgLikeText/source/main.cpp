// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

class TestScene : public Scene
{
public:
	bool onCreate() override
	{
		const std::string str =
		"Once you eliminate the impossible, \n"
		"whatever remains, no matter how improbable, \n"
		"must be the truth.";
		
		// Create the text node
		_text = std::make_shared<Text>("assets/font.fnt");
		
		_text->setString(str);
		_text->setPosition(0, 0);
		
		addChild(_text);
		
		startTextFading();
		
		return true;
	}
	
	void startTextFading()
	{
		// Get the number of characters.
		const Uint32 len = _text->getString().length();
		
		// For every character in the text
		for(Uint32 i = 0; i < len; ++i)
		{
			// Using the getCharacter method we get the
			// character sprite
			auto characterSprite = _text->getCharacter(i);
			
			// Special characters don't have a sprite
			if(characterSprite)
			{
				characterSprite->setOpacity(0);
				
				auto wait = std::make_shared<DelayTime>(Time::seconds(0.3f * i));
				auto fadeIn = std::make_shared<FadeIn>(1.0f);
			
				std::shared_ptr<Sequence> sequence(new Sequence({
					wait, fadeIn
				}));
			
				characterSprite->runAction(sequence);
			}
		}
	}
	
private:
	std::shared_ptr<Text> _text;
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
