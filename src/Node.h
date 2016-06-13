#pragma once

#include <iostream>

#include "dataType.h"
#include "test.h"

using namespace std;

class Node {
	public:
		dataType value() const {
			ACC
			return _value;
		}

		bool operator<(const Node &other) const {
			cout << "lel" << endl;
			return value() > other.value();
		}

		virtual Node * leftChild() = 0;
		virtual Node * rightChild() = 0;

		virtual ~Node() {}

		dataType _value;
		Node *_leftChild = nullptr;
		Node *_rightChild = nullptr;
};

struct NodeComparator {
	bool operator() (const Node * a, const Node * b) const {
		COMP
		return a->value() > b->value();
	}
};

struct InverseNodeComparator {
	bool operator() (const Node * a, const Node * b) const {
		COMP
		return a->value() < b->value();
	}
};
