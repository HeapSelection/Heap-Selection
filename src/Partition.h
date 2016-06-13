#pragma once

#include <vector>

#include "Node.h"

using namespace std;

class Partition {
	public:
		virtual void partition(int, vector<Node *> &) = 0;
};
