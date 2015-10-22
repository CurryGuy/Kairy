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
	
	text.setPosition(0, 30);
	text.setColor(Color::White);
	text.setLineWidth(BOTTOM_SCREEN_WIDTH);
	
	std::string str =
			"Press A to take a screenshot of top screen.\n\n"
			"Press B to take a screenshot of bottom screen.\n";
	
	text.setString(str);
	
	// Setup a basic scene
	CircleShape circle(60);
	circle.setPosition(100, 50);
	circle.setColor(Color::Yellow);
	
	circle.setSegments(20);
	
	TriangleShape triangle(Vec2(110, 60), Vec2(140, 10), Vec2(180, 60));
	triangle.setColor(Color::Red);
	
	// Main loop
	while(device->isRunning())
	{
		if(input->isKeyDown(Keys::A))
		{
			device->takeScreenshot("top.png", ImageFormat::Png, Screen::Top);
		}
		else if(input->isKeyDown(Keys::B))
		{
			device->takeScreenshot("bot.png", ImageFormat::Png, Screen::Bottom);
		}
		
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		triangle.setScale((float)std::sin(device->getTicks()));
		circle.setAngle(circle.getAngle() + 20.0f * device->getDeltaTime());
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Cyan);
		device->startFrame();
		circle.draw();
		triangle.draw();
		device->endFrame();
		
		device->setTargetScreen(Screen::Bottom);
		device->clear(Color::Black);
		device->startFrame();
		text.draw();
		device->endFrame();
		
		device->swapBuffers();
	}
	
	// DON'T FORGET TO CALL THIS OR THE 3DS WILL CRASH AT EXIT
	device->destroy();
	
	return 0;
}

//=============================================================================
