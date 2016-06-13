#pragma once

#include <sstream>
#include <vector>

#include "dataType.h"
#include "Node.h"
#include "test.h"

struct Clan {
	dataType value = 0;
	vector<Node *> nodes;
	vector<Node *> offspring;
	vector<Node *> poorRelation;

	string toString();
};

struct ClanComparator {
	bool operator() (const Clan & a, const Clan & b) const {
		COMP
		return a.value > b.value;
	}
};
