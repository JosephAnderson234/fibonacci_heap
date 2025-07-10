#include "FibonacciHeap.h"
#include <iostream>

using namespace std;

int main() {
	FibonacciHeap fibHeap;
	fibHeap.insert(10);
	fibHeap.insert(20);
	fibHeap.insert(5);

	cout << "Minimum key in Fibonacci Heap: " << fibHeap.getMin()->key << endl;

	FibonacciHeap* otherHeap = new FibonacciHeap();
	otherHeap->insert(1);
	otherHeap->insert(15);
	otherHeap->insert(25);

	FibonacciHeap* mergedHeap = fibHeap.mergeFibos(otherHeap);
	cout << "Minimum key after merging: " << mergedHeap->getMin()->key << endl;

	delete otherHeap;
	delete mergedHeap;

	return 0;
}