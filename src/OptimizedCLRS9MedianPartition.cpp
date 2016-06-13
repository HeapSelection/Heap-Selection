#include "OptimizedCLRS9MedianPartition.h"

#define MIN(x, y) (x->value() < y->value() ? x : y)
#define MAX(x, y) (x->value() < y->value() ? y : x)
#define SWAP(x, y) { \
	COMP \
	COMP \
	Node *a = MIN(nodes[x], nodes[y]); \
	Node *b = MAX(nodes[x], nodes[y]); \
	nodes[x] = a; \
	nodes[y] = b; \
}

static __inline void sort9(Node **nodes) {
	SWAP(0, 3);
	SWAP(1, 4);
	SWAP(0, 1);
	SWAP(2, 5);
	SWAP(0, 2);
	SWAP(4, 5);
	SWAP(1, 2);
	SWAP(3, 5);
	SWAP(3, 4);
	SWAP(1, 3);
	SWAP(1, 6);
	SWAP(4, 6);
	SWAP(2, 6);
	SWAP(2, 3);
	SWAP(4, 7);
	SWAP(2, 4);
	SWAP(3, 7);
	SWAP(4, 8);
	SWAP(3, 8);
	SWAP(3, 4);
}

#undef SWAP
#undef MIN
#undef MAX

void OptimizedCLRS9MedianPartition::partition(int k, vector<Node *> &nodes) {
	COMP
	if ((size_t) k == nodes.size()) {
		return;
	}
	COMP
	if ((size_t) k > nodes.size()) {
		cerr << "Too few elements found!" << endl;
		return;
	}
	size_t low = 0;
	size_t high = nodes.size();
	while (low < high) {
		COMP
//		cout << k << "\t" << low << "\t" << high << endl;
		size_t index = low;
		SELECT(nodes, low, high);
		swap(nodes[low], nodes[high - 1]);
		size_t i = low - 1;
		for (size_t j = low; j < high - 1; j++) {
			COMP
			COMP
			if (nodes[j]->value() <= nodes[high - 1]->value()) {
				i++;
				swap(nodes[i], nodes[j]);
			}
		}
		swap(nodes[i + 1], nodes[high - 1]);
		index = i + 1;
		COMP
		if (index < (size_t) k) {
			low = index + 1;
		} else if (index >(size_t) k) {
			COMP
			high = index;
		} else {
			COMP
			break;
		}
	}
}

void OptimizedCLRS9MedianPartition::SELECT(vector<Node *> &nodes, size_t low, size_t high) {
	size_t remaining = high - low;
	while (remaining > 1) {
		COMP
		size_t index = low;
		size_t extra = remaining % 9;
		for (size_t i = 0; i < remaining; i += 9, index++) {
			COMP
			if (i + 9 <= remaining) {
				sort9(&nodes[i + low]);
				COMP
				swap(nodes[index], nodes[low + i + 4]);
			} else {
				sort(nodes.begin() + i + low, nodes.begin() + low + remaining,
						InverseNodeComparator());
				COMP
				swap(nodes[index], nodes[low + i + (extra - 1) / 2]);
			}
		}
		remaining /= 9;
		COMP
		if (extra != 0) {
			remaining++;
		}
	}
}
