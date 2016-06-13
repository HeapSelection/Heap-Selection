#include "LazyNode.h"

LazyNode::LazyNode(dataType value) {
	_value = value;
}

Node * LazyNode::leftChild() {
	ACC
	if (!_leftChild) {
		_leftChild = new LazyNode(_value + dist(r));
	}
	return _leftChild;
}

Node * LazyNode::rightChild() {
	ACC
	if (!_rightChild) {
		_rightChild = new LazyNode(_value + dist(r));
	}
	return _rightChild;
}

