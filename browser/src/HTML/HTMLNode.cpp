#include "HTMLNode.h"

static std::shared_ptr<HTMLNode> createElement(const std::string& tag) {
	auto node = std::make_shared<HTMLNode>();
	node->type = HTMLNode::Type::ELEMENT;
	node->tagName = tag;
	return node;
}

static std::shared_ptr<HTMLNode> createText(const std::string& text) {
	auto node = std::make_shared<HTMLNode>();
	node->type = HTMLNode::Type::TEXT;
	node->textContent = text;
	return node;
}