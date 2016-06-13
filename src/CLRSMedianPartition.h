#pragma once

#include <algorithm>
#include <vector>

#include "dataType.h"
#include "Node.h"
#include "Partition.h"

using namespace std;

class CLRSMedianPartition : public virtual Partition {
public:
	void partition(int, vector<Node *> &);
private:
	void SELECT(vector<Node *> &, size_t, size_t);
};