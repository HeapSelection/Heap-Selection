#include "utility.h"

vector<Node *> Utility::findOne(Node *node) {
	vector<Node *> result;
	result.push_back(node);
	return result;
}

vector<Node *> Utility::findOne(vector<Node *> &nodes) {
	vector<Node *> result(1);
	dataType least = numeric_limits<dataType>::max();
	Node *leastNode = nodes[0];
	for (Node * n : nodes) {
		if (n->value() < least) {
			least = n->value();
			leastNode = n;
		}
	}
	result[0] = leastNode;
	return result;
}

vector<Node *> Utility::findUpTo(dataType highest, int k, Node *node) {
	vector<Node *> nodes;
	nodes.push_back(node);
	return findUpTo(highest, k, nodes);
}

vector<Node *> Utility::findUpTo(dataType highest, int k, vector<Node *> &nodes) {
	vector<Node *> result(0);
	vector<Node *> stack(0);
	vector<Node *> equals(0);
	result.reserve(2 * k);
	stack.reserve(2 * k);
	equals.reserve(k);
	for (Node *root : nodes) {
		stack.push_back(root);
	}
	while (!stack.empty()) {
		Node *current = stack.back();
		stack.pop_back();
		dataType value = current->value();
		COMP;
		if (value < highest) {
			result.push_back(current);
		} else if (value == highest && equals.size() <= (size_t) k) {
			equals.push_back(current);
		}
		Node *left = current->leftChild();
		COMP;
		if (left->value() < highest) {
			stack.push_back(left);
		}
		COMP;
		if (left->value() == highest) {
			COMP;
			if (equals.size() < (size_t)k) {
				stack.push_back(left);
			}
		}
		Node *right = current->rightChild();
		COMP;
		if (right->value() < highest) {
			stack.push_back(right);
		}
		COMP;
		if (right->value() == highest) {
			COMP;
			if (equals.size() < (size_t)k) {
				stack.push_back(right);
			}
		}
	}
	for (size_t i = 0;	i < equals.size(); i++) {
		result.push_back(equals[i]);
	}
	return result;
}

int Utility::iteratedLog(int k) {
	if (k <= 2) {
		return 1;
	}
	return 1 + iteratedLog((int)ceil(log2(k)));
}
