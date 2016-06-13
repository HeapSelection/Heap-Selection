#include "Clan.h"

string Clan::toString() {
	stringstream ss;
	ss << "Value: " << value;
	ss << " Nodes: [ ";
	for (Node * n : nodes) {
		ss << n->value() << " ";
	}
	ss << "] Offspring: [ ";
	for (Node * n : offspring) {
		ss << n->value() << " ";
	}
	ss << "] PoorRelation: [ ";
	for (Node * n : poorRelation) {
		ss << n->value() << " ";
	}
	ss << "]";
	return ss.str();
}
