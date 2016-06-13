#pragma once

#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <queue>

#include "BitClanForger.h"
#include "Clan.h"
#include "ClanForger.h"
#include "dataType.h"
#include "NaiveSelect.h"
#include "Node.h"
#include "Partition.h"
#include "RandomPartition.h"
#include "ScanClanForger.h"
#include "Select.h"
#include "SortPartition.h"
#include "SortClanForger.h"
#include "SplitPriorityQueue.h"
#include "SuperNode.h"
#include "test.h"
#include "utility.h"

using namespace std;

struct PClan;
struct PClanComparator;

typedef SplitPriorityQueue<PClan *, PClanComparator> SPQ3;

struct PClan {
	dataType value; // rep_elt in the paper.
	Node *node;
	SPQ3 *pq;
	PClan(Node *, SPQ3 *);
	~PClan();
};

struct PClanComparator {
	bool operator() (const PClan *a, const PClan *b) const {
		COMP
		return a->node->value() > b->node->value();
	}
};

class SEL3 : public virtual Select {
public:
	SEL3(Partition &partition) : partition(partition) {}
	vector<Node *> selectK(int, Node *);
	double asymptotic(int);

private:
	Partition &partition;
	PClan * RSEL3(Node *, SPQ3 *, int);
	int h(int);
	Utility utility;
};