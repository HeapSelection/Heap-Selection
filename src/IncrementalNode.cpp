#include "IncrementalNode.h"

dataType globalValue = 2;

IncrementalNode::IncrementalNode(dataType value) {
	_value = value;
}

Node * IncrementalNode::leftChild() {
	ACC
	if (!_leftChild) {
		_leftChild = new IncrementalNode(globalValue++);
	}
	return _leftChild;
}

Node * IncrementalNode::rightChild() {
	ACC
		if (!_rightChild) {
			_rightChild = new IncrementalNode(globalValue++);
		}
	return _rightChild;
}