#pragma once

#include <iostream>

#include "dataType.h"
#include "Node.h"

using namespace std;

struct SuperNode {
	Node *node;
	dataType value;
	int id;
	int left = -1;
	int right = -1;
	int state = -1;
	SuperNode(Node *, int);
};