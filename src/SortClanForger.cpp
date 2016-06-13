#include "SortClanForger.h"

Clan SortClanForger::forgeClan(vector<Node *> input, vector<Node *> content) {
	Clan result;
	result.nodes = content;
	sort(input.begin(), input.end());
	sort(content.begin(), content.end());

	for (Node * n : result.nodes) {
		// Find max value
		result.value = max(result.value, n->value());

		// Find offspring
		Node * left = n->leftChild();
		if (left != nullptr && !binary_search(result.nodes.begin(),
					result.nodes.end(), left)) {
			result.offspring.push_back(left);
		}
		Node * right = n->rightChild();
		if (right != nullptr && !binary_search(result.nodes.begin(),
					result.nodes.end(), right)) {
			result.offspring.push_back(right);
		}
	}

	// Find poor relation
	for (Node * n : input) {
		if (!binary_search(result.nodes.begin(), result.nodes.end(),
					n)) {
			result.poorRelation.push_back(n);
		}
	}

	return result;
}
