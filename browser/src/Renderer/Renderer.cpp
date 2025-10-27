#include "Renderer.h"
#include <iostream>
#include <stdio.h>
#include <string>

void Renderer::renderNode(SDL_Renderer* renderer, std::shared_ptr<HTMLNode> node, int x, int& y) {
    if (node->type == HTMLNode::Type::TEXT) {
        drawText(renderer, node->textContent, x, y);
        y += 20; 
    }
    else if (node->type == HTMLNode::Type::ELEMENT) {
        for (auto& child : node->children) {
            renderNode(renderer, child, x + 10, y); 
        }
    }
}

void Renderer::drawText(SDL_Renderer* renderer, const std::string& text, int x, int y) {
    if (!font) return;

    SDL_Color color = { 0, 0, 0, 255 }; 
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dstRect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}