#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	auto device = RenderDevice::getInstance();
	
	device->init();
	device->setQuitOnStart(true);
	
	Text text(30.0f);
	text.setString("Random color");
	
	// Create a thread that changes the text color every second
	Thread thread([&](void*)
	{
		while(device->isRunning())
		{
			text.setColor(Color::Random());
			Thread::sleep(Time::seconds(1));
		}
	});
	
	// Start the thread
	thread.start();
	
	while(device->isRunning())
	{
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
	
	// Wait the thread end
	thread.join();
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	return 0;
}

//=============================================================================
