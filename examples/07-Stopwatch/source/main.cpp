// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	// Get device singleton instance.
	auto device = RenderDevice::getInstance();
	
	auto input = InputManager::getInstance();
	
	device->init();
	
	Text text(20.0f);
	text.setLineWidth(BOTTOM_SCREEN_WIDTH);
	
	std::string instructions =
			"Press A to start\n\n"
			"Press B to stop\n\n"
			"Press R to reset";
	
	// Create the stopwatch
	StopWatch watch;
	
	// Main loop
	while(device->isRunning())
	{
		if(input->isKeyDown(Keys::A))
		{
			watch.start();
		}
		else if(input->isKeyDown(Keys::B))
		{
			watch.stop();
		}
		else if(input->isKeyDown(Keys::R))
		{
			watch.reset();
		}
		
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Red);
		device->startFrame();
		
		std::string elapsed =
				util::to_string(watch.getElapsedTime().asMilliseconds()) +
				" ms";
		
		text.setScale(2.0f);
		text.setPosition(100, 100);
		text.setColor(Color::Cyan);
		text.setString(elapsed);
		text.draw();
		
		device->endFrame();
		
		device->setTargetScreen(Screen::Bottom);
		device->clear(Color::Black);
		device->startFrame();
		
		text.setScale(1.0f);
		text.setPosition(20, 20);
		text.setColor(Color::White);
		text.setString(instructions);
		text.draw();
		device->endFrame();
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	return 0;
}

//=============================================================================
