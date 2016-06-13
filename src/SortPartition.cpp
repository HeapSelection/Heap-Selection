#include "SortPartition.h"

void SortPartition::partition(int, vector<Node *> & nodes) {
	sort(nodes.begin(), nodes.end(), InverseNodeComparator());
}
