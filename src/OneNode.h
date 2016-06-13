#pragma once

#include <algorithm>
#include <random>

#include "dataType.h"
#include "Node.h"

class OneNode : public virtual Node {
public:
	Node * leftChild();
	Node * rightChild();
	OneNode();
	~OneNode();
private:
	OneNode *_leftChild = nullptr;
	OneNode *_rightChild = nullptr;
};
