#pragma once
#include "HTMLNode.h"
#include <string>
#include <memory>

class HTMLParser {
public:
	std::shared_ptr<HTMLNode> parse(const std::string& html);
};