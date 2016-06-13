#include "RandomPartition.h"

void RandomPartition::partition(int k, vector<Node *> & nodes) {
	//cout << "partition " << k << " " << nodes.size() << endl;
	size_t low = 0;
	size_t high = nodes.size() - 1;
	size_t mid = partition(nodes, low, high);
	while (low < high) {
		//cout << mid << endl;
		if (mid < (size_t) k) {
			low = mid + 1;
			mid = partition(nodes, low, high);
		} else if ((size_t) k < mid) {
			high = mid - 1;
			mid = partition(nodes, low, high);
		} else {
			break;
		}
	}
}

size_t RandomPartition::partition(vector<Node *> & nodes, size_t low, size_t high) {
	if (high <= low) {
		return low;
	}
	size_t lt = low;
	size_t gt = high;
	size_t mid = (high + low) / 2;
	/*
	cout << lt << "\t" << mid << "\t" << gt << endl;
	cout << nodes[lt]->value() << "\t"
		<< nodes[(lt + mid) / 2]->value() << "\t"
		<< nodes[mid]->value() << "\t"
		<< nodes[(mid + high) / 2]->value() << "\t"
		<< nodes[gt]->value() << endl;
	*/
	size_t i;
	vector<Node *> median;
	median.push_back(nodes[low]);
	median.push_back(nodes[(low + mid) / 2]);
	median.push_back(nodes[mid]);
	median.push_back(nodes[(mid + high) / 2]);
	median.push_back(nodes[high]);
	sort(median.begin(), median.end(), NodeComparator());
	if (median[median.size() / 2]->value() == nodes[low]->value()) {
		i = low;
	} else if (median[median.size() / 2]->value() == nodes[mid]->value()) {
		i = mid;
	} else if (median[median.size() / 2]->value() == nodes[mid]->value()) {
		i = mid;
	} else {
		i = high;
	}
//	cout << nodes[low]->value() << "\t" << nodes[mid]->value() << "\t"
//		<< nodes[high]->value() << "\t" << nodes[i]->value() << endl;
	swap(nodes[i], nodes[low]);
	i = low;
	Node *pivot = nodes[i];
	dataType pivotValue = pivot->value();
	while (i <= gt) {
		dataType diff = nodes[i]->value() - pivotValue;
		if (diff < 0) {
			swap(nodes[lt], nodes[i]);
			lt++;
			i++;
		} else if (0 < diff) {
			swap(nodes[i], nodes[gt]);
			gt--;
		} else {
			i++;
		}
	}
	return gt;
}
