#include "Renderer.h"

int lineHeight = 30;

Renderer::Renderer(int pxSize) {
    font = TTF_OpenFont("./assets/font/SegoeUI.ttf", pxSize);
    boldFont = TTF_OpenFont("./assets/font/SegoeUI-Bold.ttf", pxSize);
    italicFont = TTF_OpenFont("./assets/font/SegoeUI-Italic.ttf", pxSize);
    boldItalicFont = TTF_OpenFont("./assets/font/SegoeUI-BoldItalic.ttf", pxSize);
}

Renderer::~Renderer() {
    if (font) TTF_CloseFont(font);
    if (boldFont) TTF_CloseFont(boldFont);
    if (italicFont) TTF_CloseFont(italicFont);
    if (boldItalicFont) TTF_CloseFont(boldItalicFont);
}

//thanks stackoverflow.com
int Renderer::measureTextWidth(TTF_Font* baseFont, const std::string& text, Renderer::TextStyle style) {
    int w = 0, h = 0;
    TTF_Font* measureFont = font;

    if (style.bold && style.italic && boldItalicFont) measureFont = boldItalicFont;
    else if (style.bold && boldFont) measureFont = boldFont;
    else if (style.italic && italicFont) measureFont = italicFont;

    TTF_SizeText(measureFont, text.c_str(), &w, &h);
    return w;
}

void Renderer::renderNode(SDL_Renderer* renderer, std::shared_ptr<HTMLNode> node, int& x, int& y, Renderer::TextStyle style) {
    if (!node) return;

    if (node->type == HTMLNode::Type::TEXT) {
        drawText(renderer, node->textContent, x, y, style);
        x += measureTextWidth(font, node->textContent, style);
    }
    else if (node->type == HTMLNode::Type::ELEMENT) {
        TextStyle newStyle = style;
        if (node->tagName == "b") {
            auto parentPtr = node->parent.lock();

            if (!parentPtr || parentPtr->tagName != "i") {
                newStyle.bold = true;
            }
            else {
                newStyle.bold = true;
                newStyle.italic = true;
            }
        }
        if (node->tagName == "i") {
            auto parentPtr = node->parent.lock();
            if (!parentPtr || parentPtr->tagName != "b") {
                newStyle.italic = true;
            }
            else {
                newStyle.italic = true;
                newStyle.bold = true;
            }
        }

        if (node->tagName == "p" || node->tagName == "br") {
            x = 10;
            y += lineHeight;
        }

        for (auto& child : node->children) {
            renderNode(renderer, child, x, y, newStyle);
        }
    }
}

void Renderer::drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, Renderer::TextStyle style) {
    TTF_Font* drawFont = font;

    if (style.bold && style.italic && boldItalicFont) drawFont = boldItalicFont;
    else if (style.bold && boldFont) drawFont = boldFont;
    else if (style.italic && italicFont) drawFont = italicFont;

    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(drawFont, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dstRect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}
