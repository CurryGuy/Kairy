// This is the unique header you have to include
#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	// Get device singleton instance.
	auto device = RenderDevice::getInstance();
	
	device->init();
	
	device->setQuitOnStart(true);
	
	// Create a new text using the builtin arial font
	// with a size of 30 pixels.
	Text text(30.0f);
	
	// Set text position
	text.setPosition(100, 100);
	// Set text color to white
	text.setColor(Color::White);
	// Set the string to draw
	text.setString("Hello Text");
	
	// Main loop
	while(device->isRunning())
	{
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Black);
		device->startFrame();
		// Draw the text
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
