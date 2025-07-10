
#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H
#include <cmath>
#include <stdexcept>
#include <vector>
#include <limits.h> // O #include <climits>


using namespace std;

struct Node {
	int key;
	int degree;
	bool marked=false;

	Node* parent;
	Node* child;
	Node* left;
	Node* right;
	Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), left(this), right(this) {}
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

	void remove_from_root_list(Node* node) {
        if (node == root_list) {
	        root_list = node->right;
        }
		node->left->right = node->right;
		node->right->left = node->left;
    }

	void remove_from_child_list(Node* parent, Node* node) {
		if (parent->child == parent->child->right) {
			parent->child = nullptr; // El único hijo se elimina
		} else if (parent->child == node) {
			parent->child = node->right; // Actualiza el hijo si es el primero
			node->right->parent = parent;
		}
		node->left->right = node->right; // Elimina el nodo de la lista
		node->right->left = node->left;
	}

	void consolidate() {
		int max_degree = static_cast<int>(std::log2(n)) + 1;
		vector<Node*> A(max_degree + 1, nullptr);

		vector<Node*> roots;
		Node* current = root_list;
		if (current == nullptr) return;


		do {
			roots.push_back(current);
			current = current->right;
		} while (current != root_list);

		for (Node* w : roots) {
			Node* x = w;
			int d = x->degree;

			while (A[d] != nullptr) {
				Node* y = A[d];
				if (x->key > y->key) swap(x, y);

				// y se convierte en hijo de x
				remove_from_root_list(y);
				if (x->child == nullptr) {
					x->child = y;
					y->left = y;
					y->right = y;
				} else {
					y->left = x->child;
					y->right = x->child->right;
					x->child->right->left = y;
					x->child->right = y;
				}
				y->parent = x;
				x->degree++;
				y->marked = false;

				A[d] = nullptr;
				d++;
			}
			A[d] = x;
		}

		// Reconstruir la nueva lista raíz y encontrar el nuevo mínimo
		min = nullptr;
		root_list = nullptr;

		for (Node* node : A) {
			if (node != nullptr) {
				node->left = node->right = node;
				node->parent = nullptr;
				merge_with_root_list(node);
				if (min == nullptr || node->key < min->key) {
					min = node;
				}
			}
		}
	}



	void cut(Node* x, Node* y) {
		remove_from_child_list(y, x);
		y->degree--;
		merge_with_root_list(x);
		x->parent = nullptr;
		x->marked = false;
    }

	void cascading_cut(Node* y) {
        Node* z = y->parent;
        if (z != nullptr) {
            if (!y->marked) {
                y->marked = true;
            } else {
                cut(y, z);
                cascading_cut(z);
            }
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

	Node* extract_min() {
		Node* z = min;
		if (z != nullptr) {
            if (z->child != nullptr) {
            	Node* child = z->child;
            	vector<Node*> children;
            	do {
            		children.push_back(child);
            		child = child->right;
            	} while (child != z->child);

            	for (Node* c : children) {
            		c->parent = nullptr;
            		merge_with_root_list(c);
            	}
            }
            remove_from_root_list(z);
            if (z == z->right) {
                min = nullptr;
            } else {
                min = z->right;
                consolidate();
            }
            n--;
        }
		return z;
	}

	void decrease_key(Node* x, int new_key) {
        if (new_key > x->key) {
            throw runtime_error("Nuevo valor mayor que el actual");
        }
        x->key = new_key;
        Node* y = x->parent;
		if (y != nullptr && x->key < y->key) {
			cut(x, y);
			cascading_cut(y);
        }
		if (x->key < min->key) {
            min = x;
        }
	}

	void delete_node(Node* x) {
        decrease_key(x, INT_MIN);
        delete extract_min();
    }
};
#endif //FIBONACCIHEAP_H
