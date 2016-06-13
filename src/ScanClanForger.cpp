#include "ScanClanForger.h"

Clan ScanClanForger::forgeClan(vector<Node *> input, vector<Node *> content) {
	Clan result;
	result.nodes = content;
	sort(input.begin(), input.end());
	sort(content.begin(), content.end());

	for (Node * n : result.nodes) {
		// Find max value
		result.value = max(result.value, n->value());

		// Find offspring
		Node * left = n->leftChild();
		bool foundLeft = false;
		for (Node *m : result.nodes) {
			if (left == m) {
				foundLeft = true;
				break;
			}
		}
		if (!foundLeft) {
			result.offspring.push_back(left);
		}
		Node * right = n->rightChild();
		bool foundRight = false;
		for (Node *m : result.nodes) {
			if (right == m) {
				foundRight = true;
				break;
			}
		}
		if (!foundRight) {
			result.offspring.push_back(right);
		}
	}

	// Find poor relation
	for (Node *n : input) {
		bool found = false;
		for (Node *m : result.nodes) {
			if (n == m) {
				found = true;
				break;
			}
		}
		if (!found) {
			result.poorRelation.push_back(n);
		}
	}

	return result;
}
