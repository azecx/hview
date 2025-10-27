#pragma once
#include <SDL.h>
#include "../HTML/HTMLNode.h"


class Window {
private:
public:
	void render(SDL_Renderer* renderer, SDL_Window* window, std::shared_ptr<HTMLNode> dom);
};