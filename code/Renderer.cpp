#include "Renderer.h"

#include "Common.h"

#include "graphics.h"

void Renderer::refresh()
{
	// Clear screen
	FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void Renderer::render(const std::vector<GameObject*>& renderList)
{
	// TODO Since there is no face, vertex, etc. information at this moment, it only
	// calls displaySelf() method of renderable objects (GameObject).
	for (int ei = 0; ei < renderList.size(); ei++)
	{
		renderList[ei]->displaySelf();
	}
}