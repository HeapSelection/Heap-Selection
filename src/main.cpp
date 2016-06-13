#include "main.h"

using namespace std;
using namespace std::chrono;

enum TreeType {
	lazy,
	lazySpine,
	incremental,
	worst,
	sparse,
	one,
	TREE_TYPE_MAX
} treeType = worst;

enum SelectType {
	naive,
	sel1,
	sel2,
	sel3,
	sel4,
	SELECT_TYPE_MAX
} selectType = naive;

enum PartitionType {
	random_,
	sorting,
	fake,
	clrs,
	optimizedClrs,
	optimizedClrs2,
	optimizedClrs3,
	optimizedClrs9,
	PARTITION_TYPE_MAX
} partitionType = optimizedClrs9;

enum ForgerType {
	sortForger,
	scanForger,
	FORGER_TYPE_MAX
} forgerType = sortForger;

enum RunType {
	normal,
	solorun,
	solobase,
	correctness,
	partitionTiming,
	cross,
	RUN_TYPE_MAX
} runType = normal;

int soloK = 10;

void handleArgs(int, char *[]);
void benchmark();
void testPartition();
void testCorrectness();
void solo(bool);
void crossBenchmark();

Node * createNode();
Select & createSelect();
Partition & createPartition();
ClanForger & createClanForger();

Node * createNode(TreeType);
Select & createSelect(SelectType, PartitionType);
Partition & createPartition(PartitionType);
ClanForger & createClanForger(ForgerType);

string selectString(int);
string partitionString(int);

int main(int argc, char *argv[]) {
	handleArgs(argc, argv);
	if (runType == correctness) {
		testCorrectness();
	} else if (runType == partitionTiming) {
		testPartition();
	} else if (runType == solobase) {
		solo(true);
	} else if (runType == solorun) {
		solo(false);
	} else if (runType == cross) {
		crossBenchmark();
	} else {
		benchmark();
	}
	//testPartition();
}

void handleArgs(int argc, char *argv[]) {
	vector<string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(string(argv[i]));
	}
	for (size_t i = 0; i < args.size(); i++) {
		string s = args[i];
		if (s == "lazy") { // Tree
			treeType = lazy;
		} else if (s == "spine") {
			treeType = lazySpine;
		} else if (s == "incremental") {
			treeType = incremental;
		} else if (s == "worst") {
			treeType = worst;
		} else if (s == "sparse") {
			treeType = sparse;
		} else if (s == "one") {
			treeType = one;
		} else if (s == "clan" || s == "sel1") { // Select
			selectType = sel1;
		} else if (s == "recclan" || s == "sel2") {
			selectType = sel2;
		} else if (s == "sel3") {
			selectType = sel3;
		} else if (s == "sel4") {
			selectType = sel4;
		} else if (s == "naive") {
			selectType = naive;
		} else if (s == "sort") { // Partition
			partitionType = sorting;
		} else if (s == "fake") {
			partitionType = fake;
		} else if (s == "clrs") {
			partitionType = clrs;
		} else if (s == "optimizedclrs") {
			partitionType = optimizedClrs;
		} else if (s == "optimizedclrs2") {
			partitionType = optimizedClrs2;
		} else if (s == "optimizedclrs3") {
			partitionType = optimizedClrs3;
		} else if (s == "optimizedclrs9" || s == "best") {
			partitionType = optimizedClrs9;
		} else if (s == "sortforge") { // Forger
			forgerType = sortForger;
		} else if (s == "correctness") { // Other
			runType = correctness;
		} else if (s == "partition") {
			runType = partitionTiming;
		} else if (s == "solobase") {
			runType = solobase;
			i++;
			stringstream(args[i]) >> soloK;
		} else if (s == "solo") {
			runType = solorun;
			i++;
			stringstream(args[i]) >> soloK;
		} else if (s == "size") {
			i++;
			stringstream(args[i]) >> soloK;
		} else if (s == "cross") {
			runType = cross;
		} else {
			cerr << "Unknown arg: " << s << endl;
		}
	}
}

void crossBenchmark() {
	const int k = 1000000;
	Node *root = createNode();
	NaiveSelect naive;
	naive.selectK(k, root);
	OptimizedCLRS9MedianPartition partition;
	vector<int> baseCase = {1, 2, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 180, 200};
	vector<double> catFactor = {0.6, 0.7, 0.8, 0.9, 1, 2, 3, 4, 5, 6};
	size_t minAccess = 1000000000;
	size_t minCompares = 1000000000;
	int bestAccBase = 0, bestComBase = 0;
	size_t accCom = 0, comAcc = 0;
	double bestAccCat = 0, bestComCat = 0;
	cout << setprecision(3);
	for (size_t i = 0; i < baseCase.size(); i++) {
		for (size_t j = 0; j < catFactor.size(); j++) {
			SEL4 sel4(partition, baseCase[i], catFactor[j]);
			accesses = 0;
			compares = 0;
			auto start = high_resolution_clock::now();
			sel4.selectK(k, root);
			auto end = high_resolution_clock::now();
			auto time = duration_cast<microseconds>(end - start).count();
			if (compares < minCompares) {
				minCompares = compares;
				bestComBase = baseCase[i];
				bestComCat = catFactor[j];
				comAcc = accesses;
			}
			if (accesses < minAccess) {
				minAccess = accesses;
				bestAccBase = baseCase[i];
				bestAccCat = catFactor[j];
				accCom = compares;
			}
			cout << baseCase[i] << "\t" << catFactor[j] << "\t" << accesses
				<< "\t" << compares << "\t" << time << endl;
		}
	}
	cout << "Best comparison" << endl;
	cout << bestComBase << "\t" << bestComCat << "\t" << minCompares << "\t" << comAcc << "\t" << endl;
	cout << "Best accesses" << endl;
	cout << bestAccBase << "\t" << bestAccCat << "\t" << minAccess << "\t" << accCom << "\t" << endl;
	delete root;
}

void solo(bool base) {
	Node *root = createNode();
	NaiveSelect ns;
	vector<Node *> result1 = ns.selectK(soloK, root);
	Select &select = createSelect();
	vector<Node *> result2 = select.selectK(soloK, root);
	if (!base) {
		vector<Node *> result3 = select.selectK(soloK, root);
	}
	delete root;
}

void benchmark() {
	const int early = 1 << 10;
#if defined(_COMPARE) || defined(_ACCESS)
	const int sample = 1;
#else
	const int sample = 5;
#endif
	cout << selectString(selectType) << endl;
	cout << "k" << "\t"
		<< "log" << "\t"
#ifdef _COMPARE
		<< "comp" << "\t"
		<< "asympcomp" << "\t"
#endif
#ifdef _ACCESS
		<< "access" << "\t"
		<< "asympaccess" << "\t"
#endif
		<< "time" << "\t"
		<< "asymptime" << "\t"
		<< endl;
	for (int kk = early; kk <= soloK; kk *= 2) {
		if (kk > 100000 && selectType == sel2) {
			continue;
		}
		for (int l = 0; l < 3; l++) {
			int k = kk;
			if (l == 1) {
				k = (int) (k * 1.2599210498948731647642995715334); // 1/3 distance on a log2 scale
			} else if (l == 2) {
				k = (int) (k * 1.5874010519681994747516322857681); // 2/3 distance on a log2 scale
			}

			r = mt19937(42);
			Node * root = createNode();
			Select &select = createSelect();

			auto t1 = high_resolution_clock::now();
			auto t2 = high_resolution_clock::now();
			auto t3 = t2 - t1;

			auto best = duration_cast<milliseconds>(t3).count();

			best = 1000 * 1000 * 1000;

			//		/*
			{
				NaiveSelect ns;
				vector<Node *> result2 = ns.selectK(k, root);
			}
			//		*/
			for (auto _ = 0; _ < sample; _++) {
#ifdef _COMPARE
				compares = 0;
#endif
#ifdef _ACCESS
				accesses = 0;
#endif
				auto start = high_resolution_clock::now();
				auto t2 = high_resolution_clock::now();
				auto t3 = t2 - start;
				auto time = duration_cast<microseconds>(t3).count();
				int rounds = 1;
				int completed = 0;
				while (true) {
					for (int round = 0; round < rounds; round++) {
						vector<Node *> result = select.selectK(k, root);
					}
					completed += rounds;
					auto end = high_resolution_clock::now();
					auto spent = end - start;
					time = duration_cast<microseconds>(spent).count();
					if (time > 100000) {
						time /= completed;
#ifdef _COMPARE
						compares /= completed;
#endif
#ifdef _ACCESS
						accesses  /= completed;
#endif
						break;
					}
					rounds *= 2;
				}

				best = min(best, time);
			}

			double asymptotic = select.asymptotic(k);


			cout
				<< k << "\t"
				<< log2(k) << "\t"
#ifdef _COMPARE
				<< compares << "\t"
				<< (compares / asymptotic) << "\t"
#endif
#ifdef _ACCESS
				<< accesses << "\t"
				<< (accesses / asymptotic) << "\t"
#endif
				<< best << "\t"
				<< (best / asymptotic) << "\t"
				<< endl;

			delete root;
		}
	}
}

void testPartition() {
	const int sample = 1;
	Partition &p = createPartition();
	const int a = 1 << 18;
	uniform_int_distribution<int> d(1, a);
	for (int i = 1 << 2; i <= a; i *= 2) {
		auto t1 = high_resolution_clock::now();
		auto t2 = high_resolution_clock::now();
		auto t3 = t2 - t1;

		auto best = duration_cast<milliseconds>(t3).count();

		best = 1000 * 1000 * 1000;
		for (int k = 0; k < sample; k++) {
			vector<Node *> nodes;
			nodes.reserve(i);
			r = mt19937(42);
			for (int j = 0; j < i; j++) {
				nodes.push_back(new LazyNode(d(r)));
			}

			auto start = high_resolution_clock::now();
			p.partition(i / 2, nodes);
			auto end = high_resolution_clock::now();
			auto spent = end - start;
			auto time = duration_cast<milliseconds>(spent).count();

			for (Node * n : nodes) {
				delete n;
			}
			best = min(best, time);
		}

		cout << i << "\t"
			<< best << "\t"
			<< (best / (double) i) << endl;
	}
}

Node * createNode() {
	return createNode(treeType);
}

Node * createNode(TreeType treeType) {
	if (treeType == lazySpine) {
		return new LazySpineNode(1);
	}
	if (treeType == incremental) {
		return new IncrementalNode(1);
	}
	if (treeType == worst) {
		return new WorstSpineNode(1, 1000 * 1000 * 1000);
	}
	if (treeType == sparse) {
		return new SparseNode(1);
	}
	if (treeType == one) {
		return new OneNode();
	}
	return new LazyNode(1);
}

Partition & createPartition() {
	return createPartition(partitionType);
}

Partition & createPartition(PartitionType partitionType) {
	if (partitionType == sorting) {
		return *new SortPartition();
	}
	if (partitionType == fake) {
		return *new FakePartition();
	}
	if (partitionType == clrs) {
		return *new CLRSMedianPartition();
	}
	if (partitionType == optimizedClrs) {
		return *new OptimizedCLRSMedianPartition();
	}
	if (partitionType == optimizedClrs2) {
		return *new OptimizedCLRSMedianPartition2();
	}
	if (partitionType == optimizedClrs3) {
		return *new OptimizedCLRSMedianPartition3();
	}
	if (partitionType == optimizedClrs9) {
		return *new OptimizedCLRS9MedianPartition();
	}
	return *new RandomPartition();
}

Select & createSelect() {
	return createSelect(selectType, partitionType);
}

Select & createSelect(SelectType selectType, PartitionType partitionType) {
	if (selectType == sel1) {
		return *new SEL1(createPartition(partitionType));
	}
	if (selectType == sel2) {
		return *new SEL2(createPartition(partitionType));
	}
	if (selectType == sel3) {
		return *new SEL3(createPartition(partitionType));
	}
	if (selectType == sel4) {
		return *new SEL4(createPartition(partitionType));
	}
	return *new NaiveSelect();
}

ClanForger & createClanForger() {
	return createClanForger(forgerType);
}

ClanForger & createClanForger(ForgerType forgerType) {
	if (forgerType == sortForger) {
		return *new SortClanForger();
	}
	return *new ScanClanForger();
}

void testCorrectness() {
//	const int a = 4;
	const int a = soloK;
//	const int b = max(a / 17, 1);
	const int b = a;
	r = mt19937(42);
	Node *root = createNode();
	for (int i = b; i <= a; i += b) {
		remaining = i - 2;
//		remaining = 6;
		NaiveSelect base;
		vector<Node *> expected = base.selectK(i, root);
		sort(expected.begin(), expected.end(), NodeComparator());
		for (int j = 0; j < SELECT_TYPE_MAX; j++) {
			if (j != sel4) {
				//continue;
			}
			for (int k = 0; k < PARTITION_TYPE_MAX; k++) {
			//	if (k == fake || k != clrs) {
				if (k != optimizedClrs9) {
					continue;
				}
				cout << "Testing " << selectString(j) << " "
					<< partitionString(k) << " size " << i << endl;
				bool ok = true;
				Select &test = createSelect((SelectType) j, (PartitionType) k);
				vector<Node *> result = test.selectK(i, root);
//				cout << result.size() << endl;
				sort(result.begin(), result.end(), NodeComparator());
				if (expected.size() != result.size()) {
					ok = false;
				}
				if (ok) {
					for (int l = 0; l < b; l++) {
						if (expected[l]->value() != result[l]->value()) {
							ok = false;
						}
					}
				}
				/*
				for (Node * n : expected) {
					cout << n->value() << " ";
				}
				cout << endl;
				for (Node * n : result) {
					cout << n->value() << " ";
				}
				cout << endl;
//				*/
//				/*
				if (!ok) {
					cout << selectString(j) << " "
						<< partitionString(k)
						<< " does not work: ";
					if (expected.size() != result.size() ) {
						cout << "Sizes differ: " << expected.size()
							<< " vs " << result.size();
					} else {
						cout << "Elements do not match.";
					}
					cout << endl;
				}
//				*/
			}
		}
	}
	delete root;
}

string selectString(int type) {
	if (type == 0) {
		return "naive";
	}
	if (type == 1) {
		return "SEL1";
	}
	if (type == 2) {
		return "SEL2";
	}
	if (type == 3) {
		return "SEL3";
	}
	if (type == 4) {
		return "SEL4";
	}
	return "unknown";
}

string partitionString(int type) {
	if (type == 0) {
		return "random_";
	}
	if (type == 1) {
		return "sorting";
	}
	if (type == 2) {
		return "fake";
	}
	if (type == 3) {
		return "clrs";
	}
	if (type == 4) {
		return "clrs1";
	}
	if (type == 5) {
		return "clrs2";
	}
	if (type == 6) {
		return "clrs3";
	}
	if (type == 7) {
		return "clrs9";
	}
	return "unknown";
}
