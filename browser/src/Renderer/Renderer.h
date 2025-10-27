#pragma once
#include <memory>
#include "SDL.h"
#include "../HTML/HTMLNode.h"


class Renderer {
public:
	void renderNode(SDL_Renderer* renderer, std::shared_ptr<HTMLNode> node, int x, int& y);
	void drawText(SDL_Renderer* renderer, std::string text, int x, int y);
};