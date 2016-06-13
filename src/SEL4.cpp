#include "SEL4.h"

static vector<SPQ4 *> pq4s;

Clan4::Clan4(Node *node, SPQ4 *pq, int category)
	: node(node), pq(pq), category(category) {
	value = node->value();
}

Clan4::~Clan4() {
}

int SEL4::f(int r) {
	double numerator = ceil(log2(r));
	int denominator = utility.iteratedLog(r);
	return (int) floor(pow(numerator / denominator, 2));
}

int SEL4::h(int r) {
	if (r == 1) {
		return 1;
	}
	auto hFR = h(f(r));
	return hFR * (int) ceil(r / (double) hFR);
}

vector<Node *> SEL4::selectK(int k, Node *node) {
	auto highestClan = RSEL4(node, nullptr, k);
	dataType highest = highestClan->value;
	auto possible = utility.findUpTo(highest, k, node);
	delete highestClan;
	for (SPQ4 *pq : pq4s) {
		delete pq;
	}
	pq4s.clear();
	partition.partition(k, possible);
	possible.resize(k);
	return possible;
}

Clan4 * SEL4::RSEL4(Node *H0, SPQ4 *H, int r) {
	if (r <= baseCase) {
		Clan4 *pc = nullptr;
		for (int i = 0; i < r; i++) {
			if (H == nullptr) {
				H = new SPQ4();
				pq4s.push_back(H);
				pc = new Clan4(H0, H, 1);
			} else {
				pc = H->extractMin();
			}
			Node *left = pc->node->leftChild();
			Clan4 *pc1 = new Clan4(left, H, 1);
			H->insert(pc1);
			Node *right = pc->node->rightChild();
			Clan4 *pc2 = new Clan4(right, H, 1);
			H->insert(pc2);
			pc->pq = H;
			if (i < r - 1) {
				delete pc;
			}
		}
		return pc;
	}
	if (H == nullptr) {
		Clan4 *pc = RSEL4(H0, H, (int) floor(f(r)));
		pc->category = 1;
		H = new SPQ4();
		pq4s.push_back(H);
		H->insert(pc);
	}
	const int limit = h(r) / h(f(r));
	const int catLimit = (int) pow(utility.iteratedLog(r), 2) * catFactor;
	Clan4 *last = nullptr;
	for (int i = 0; i < limit; i++) {
		Clan4 *pc = last = H->extractMin();
		if (pc->category < catLimit) {
			Clan4 *pc1 = RSEL4(H0, pc->pq, f(r));
			pc1->category = pc->category + 1;
			H->insert(pc1);
		} else {
			SPQ4 *pq1 = pc->pq;
			SPQ4 *pq2 = pq1->split();
			pq4s.push_back(pq2);
			Clan4 *pc1 = RSEL4(H0, pq1, f(r));
			pc1->category = 1;
			H->insert(pc1);
			Clan4 *pc2 = RSEL4(H0, pq2, f(r));
			pc2->category = 1;
			H->insert(pc2);
		}
		if (i < limit - 1) {
			delete pc;
		}
	}
	last->pq = H;
	return last;
}

double SEL4::asymptotic(int k) {
	return k;
}
