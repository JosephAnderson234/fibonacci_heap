#include <iostream>

using namespace std;

struct Node {
	int key;
	int degree;
	bool marked;

	Node* parent;
	Node* child;
	Node* left;
	Node* right;
	Node(int k) : key(k), degree(0), marked(false), parent(nullptr), child(nullptr), left(this), right(this) {}
};

class FibonacciHeap {
	int n = 0;
	Node* min = nullptr;
	Node* root_list = nullptr;


	void merge_with_root_list(Node* node) {
		if (root_list == nullptr) {
			root_list = node;
		} else {
			node->right = root_list;
			node->left = root_list->left;
			root_list->left->right = node;
			root_list->left = node;
		}
	}
public:
	//getters
	int getN() {
		return n;
	}

	Node* getMin () {
		return min;
	}

	Node* getRootList() {
		return root_list;
	}

	//setters
	void setN(int newN) {
		n = newN;
	}
	void setMin(Node* newMin) {
		min = newMin;
	}
	void setRootList(Node* newRootList) {
		root_list = newRootList;
	}

	Node* insert(int key) {
		Node* newNode = new Node(key);
		newNode->left = newNode;
		newNode->right = newNode;

		merge_with_root_list(newNode);

		if (min == nullptr || newNode->key < min->key) {
			min = newNode;
		}
		n++;
		return newNode;
	}

	FibonacciHeap* mergeFibos(FibonacciHeap* other) {
		FibonacciHeap* newHeap = new FibonacciHeap();
		newHeap->setRootList(root_list);
		if (min->key < other->getMin()->key) {
			newHeap->setMin(min);
		} else {
			newHeap->setMin(other->getMin());
		}

		Node* last = other->getRootList()->left;
		other->getRootList()->left = newHeap->getRootList()->left;
		newHeap->getRootList()->left->right = other->getRootList();
		newHeap->getRootList()->left = last;
		newHeap->getRootList()->left->right = newHeap->getRootList();

		newHeap->setN(n + other->getN());
		return newHeap;
	}
};

int main() {
	return 0;
}