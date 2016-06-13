#pragma once

#include <cmath>
#include <limits>
#include <vector>

#include "dataType.h"
#include "Node.h"

class Utility {
public:
	vector<Node *> findUpTo(dataType, int, Node *);
	vector<Node *> findUpTo(dataType, int, vector<Node *> &);
	vector<Node *> findOne(Node *);
	vector<Node *> findOne(vector<Node *> &);
	int iteratedLog(int);
};
