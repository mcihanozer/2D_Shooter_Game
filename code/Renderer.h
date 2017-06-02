#ifndef RENDERER_H
#define RENDERER_H

#include "GameObject.h"

// Renderer is used to render in the scene.
// Since there is no face, vertex, etc. information at this moment, it only
// calls displaySelf() method of renderable objects (GameObject).
class Renderer
{
public:
	void refresh();
	void render(const std::vector<GameObject*>& renderList);
};

#endif // !RENDERER_H

