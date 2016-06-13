#include "SEL1.h"

Clan SEL1::createClan(int clanSize, vector<Node *> & nodes) {
	vector<Node *> content = selectForClan.selectK(clanSize, nodes);
	return clanForger.forgeClan(nodes, content);
}

vector<Node *> SEL1::selectK(int k, Node *node) {
	vector<Node *> nodes;
	nodes.push_back(node);

	vector<Node *> result(0);
	result.reserve(k);

	priority_queue<Clan, vector<Clan>, ClanComparator> pq;
	const int clanSize = (int)floor(log2(k));
	pq.push(createClan(clanSize, nodes));
	dataType highest = 0;
	int limit = (int)ceil(k / (double)clanSize);
	for (int i = 0; i < limit; i++) {
		Clan c = pq.top();
		pq.pop();
		highest = c.value;

		if (c.offspring.size() > 0) {
			pq.push(createClan(clanSize, c.offspring));
		}
		if (c.poorRelation.size() > 0) {
			pq.push(createClan(clanSize, c.poorRelation));
		}
	}

	auto possible = utility.findUpTo(highest, k, nodes);

	partition.partition(k, possible);

	for (int i = 0; i < k && i < (int)possible.size(); i++) {
		result.push_back(possible[i]);
	}

	return result;
}

double SEL1::asymptotic(int k) {
	return k * log2(log2(k));
}
