#pragma once

#include <algorithm>
#include <random>

#include "dataType.h"
#include "Node.h"
#include "random.h"

using namespace std;

class WorstSpineNode : public virtual Node {
public:
	Node * leftChild();
	Node * rightChild();
	WorstSpineNode(dataType, dataType);
	~WorstSpineNode();
private:
	dataType _top;
	WorstSpineNode *_leftChild = nullptr;
	WorstSpineNode *_rightChild = nullptr;
};