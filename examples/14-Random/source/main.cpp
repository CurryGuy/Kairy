#include <Kairy/Kairy.h>

USING_NS_KAIRY;

//=============================================================================

int main(int argc, char* argv[])
{
	auto device = RenderDevice::getInstance();

	device->init();
	device->setQuitOnStart(true);

	// Change the clear color every second with a random color
	Color clearColor;

	Timer timer;

	timer.setCallback([&](float)
	{
		clearColor = Color::Random();
	}, Time::seconds(1.0f));
	
	while(device->isRunning())
	{
		timer.update(device->getDeltaTime());

		device->setTargetScreen(Screen::Top);
		device->clear(clearColor);
		device->startFrame();
		device->endFrame();

		device->setTargetScreen(Screen::Bottom);
		device->clear(clearColor);
		device->startFrame();
		device->endFrame();

		device->swapBuffers();
	}

	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();

	return 0;
}

//=============================================================================
