#include "platform.h"

int main(int args, char** argv)
{
	renderer::Renderer renderer(false);
	renderer.SetClearColor(renderer::ColorRGBA::BLUE);

	while (true)
	{
		renderer.PreDraw();
		renderer.DisplayBuffer();		
	}

	return 0;
}