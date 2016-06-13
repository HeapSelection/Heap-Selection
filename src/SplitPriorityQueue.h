#pragma once

#include <queue>
#include <vector>

/*
Sneaky access to the underlying vector of the priority queue.
It's used for deleting pointers in the queue, which we want done
in linear time.

See: https://stackoverflow.com/questions/1185252/is-there-a-way-to-access-the-underlying-container-of-stl-container-adaptors
*/
template <class T, class S, class C>
S& Container(priority_queue<T, S, C>& q) {
	struct HackedQueue : private priority_queue<T, S, C> {
		static S& Container(priority_queue<T, S, C>& q) {
			return q.*&HackedQueue::c;
		}
	};
	return HackedQueue::Container(q);
}

template<class E, class C>
class SplitPriorityQueue {
public:
	SplitPriorityQueue<E, C>();
	SplitPriorityQueue(std::priority_queue<E, std::vector<E>, C>);
	~SplitPriorityQueue();
	std::size_t size();
	E extractMin();
	void insert(E);
	SplitPriorityQueue<E, C> * split();

private:
	std::priority_queue<E, std::vector<E>, C> a, b;
};

template<class E, class C>
SplitPriorityQueue<E, C>::SplitPriorityQueue() {}

template<class E, class C>
SplitPriorityQueue<E, C>::SplitPriorityQueue(std::priority_queue<E, std::vector<E>, C> c) {
	a = c;
}

template<class E, class C>
SplitPriorityQueue<E, C>::~SplitPriorityQueue() {
	vector<E> &as = Container(a);
	for (E e : as) {
		delete e;
	}
	vector<E> &bs = Container(b);
	for (E e : bs) {
		delete e;
	}
}

template<class E, class C>
std::size_t SplitPriorityQueue<E, C>::size() {
	return a.size() + b.size();
}

template<class E, class C>
E SplitPriorityQueue<E, C>::extractMin() {
	if (b.empty()) {
		E result = a.top();
		a.pop();
		return result;
	}

	if (a.empty()) {
		E result = b.top();
		b.pop();
		return result;
	}

	if (a.top()->value < b.top()->value) {
		E result = a.top();
		a.pop();
		return result;
	} else {
		E result = b.top();
		b.pop();
		return result;
	}
}

template<class E, class C>
void SplitPriorityQueue<E, C>::insert(E e) {
	if (a.size() < b.size()) {
		a.push(e);
	} else {
		b.push(e);
	}
}

template<class E, class C>
SplitPriorityQueue<E, C> * SplitPriorityQueue<E, C>::split() {
	SplitPriorityQueue<E, C> *result = new SplitPriorityQueue<E, C>(b);
	b = std::priority_queue<E, std::vector<E>, C>();
	return result;
}