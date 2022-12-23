#pragma once

#include "Structs.h"
#include "Input.h"

#include "UIElement.h"

class Camera;

class Canvas
{ 
public:

	Canvas();

	~Canvas();

	void Start();

	void RenderStart(SDL_Renderer* renderer);

	void Update();

	void RenderUpdate(SDL_Renderer* renderer, Camera camera);

private:

	vector<UIElement*> m_elements;

};