#include "OptimizedCLRSMedianPartition2.h"

#define MIN(x, y) (x->value() < y->value() ? x : y)
#define MAX(x, y) (x->value() < y->value() ? y : x)
#define SWAP(x, y) { \
	Node *a = MIN(nodes[x], nodes[y]); \
	Node *b = MAX(nodes[x], nodes[y]); \
	nodes[x] = a; \
	nodes[y] = b; \
}

static __inline void sort52(Node **nodes) {
	SWAP(0, 1);
	SWAP(1, 2);
	SWAP(2, 3);
	SWAP(0, 1);
	SWAP(1, 2);
	SWAP(3, 4);
	SWAP(0, 1);
	SWAP(2, 3);
	SWAP(1, 2);
}

#undef SWAP
#undef MIN
#undef MAX

void OptimizedCLRSMedianPartition2::partition(int k, vector<Node *> &nodes) {
	size_t low = 0;
	size_t high = nodes.size();
	while (low < high) {
		size_t index = low;
		SELECT(nodes, low, high);
		swap(nodes[low], nodes[high - 1]);
		size_t i = low - 1;
		for (size_t j = low; j < high - 1; j++) {
			if (nodes[j]->value() <= nodes[high - 1]->value()) {
				i++;
				swap(nodes[i], nodes[j]);
			}
		}
		swap(nodes[i + 1], nodes[high - 1]);
		index = i + 1;
		if (index < (size_t) k) {
			low = index + 1;
		} else if (index > (size_t) k) {
			high = index;
		} else {
			break;
		}
	}
}

void OptimizedCLRSMedianPartition2::SELECT(vector<Node *> &nodes, size_t low, size_t high) {
	size_t remaining = high - low;
	while (remaining > 1) {
		size_t index = low;
		size_t extra = remaining % 5;
		for (size_t i = 0; i < remaining; i += 5, index++) {
			if (i + 5 <= remaining) {
				sort52(&nodes[i + low]);
				swap(nodes[index], nodes[low + i + 2]);
			} else {
				sort(nodes.begin() + i + low, nodes.begin() + low + remaining,
						InverseNodeComparator());
				swap(nodes[index], nodes[low + i + (extra - 1) / 2]);
			}
		}
		remaining /= 5;
		if (extra != 0) {
			remaining++;
		}
	}
}
