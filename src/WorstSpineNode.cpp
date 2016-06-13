#include "WorstSpineNode.h"

WorstSpineNode::WorstSpineNode(dataType value, dataType top) {
	_value = value;
	_top = top;
}

WorstSpineNode::~WorstSpineNode() {
	//cout << "lala" << endl;
	if (_leftChild == nullptr && _rightChild == nullptr) {
		return;
	}
	//cerr << "lala" << endl;

	vector<WorstSpineNode *> found;
	if (_leftChild != nullptr) {
		found.push_back(_leftChild);
		_leftChild = nullptr;
	}
	if (_rightChild != nullptr) {
		found.push_back(_rightChild);
		_rightChild = nullptr;
	}
	for (size_t i = 0; i < found.size(); i++) {
		WorstSpineNode *n = found[i];
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
	/*
	vector<WorstSpineNode *> nodes;

	WorstSpineNode *n = _rightChild;
	while (n != nullptr) {
		if (n->_leftChild != nullptr) {
			nodes.push_back(n->_leftChild);
			n->_leftChild = nullptr;
		}
		nodes.push_back(n);
		auto temp = n;
		n = n->_rightChild;
		temp->_rightChild = nullptr;
	}

	//cerr << "lala" << endl;
	for (auto a : nodes) {
		//cerr << (void *)a << endl;
		delete a;
	}
	*/
}

Node * WorstSpineNode::leftChild() {
	ACC
	COMP
	if (!_leftChild) {
		_leftChild = new WorstSpineNode(_top, _top);
	}
	return _leftChild;
}

Node * WorstSpineNode::rightChild() {
	ACC
	COMP
	if (!_rightChild) {
		COMP
		if (_top == _value) {
			_rightChild = new WorstSpineNode(_top, _top);
		} else {
			_rightChild = new WorstSpineNode(1, _top - 1);
		}
	}
	return _rightChild;
}