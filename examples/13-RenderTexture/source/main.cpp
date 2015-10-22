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
	
	Text text(20.0f);
	
	text.setPosition(0, 0);
	text.setColor(Color::White);
	text.setString("Hello Text");
	
	// Create the render texture, make it 100x100
	RenderTexture renderTexture;
	renderTexture.create(100, 100);
	// Start drawing on the texture
	renderTexture.startFrame();
	// Draw the text
	text.draw();
	// End drawing to the texture
	renderTexture.endFrame();
	
	// Save the render texture to a file
	renderTexture.save("out.png");
	
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
