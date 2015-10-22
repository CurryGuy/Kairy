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
	
	Sprite bee("assets/Bee.png");
	
	bee.setPosition(100, 100);
	
	// Bee sheet frames
	std::vector<Rect> frames =
	{
		{ 0.0f, 0.0f, 41.0f, 32.0f },
		{ 41.0f, 0.0f, 41.0f, 32.0f },
		{ 82.0f, 0.0f, 41.0f, 32.0f },
		{ 123.0f, 0.0f, 41.0f, 32.0f },
		{ 164.0f, 0.0f, 41.0f, 32.0f }
	};
	
	// Current sprite frame index
	Uint32 currentFrame = 0;
	
	// Create a new timer
	Timer timer;

	// And set its callback.
	// A callback is function called by the timer.
	// The timer also has a interval. In that case we set
	// it to 0.3 seconds. This means that every 0.3 seconds
	// the callback function will be called.
	timer.setCallback([&](float)
	{
		currentFrame++;
		if(currentFrame == frames.size())
			currentFrame = 0;
	}, Time::seconds(0.3f));
	
	// Main loop
	while(device->isRunning())
	{
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		// We need to update the timer
		// The timer like a lot of other Kairy classes
		// is an Updatable, so it has an update function.
		// The update function needs the delta time
		// (the time elapsed since the last frame) in seconds.
		// We can get the delta time using the RenderDevice
		// function getDeltaTime().
		timer.update(device->getDeltaTime());
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Cyan);
		device->startFrame();
		
		bee.setTextureRect(frames[currentFrame]);
		bee.draw();
		
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
