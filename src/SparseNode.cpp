#include "SparseNode.h"

int remaining = 0;

SparseNode::SparseNode(dataType value, bool good) {
	_value = value;
	_good = good;
	_root = false;
}

SparseNode::SparseNode(dataType value) {
	_value = value;
	_root = true;
}

Node * SparseNode::leftChild() {
	ACC
	if (!_leftChild) {
		if (_root) {
			_leftChild = new SparseNode(2, false);
		} else if (_good) {
			if (remaining > 0) {
				_leftChild = new SparseNode(1, _good);
				remaining--;
			}
		} else {
			_leftChild = new SparseNode(2, _good);
		}
	}
	return _leftChild;
}

Node * SparseNode::rightChild() {
	ACC
	if (!_rightChild) {
		if (_root) {
			_rightChild = new SparseNode(1, true);
			remaining--;
		} else if (_good) {
			if (remaining > 0) {
				_rightChild = new SparseNode(1, _good);
				remaining--;
			}
		} else {
			_rightChild = new SparseNode(2, _good);
		}
	}
	return _rightChild;
}

