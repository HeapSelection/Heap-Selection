#pragma once

#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <queue>

#include "BitClanForger.h"
#include "Clan.h"
#include "dataType.h"
#include "NaiveSelect.h"
#include "Node.h"
#include "Partition.h"
#include "RandomPartition.h"
#include "Select.h"
#include "SortPartition.h"
#include "utility.h"

using namespace std;

class SEL2 : public virtual Select {
public:
	SEL2(Partition &);
	vector<Node *> selectK(int, Node *);
	vector<Node *> selectK(int, vector<Node *> &);
	double asymptotic(int);

private:
	Partition &partition;
	BitClanForger clanForger;
	Utility utility;
};