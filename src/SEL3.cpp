#include "SEL3.h"

vector<SPQ3 *> pqs;

PClan::PClan(Node *node, SPQ3 *pq) : node(node), pq(pq) {
	value = node->value();
}

PClan::~PClan() {
}

int SEL3::h(int r) {
	COMP
	if (r == 1) {
		return 1;
	}
	auto hLogR = h((int) floor(log2(r)));
	return hLogR * (int) ceil(r / (double) hLogR);
}

vector<Node *> SEL3::selectK(int k, Node *node) {
	auto highestClan = RSEL3(node, nullptr, k);
	auto possible = utility.findUpTo(highestClan->node->value(), k, node);
	delete highestClan;
	partition.partition(k, possible);
	possible.resize(k);
	for (SPQ3 *pq : pqs) {
		COMP;
		delete pq;
	}
	pqs.clear();
	return possible;
}

PClan * SEL3::RSEL3(Node *H0, SPQ3 *H, int r) {
	COMP;
	if (r == 1) {
		COMP;
		if (H == nullptr) {
			H = new SPQ3();
			pqs.push_back(H);
			PClan *result = new PClan(H0, H);
			Node *left = H0->leftChild();
			PClan *pc1 = new PClan(left, H);
			result->pq->insert(pc1);
			Node *right = H0->rightChild();
			PClan *pc2 = new PClan(right, H);
			result->pq->insert(pc2);
			return result;
		}

		PClan *pc = H->extractMin();
		Node *left = pc->node->leftChild();
		PClan *pc1 = new PClan(left, H);
		H->insert(pc1);
		Node *right = pc->node->rightChild();
		PClan *pc2 = new PClan(right, H);
		H->insert(pc2);
		pc->pq = H;
		return pc;
	}
	COMP;
	if (H == nullptr) {
		PClan *pc = RSEL3(H0, H, (int) log2(r));
		H = new SPQ3();
		pqs.push_back(H);
		H->insert(pc);
	}
	int limit = (int) h(r) / h((int) log2(r));
	PClan *last = nullptr;
	for (int i = 0; i < limit; i++) {
		COMP;
		PClan *pc = last = H->extractMin();
		SPQ3 *pq1 = pc->pq;
		SPQ3 *pq2 = pq1->split();
		pqs.push_back(pq2);
		PClan *pc1 = RSEL3(H0, pq1, (int) log2(r));
		H->insert(pc1);
		PClan *pc2 = RSEL3(H0, pq2, (int) log2(r));
		H->insert(pc2);
		if (i < limit - 1) {
			delete pc;
		}
	}
	last->pq = H;
	return last;
}

double SEL3::asymptotic(int k) {
	return k * pow(2, utility.iteratedLog(k));
}
