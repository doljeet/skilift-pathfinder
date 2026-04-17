#pragma once
#include "types.h"

void swap(Node* &a, Node* &b);
void push(Node* newNode, MinHeap* minHeap);
Node* pop(MinHeap* minHeap);
void freeMinHeap(MinHeap* minHeap);
