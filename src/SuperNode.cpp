#include "SuperNode.h"

using namespace std;

SuperNode::SuperNode(Node *node, int id) : node(node), id(id) {
	value = node->value();
}