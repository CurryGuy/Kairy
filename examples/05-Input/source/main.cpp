// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	// Get device singleton instance.
	auto device = RenderDevice::getInstance();
	// We use a class called InputManager for checking input.
	// It's a singleton so we need to get the instance.
	auto input = InputManager::getInstance();
	
	device->init();
	
	Text text(20.0f);
	
	text.setPosition(100, 100);
	text.setColor(Color::White);
	
	// Main loop
	while(device->isRunning())
	{
		std::string key;
		
		if(input->isKeyDown(Keys::A))
		{
			key = "A";
		} else if(input->isKeyDown(Keys::B))
		{
			key = "B";
		} else if(input->isKeyDown(Keys::X))
		{
			key = "X";
		} else if(input->isKeyDown(Keys::Y))
		{
			key = "Y";
		} else if(input->isKeyDown(Keys::L))
		{
			key = "L";
		} else if(input->isKeyDown(Keys::R))
		{
			key = "R";
		} else if(input->isKeyDown(Keys::Select))
		{
			key = "Select";
		} else // ... You should check other buttons too
		{
			key = "Nothing";
		}
		
		// Quit if the start button is pressed
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		text.setString(key + " pressed.");
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Black);
		device->startFrame();
		text.draw();
		device->endFrame();
		
		device->setTargetScreen(Screen::Bottom);
		device->clear(Color::Black);
		device->startFrame();
		device->endFrame();
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	return 0;
}

//=============================================================================
