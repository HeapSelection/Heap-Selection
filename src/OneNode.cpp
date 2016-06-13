#include "OneNode.h"

OneNode::OneNode() {
	_value = 1;
}
OneNode::~OneNode() {
	if (_leftChild == nullptr && _rightChild == nullptr) {
		return;
	}

	vector<OneNode *> found;
	if (_leftChild != nullptr) {
		found.push_back(_leftChild);
		_leftChild = nullptr;
	}
	if (_rightChild != nullptr) {
		found.push_back(_rightChild);
		_rightChild = nullptr;
	}
	for (size_t i = 0; i < found.size(); i++) {
		OneNode *n = found[i];
		if (n->_leftChild != nullptr) {
			found.push_back(n->_leftChild);
			n->_leftChild = nullptr;
		}
		if (n->_rightChild != nullptr) {
			found.push_back(n->_rightChild);
			n->_rightChild = nullptr;
		}
		delete n;
	}
}

Node * OneNode::leftChild() {
	ACC;
	COMP;
	if (!_leftChild) {
		_leftChild = new OneNode();
	}
	return _leftChild;
}

Node * OneNode::rightChild() {
	ACC;
	COMP;
	if (!_rightChild) {
		_rightChild = new OneNode();
	}
	return _rightChild;
}