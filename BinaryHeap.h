#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

struct BHNode {
	int key;
	int vertex;

	BHNode(int k, int v) : key(k), vertex(v) {}
};

class BinaryHeap {
	vector<BHNode> heap;
	unordered_map<int, int> pos; // vertex -> index in heap

	void swap_nodes(int i, int j) {
		swap(heap[i], heap[j]);
		pos[heap[i].vertex] = i;
		pos[heap[j].vertex] = j;
	}

	void heapify_up(int i) {
		while (i > 0) {
			int parent = (i - 1) / 2;
			if (heap[i].key < heap[parent].key) {
				swap_nodes(i, parent);
				i = parent;
			} else break;
		}
	}

	void heapify_down(int i) {
		int n = heap.size();
		while (true) {
			int smallest = i;
			int l = 2 * i + 1;
			int r = 2 * i + 2;
			if (l < n && heap[l].key < heap[smallest].key) smallest = l;
			if (r < n && heap[r].key < heap[smallest].key) smallest = r;

			if (smallest != i) {
				swap_nodes(i, smallest);
				i = smallest;
			} else break;
		}
	}

public:
	bool empty() const {
		return heap.empty();
	}

	void insert(int vertex, int key) {
		heap.emplace_back(key, vertex);
		pos[vertex] = heap.size() - 1;
		heapify_up(heap.size() - 1);
	}

	int extract_min() {
		if (heap.empty()) return -1;
		int minVertex = heap[0].vertex;
		pos.erase(minVertex);
		heap[0] = heap.back();
		heap.pop_back();
		if (!heap.empty()) {
			pos[heap[0].vertex] = 0;
			heapify_down(0);
		}
		return minVertex;
	}

	void decrease_key(int vertex, int new_key) {
		int i = pos[vertex];
		if (heap[i].key > new_key) {
			heap[i].key = new_key;
			heapify_up(i);
		}
	}
};

#endif // BINARYHEAP_H
