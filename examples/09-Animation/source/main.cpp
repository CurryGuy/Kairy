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
	
	// First we load the sprite we want to animate.
	Sprite skeleton("assets/Skeleton.png");
	
	skeleton.setPosition(100, 100);
	
	// Then we create the animation.
	// The animation class has different constructors, but in this case
	// we used this because is so convenient. This basically calculates
	// the animation frames using a region rectangle and the size of every frame.
	// So using this constructor implies that every frame has the same size.
	// We also passed the time we want to pass between each frame and the type
	// of animation.
	Animation animation(
		Rect(0, 0, skeleton.getTextureWidth(), skeleton.getTextureHeight()),
		Vec2(64, 64),
		Time::seconds(0.1f),
		Animation::Type::Loop);
	
	// Main loop
	while(device->isRunning())
	{
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		// Animation is an updatable so we need to call its update function.
		animation.update(device->getDeltaTime());
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Cyan);
		device->startFrame();
		
		// We set the sprite frame retriving it from the animation
		skeleton.setTextureRect(animation.getCurrentFrame());
		skeleton.draw();
		
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
