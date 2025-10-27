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
            renderNode(renderer, child, x + 10, y); // indent children
        }
    }
}

void Renderer::drawText(SDL_Renderer* renderer, std::string text, int x, int y) {
    std::cout << text << std::endl;
}