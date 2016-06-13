#pragma once

#include <algorithm>
#include <vector>

#include "Clan.h"
#include "ClanForger.h"
#include "dataType.h"
#include "Node.h"

class ScanClanForger : public virtual ClanForger {
public:
	Clan forgeClan(vector<Node *>, vector<Node *>);
};