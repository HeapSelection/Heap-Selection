#include "BitClanForger.h"

Clan BitClanForger::forgeClan(vector<Node *> input, vector<Node *> content) {
	Clan result;
	result.nodes = content;

	// Do you even cpp, brah?
	for (size_t i = 0; i < content.size(); i++) {
		result.value = max(result.value, content[i]->value());
		content[i]->_leftChild = (Node *) ((size_t) content[i]->_leftChild | 1);
	}

	for (size_t i = 0; i < input.size(); i++) {
		if (((size_t) input[i]->_leftChild & 1) == 0) {
			result.poorRelation.push_back(input[i]);
		}
	}

	for (size_t i = 0; i < content.size(); i++) {
		Node *n = content[i];
		Node *left = (Node *) ((size_t) n->leftChild() & ~1);
		if (left != nullptr) {
			if (((size_t) left->_leftChild & 1) == 0) {
				result.offspring.push_back(left);
			}
		}
		Node *right = (Node *) ((size_t) n->rightChild() & ~1);
		if (right != nullptr) {
			if (((size_t) right->_leftChild & 1) == 0) {
				result.offspring.push_back(right);
			}
		}
	}

	for (size_t i = 0; i < content.size(); i++) {
		content[i]->_leftChild = (Node *) (((size_t) content[i]->_leftChild) & ~1);
	}

	return result;
}
