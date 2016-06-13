#pragma once

#include <algorithm>
#include <random>

#include "dataType.h"
#include "Node.h"
#include "random.h"

using namespace std;

class IncrementalNode : public virtual Node {
public:
	Node * leftChild();
	Node * rightChild();
	IncrementalNode(dataType);
	~IncrementalNode() {
		if (_leftChild) {
			delete _leftChild;
		}
		if (_rightChild) {
			delete _rightChild;
		}
	}
};
