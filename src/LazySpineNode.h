#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "dataType.h"
#include "Node.h"
#include "random.h"

using namespace std;

class LazySpineNode : public virtual Node {
public:
	Node * leftChild();
	Node * rightChild();
	LazySpineNode(dataType);
	~LazySpineNode();
private:
	LazySpineNode * _leftChild = nullptr;
};