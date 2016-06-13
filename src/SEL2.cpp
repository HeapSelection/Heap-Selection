#include "SEL2.h"

SEL2::SEL2(Partition &partition) : partition(partition) {
}

vector<Node *> SEL2::selectK(int k, Node *node) {
	vector<Node *> nodes;
	nodes.push_back(node);
	return selectK(k, nodes);
}

vector<Node *> SEL2::selectK(int k, vector<Node *> & nodes) {
	// Base case
	COMP;
	if (k == 1) {
		return utility.findOne(nodes);
	}

	vector<Node *> result;
	result.reserve(k);
	priority_queue<Clan, vector<Clan>, ClanComparator> pq;
	const int partitionSize = (int)(2 * floor(log2(k)));
	vector<Node *> partitionInput(0);
	partitionInput.reserve(partitionSize);
	for (int i = 0; i < (int)nodes.size(); i += partitionSize) {
		COMP;
		for (int j = 0; j < partitionSize && i + j < (int)nodes.size(); j++) {
			COMP;
			partitionInput.push_back(nodes[i + j]);
		}
		auto content = selectK((int)floor(log2(k)), partitionInput);
		Clan c = clanForger.forgeClan(partitionInput, content);
		pq.push(c);
		partitionInput.clear();
	}

	int limit = (int)ceil(k / (double)floor(log2(k)));
	dataType highest = 0;
	for (int i = 0; i <= limit && !pq.empty(); i++) {
		COMP;
		Clan c = pq.top();
		pq.pop();
		highest = max(highest, c.value);
		/*
		cout << "Content: ";
		for (auto a : c.nodes) {
			cout << a->value() << " ";
		}
		cout << endl;
		*/
		COMP;
		if (!c.offspring.empty()) {
			/*
			cout << "Offspring: ";
			for (auto a : c.offspring) {
				cout << a->value() << " ";
			}
			cout << endl;
			*/
			auto content = selectK((int)floor(log2(k)), c.offspring);
			Clan c1 = clanForger.forgeClan(c.offspring, content);
			pq.push(c1);
		}
		COMP;
		if (!c.poorRelation.empty()) {
			/*
			cout << "Poor relation: ";
			for (auto a : c.poorRelation) {
				cout << a->value() << " ";
			}
			cout << endl;
			*/
			auto content = selectK((int)floor(log2(k)), c.poorRelation);
			Clan c2 = clanForger.forgeClan(c.poorRelation, content);
			pq.push(c2);
		}
	}

	//cout << highest << "\t" << k << "\t" << nodes.size() << endl;
	auto possible = utility.findUpTo(highest, k, nodes);

	partition.partition(k, possible);

	for (int i = 0; i < k && i < (int)possible.size(); i++) {
		COMP;
		result.push_back(possible[i]);
	}




	return result;
}

double SEL2::asymptotic(int k) {
	return k * pow(3, utility.iteratedLog(k));
}
