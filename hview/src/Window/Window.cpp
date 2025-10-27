#include "Window.h"
#include <iostream>
#include "../Renderer/Renderer.h"

void Window::render(SDL_Renderer* renderer, SDL_Window* window, std::shared_ptr<HTMLNode> dom) {
	if (!renderer || !window) {
		std::cerr << "Renderer or Window is null!" << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	Renderer domRenderer;
	int y = 10;
	int x = 10;
	Renderer::TextStyle style;
	domRenderer.renderNode(renderer, dom, x, y, style);

	SDL_RenderPresent(renderer);
}