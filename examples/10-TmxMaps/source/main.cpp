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
	
	// If we want to draw a tmx map we first need a renderer.
	TmxMapRenderer mapRenderer;
	
	// We created the renderer but we didn't load the map.
	// Since we don't need any information from the map
	// we can just load the map and pass it directly to the renderer
	// using the function setMap.
	mapRenderer.setMap(TmxMap("assets/map.tmx"));
	
	// We can specify a region of the map to draw and we're doing that
	// with this rectangle called "camera".
	Rect camera { 0, 0, TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT };
	
	// The camera movement speed
	constexpr float SCROLL_SPEED = 64.0f;
	
	// Main loop
	while(device->isRunning())
	{
		float dt = device->getDeltaTime();
		
		if(input->isKeyDown(Keys::Start))
		{
			device->quit();
		}
		
		if(input->isKeyDown(Keys::Right))
		{
			camera.x += SCROLL_SPEED * dt;
		}
		else if(input->isKeyDown(Keys::Left))
		{
			camera.x -= SCROLL_SPEED * dt;
		}
		else if(input->isKeyDown(Keys::Down))
		{
			camera.y += SCROLL_SPEED * dt;
		}
		else if(input->isKeyDown(Keys::Up))
		{
			camera.y -= SCROLL_SPEED * dt;
		}
		
		// OrthoTmxMapRenderer is an updatable. The reason of that
		// is it should update the tile animations.
		mapRenderer.update(device->getDeltaTime());
		
		device->setTargetScreen(Screen::Top);
		device->clear(Color::Cyan);
		device->startFrame();
		mapRenderer.setCamera(camera);
		mapRenderer.draw();
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
