#include "NaiveSelect.h"

vector<Node *> NaiveSelect::selectK(int k, Node *node) {
	vector<Node *> nodes;
	nodes.push_back(node);
	return selectK(k, nodes);
}

vector<Node *> NaiveSelect::selectK(int k, vector<Node *> & nodes) {
	priority_queue<Node *, vector<Node *>, NodeComparator> pq;
	vector<Node *> result;
	int found = 0;
	for (Node * n : nodes) {
		COMP;
		pq.push(n);
	}
	while (!pq.empty()) {
		COMP;
		Node *n = pq.top();
		pq.pop();
		result.push_back(n);
		found++;
		COMP;
		if (found == k) {
			break;
		}
		Node *l = n->leftChild();
		COMP;
		if (l) {
			pq.push(l);
		}
		Node *r = n->rightChild();
		COMP;
		if (r) {
			pq.push(r);
		}
	}
	return result;
}

double NaiveSelect::asymptotic(int k) {
	return k * log2(k);
}
