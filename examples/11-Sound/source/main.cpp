// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	// Get device singleton instance.
	auto device = RenderDevice::getInstance();
	
	// Just like we need to get and initialize
	// the RenderDevice for rendering, we need to get and
	// initialize the AudioDevice for playing audio.
	auto audio = AudioDevice::getInstance();
	
	auto input = InputManager::getInstance();
	
	device->init();
	audio->init();
	
	std::string instructions =
		"Press A to play\n\n"
		"Press B to stop\n\n"
		"Press X to pause";
	
	Text text(20.0f);
	text.setPosition(20, 20);
	text.setLineWidth(BOTTOM_SCREEN_WIDTH);
	text.setString(instructions);
	
	Sprite explosion("assets/Explosion.png");
	explosion.setPosition(
		(TOP_SCREEN_WIDTH-89)/2.0f,
		(TOP_SCREEN_HEIGHT-89)/2.0f);
	explosion.hide();
	
	Animation anim(Rect(0, 0,
		explosion.getTextureWidth(), explosion.getTextureHeight()),
		Vec2(89, 89), Time::seconds(0.1f), Animation::Type::Loop);
	
	// Creating a new sound loading it from a Wav file
	Sound sound("assets/Explosion.wav");
	sound.setLoop(true);
	
	// Main loop
	while(device->isRunning())
	{
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		if(input->isKeyDown(Keys::A))
		{
			sound.play();
			explosion.show();
			anim.start();
		}
		else if(input->isKeyDown(Keys::B))
		{
			sound.stop();
			explosion.hide();
			anim.stop();
		}
		else if(input->isKeyDown(Keys::X))
		{
			sound.pause();
			anim.pause();
		}
		
		anim.update(device->getDeltaTime());
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Cyan);
		device->startFrame();
		explosion.setTextureRect(anim.getCurrentFrame());
		explosion.draw();
		device->endFrame();
		
		device->setTargetScreen(Screen::Bottom);
		device->clear(Color::Black);
		device->startFrame();
		text.draw();
		device->endFrame();
		
		csndExecCmds(false);
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	audio->destroy();
	
	return 0;
}

//=============================================================================
