#pragma once

#include <vector>

#include "dataType.h"
#include "Node.h"

using namespace std;

class Select {
	public:
		virtual vector<Node *> selectK(int, Node *) = 0;
		virtual double asymptotic(int k) = 0;
};
