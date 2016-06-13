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
#include "SuperNode.h"
#include "utility.h"

using namespace std;

class SEL1 : public virtual Select {
public:
	SEL1(Partition &partition) : partition(partition) {}
	vector<Node *> selectK(int, Node *);
	double asymptotic(int);

private:
	Clan createClan(int, vector<Node *> &);
	Partition &partition;
	NaiveSelect selectForClan;
	BitClanForger clanForger;
	Utility utility;
};