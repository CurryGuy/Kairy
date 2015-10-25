// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

class TestScene : public Scene
{
public:
	bool onCreate() override
	{
		constexpr auto str =
		"Once you eliminate the impossible, \n"
		"whatever remains, no matter how improbable, \n"
		"must be the truth.";
		
		// Create the text node
		_text = Text::create("assets/font.fnt");
		
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
				
				auto sequence = Sequence::create({
					DelayTime::create(Time::seconds(0.3f * i)),
					FadeIn::create(1.0f)
				});
			
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
