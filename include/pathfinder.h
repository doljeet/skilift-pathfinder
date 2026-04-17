#pragma once
#include "types.h"

void readInput(Input* input);
int** createTimeTable(Input* input);
void freeInput(Input* input);
void liftTime(Input* input, MinHeap* minHeap, Node* currentNode, int** &timeTo);
int** shortestPath(Input* input, MinHeap* minHeap, int** &timeTo);
