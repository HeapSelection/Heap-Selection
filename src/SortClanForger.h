#pragma once

#include <algorithm>
#include <vector>

#include "Clan.h"
#include "ClanForger.h"
#include "dataType.h"
#include "Node.h"

class SortClanForger : public virtual ClanForger {
public:
	Clan forgeClan(vector<Node *>, vector<Node *>);
};