#include "../include/minheap.h"

void swap(Node* &a, Node* &b) {
	Node* temp = a;
	a = b;
	b = temp;
}

void push(Node* newNode, MinHeap* minHeap) {
	int i = minHeap->size;
	minHeap->node[i] = newNode;
	minHeap->size++;												

	while(i != 0 && minHeap->node[(i - 1) / 2]->time > minHeap->node[i]->time) {	
		swap(minHeap->node[i], minHeap->node[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

Node* pop(MinHeap* minHeap) {
	if(minHeap->size == 0) return nullptr;

	Node* min = minHeap->node[0];
	minHeap->node[0] = minHeap->node[minHeap->size - 1];
	minHeap->size--;

	int i = 0;
	while(true) {											
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int smallest = i;

		if (left < minHeap->size && minHeap->node[left]->time < minHeap->node[smallest]->time) smallest = left;
		if (right < minHeap->size && minHeap->node[right]->time < minHeap->node[smallest]->time) smallest = right;

		if (smallest == i) break;

		swap(minHeap->node[i], minHeap->node[smallest]);
		i = smallest;
	}
	return min;
}

void freeMinHeap(MinHeap* minHeap) {
	for (int i = 0; i < minHeap->size; i++) {
		delete minHeap->node[i];
	}
	delete[] minHeap->node;
	minHeap->size = 0;
}
