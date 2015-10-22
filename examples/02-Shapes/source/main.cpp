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
	
	// Create a rectangle shape
	RectangleShape rect(100, 60, 100, 100);
	// And we set it's color to blue
	rect.setColor(Color::Blue);
	
	rect.setOutlineColor(Color::Red);
	rect.setOutlineThickness(2);
	
	// Create a line
	LineShape line(0, 0, BOTTOM_SCREEN_WIDTH, BOTTOM_SCREEN_HEIGHT);
	// And set its color to yellow
	line.setColor(Color::Yellow);
	
	// Main loop
	while(device->isRunning())
	{
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Black);
		device->startFrame();
		// Draw the rectangle to top screen
		rect.draw();
		device->endFrame();
		
		device->setTargetScreen(Screen::Bottom);
		device->clear(Color::Black);
		device->startFrame();
		// Draw a diagonal line on bottom screen
		line.draw();
		device->endFrame();
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	return 0;
}

//=============================================================================
