#pragma once

#define MAX_NODES 3000000

struct Lift {
    int initialX, initialY, targetX, targetY;
    int time;
    int interval;
    Lift* next;
};

struct Input {
    int width, height, initialX, initialY, targetX, targetY, liftCount;
    Lift*** lift;
    int** topography;
};

struct Node {
    int y, x;
    int time;
};

struct MinHeap {
    Node** node;
    int size = 0;
};
