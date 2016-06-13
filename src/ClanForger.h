#pragma once

#include <vector>

#include "Clan.h"
#include "dataType.h"
#include "Node.h"

class ClanForger {
	public:
		virtual Clan forgeClan(vector<Node *>, vector<Node *>) = 0;
};
