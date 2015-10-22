// This is the unique header you have to include
#include <Kairy/Kairy.h>

// All the Kairy classes and functions are in the
// namespace kairy. This macro is just an "using namespace kairy";
USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	// RenderDevice is a singleton class that
	// manages the rendering system.
	// With get instance we get the pointer to the singleton instance.
	auto device = RenderDevice::getInstance();
	
	// After we got that instance, we have to initialize the device
	device->init();
	// Set if the device should stop running if the users press
	// the start button or not. This is disabled by default.
	// We're doing this because otherwise the user
	// can't to exit from the homebrew.
	device->setQuitOnStart(true);
	
	// Main loop
	while(device->isRunning())
	{
		// With this function we specify the screen were
		// we want to draw to.
		device->setTargetScreen(Screen::Top);
		// We clear the screen with a pure red color
		device->clear(Color::Red);
		// We start drawing the frame on the top screen
		device->startFrame();
		// We end the drawing of the frame
		device->endFrame();
		
		// Same as above, but this time we set the
		// bottom screen as the target.
		device->setTargetScreen(Screen::Bottom);
		// And we clear it with cyan (i like cyan)
		device->clear(Color::Cyan);
		device->startFrame();
		device->endFrame();
		
		// Finally we show the contents of the framebuffers
		// to the screen.
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	// You may ask why we need to call init and destroy on a class.
	// These functions should be called once, so why we can't just
	// let the costructors and destructors call them? Well the fact is
	// that it's a workaround. If you call the destroy function in the destructor
	// the 3DS just crashes. That's for a specific reason, but in short: libctru fault
	// (Or maybe it's just an overall bad design...)
	
	return 0;
}

//=============================================================================
