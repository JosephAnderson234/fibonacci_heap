#include <iostream>
using namespace std;

struct Node {
	int key;
	Node* next;
	Node(int k) : key(k), next(nullptr) {}
};

class FibonacciHeap {
	Node* min = nullptr;

public:
	void insert(int key) {
		Node* node = new Node(key);
		if (!min || key < min->key)
			min = node;
		node->next = min;
	}

	int getMin() {
		if (!min) throw runtime_error("Heap vacío");
		return min->key;
	}
};

int main() {
	FibonacciHeap heap;
	heap.insert(5);
	heap.insert(2);
	heap.insert(8);
	cout << "Mínimo: " << heap.getMin() << endl;
	return 0;
}

