#include <cstdio>
#include "../include/types.h"
#include "../include/pathfinder.h"
#include "../include/minheap.h"

int main() {
    Input* input = new Input;
    readInput(input);

    MinHeap* minHeap = new MinHeap;
    minHeap->node = new Node*[MAX_NODES];

    int** timeTo = createTimeTable(input);

    shortestPath(input, minHeap, timeTo);

    printf("%d\n", timeTo[input->targetY][input->targetX]);

    freeInput(input);
    freeMinHeap(minHeap);
    for (int y = 0; y < input->height; y++) {
        delete[] timeTo[y];
    }
    delete input;
    delete minHeap;
    delete[] timeTo;
    
    return 0;
}
