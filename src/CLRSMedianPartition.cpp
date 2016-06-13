#include "CLRSMedianPartition.h"

void CLRSMedianPartition::partition(int k, vector<Node *> &nodes) {
	size_t low = 0;
	size_t high = nodes.size();
	while (low < high) {
		size_t index = low;
		SELECT(nodes, low, high);
		swap(nodes[low], nodes[high - 1]);
		/*
//		for (size_t i = low; i < high; i++) {
		for (size_t i = 0; i < nodes.size(); i++) {
			cout << nodes[i]->value() << " ";
		}
		cout << endl;
//		*/
		/*
		cout << low << "\t" << index << "\t" << high << "\t" << k << endl;
		cout << "Pivot value:\t" << nodes[index]->value() << endl;
//		*/
//		cout << "elegiggle" << endl;
		size_t i = low - 1;
		for (size_t j = low; j < high - 1; j++) {
			if (nodes[j]->value() <= nodes[high - 1]->value()) {
				i++;
				swap(nodes[i], nodes[j]);
			}
		}
		swap(nodes[i + 1], nodes[high - 1]);
		index = i + 1;
		/*
		for (size_t i = low + 1; i < high; i++) {
			if (nodes[index]->value() >= nodes[i]->value()) {
				swap(nodes[index], nodes[i]);
				index = i;
			}
		}
		*/
//		cout << "New index:\t" << index << endl;
		/*
//		for (size_t i = low; i < high; i++) {
		for (size_t i = 0; i < nodes.size(); i++) {
			cout << nodes[i]->value() << " ";
		}
		cout << endl;
//		*/
		if (index < (size_t) k) {
			low = index + 1;
//			cout << "Too small:\t" << index << "\t" << k << endl;
		} else if (index > (size_t) k) {
			high = index;
//			cout << "Too large:\t" << index << "\t" << k << endl;
		} else {
			break;
		}
	}
}

void CLRSMedianPartition::SELECT(vector<Node *> &nodes, size_t low, size_t high) {
	size_t remaining = high - low;
	while (remaining > 1) {
		size_t index = low;
		size_t extra = remaining % 5;
		for (size_t i = 0; i < remaining; i += 5, index++) {
			if (i + 5 <= remaining) {
				sort(nodes.begin() + i + low, nodes.begin() + i + low + 5,
						InverseNodeComparator());
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
