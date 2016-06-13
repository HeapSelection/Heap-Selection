#pragma once

#include <cmath>
#include <queue>
#include <vector>

#include "Select.h"
#include "dataType.h"

class NaiveSelect : public virtual Select {
public:
	vector<Node *> selectK(int, Node *);
	vector<Node *> selectK(int, vector<Node *> &);
	double asymptotic(int);
};