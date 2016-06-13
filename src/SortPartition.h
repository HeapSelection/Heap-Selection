#pragma once

#include <algorithm>
#include <vector>

#include "dataType.h"
#include "Node.h"
#include "Partition.h"

using namespace std;

class SortPartition : public virtual Partition {
public:
	void partition(int, vector<Node *> &);
};