#include "HTMLParser.h"
#include <stack>
#include <sstream>
#include <cctype>

std::shared_ptr<HTMLNode> HTMLParser::parse(const std::string& html) {
	std::shared_ptr<HTMLNode> root = HTMLNode::createElement("root");
	std::stack<std::shared_ptr<HTMLNode>> stack;
	stack.push(root);


	//parsing shit
	size_t i = 0;
	while (i < html.size()) {
		//starting tag, means element
		if (html[i] == '<') {
			if (html[+1] == '/') {
				//closing tag
				i += 2;
				size_t end = html.find('>', i);
				stack.pop();
				i = end + 1;
			}
			else {
				//opening tag
				i++;
				size_t end = html.find('>', i);
				std::string tag = html.substr(i, end - i);

				//create tag node
				auto node = HTMLNode::createElement(tag);
				stack.top()->children.push_back(node);
				node->parent = stack.top();
				stack.push(node);
				i = end + 1;
			}
		}
		else {
			//else, it's obv text content. so make a text node.
			size_t end = html.find("<");
			std::string text = html.substr(i, end - i);
			auto txtNode = HTMLNode::createText(text);
			stack.top()->children.push_back(txtNode);
			txtNode->parent = stack.top();
			i = end;
		}
	}
}