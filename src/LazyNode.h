#pragma once

#include <algorithm>
#include <random>

#include "dataType.h"
#include "Node.h"
#include "random.h"

using namespace std;

class LazyNode : public virtual Node {
public:
	Node * leftChild();
	Node * rightChild();
	LazyNode(dataType);
	~LazyNode() {
		if (_leftChild) {
			delete _leftChild;
		}
		if (_rightChild) {
			delete _rightChild;
		}
	}
};
