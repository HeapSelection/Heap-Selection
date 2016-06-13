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
#include "utility.h"

using namespace std;

struct Clan4;
struct Clan4Comparator;

typedef SplitPriorityQueue<Clan4 *, Clan4Comparator> SPQ4;

struct Clan4 {
	dataType value; // rep_elt in the paper.
	Node *node;
	SPQ4 *pq;
	int category;
	Clan4(Node *, SPQ4 *, int);
	~Clan4();
};

struct Clan4Comparator {
	bool operator() (const Clan4 *a, const Clan4 *b) const {
		COMP;
		return a->value > b->value;
	}
};

class SEL4 : public virtual Select {
public:
	SEL4(Partition &partition) : partition(partition) {}
	SEL4(Partition &partition, int baseCase, double catFactor) : partition(partition), baseCase(baseCase),
		catFactor(catFactor) {}
	vector<Node *> selectK(int, Node *);
	double asymptotic(int);

private:
	Partition &partition;
	Clan4 * RSEL4(Node *, SPQ4 *, int);
	int h(int);
	int f(int);
	Utility utility;
	int baseCase = 36;
	double catFactor = 1.0;
};
