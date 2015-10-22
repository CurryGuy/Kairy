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
	
	// Create a sprite with "assets/Pikachu.png" as texture
	Sprite sprite("assets/Pikachu.png");
	
	// Set sprite position
	sprite.setPosition(20, 20);
	//  And blend it with orange
	sprite.setColor(Color::Orange);
	
	// Main loop
	while(device->isRunning())
	{
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Gray);
		device->startFrame();
		// Shiny Pikachu appears!
		sprite.draw();
		device->endFrame();
		
		device->setTargetScreen(Screen::Bottom);
		device->clear(Color::Gray);
		device->startFrame();
		device->endFrame();
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	return 0;
}

//=============================================================================
