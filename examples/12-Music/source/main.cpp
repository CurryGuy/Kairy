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
	
	// Create the music by file path
	Music mus("assets/Intense_Theme.wav");
	// Play the music
	mus.play();
	
	// Main loop
	while(device->isRunning())
	{
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Cyan);
		device->startFrame();
		device->endFrame();
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	audio->destroy();
	
	return 0;
}

//=============================================================================
