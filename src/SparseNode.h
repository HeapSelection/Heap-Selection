#pragma once

#include <algorithm>
#include <random>

#include "dataType.h"
#include "Node.h"
#include "random.h"

using namespace std;

class SparseNode : public virtual Node {
public:
	Node * leftChild();
	Node * rightChild();
	SparseNode(dataType, bool);
	SparseNode(dataType);
	~SparseNode() {
		if (_leftChild) {
			delete _leftChild;
		}
		if (_rightChild) {
			delete _rightChild;
		}
	}
	bool _good;
	bool _root;
};

extern int remaining;
