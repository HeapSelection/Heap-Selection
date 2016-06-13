#include "LazySpineNode.h"

LazySpineNode::LazySpineNode(dataType value) {
	_value = value;
}

LazySpineNode::~LazySpineNode() {
	if (_leftChild == nullptr) {
		return;
	}

	vector<LazySpineNode *> nodes;
	LazySpineNode * n = _leftChild;
	do {
		nodes.push_back(n);
		auto temp = n;
		n = n->_leftChild;
		temp->_leftChild = nullptr;
	} while (n != nullptr);

	for (auto a : nodes) {
		delete a;
	}
}

Node * LazySpineNode::leftChild() {
	ACC
	if (!_leftChild) {
		_leftChild = new LazySpineNode(_value + dist(r));
	}
	return _leftChild;
}

Node * LazySpineNode::rightChild() {
	ACC
	return nullptr;
}
