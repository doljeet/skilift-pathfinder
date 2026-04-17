#include "../include/pathfinder.h"
#include "../include/minheap.h"
#include <cstdio>
#include <climits>

void readInput(Input* input) {
	scanf("%d", &input->width);
	scanf("%d", &input->height);
	scanf("%d", &input->initialX);
	scanf("%d", &input->initialY);
	scanf("%d", &input->targetX);
	scanf("%d", &input->targetY);
	scanf("%d", &input->liftCount);

	input->lift = new Lift**[input->height];
	for (int y = 0; y < input->height; y++) {
		input->lift[y] = new Lift*[input->width];
		for (int x = 0; x < input->width; x++) {
			input->lift[y][x] = nullptr;
		}
	}

	for (int i = 0; i < input->liftCount; i++) {
		int init_x, init_y;
		scanf("%d", &init_x);
		scanf("%d", &init_y);
		Lift* temp = input->lift[init_y][init_x];
		input->lift[init_y][init_x] = new Lift;
		input->lift[init_y][init_x]->next = temp;
		input->lift[init_y][init_x]->initialX = init_x;
		input->lift[init_y][init_x]->initialY = init_y;
		scanf("%d", &input->lift[init_y][init_x]->targetX);
		scanf("%d", &input->lift[init_y][init_x]->targetY);
		scanf("%d", &input->lift[init_y][init_x]->time);
		scanf("%d", &input->lift[init_y][init_x]->interval);
	}

	input->topography = new int*[input->height];
	for (int y = 0; y < input->height; y++) {
		input->topography[y] = new int[input->width];
		for (int x = 0; x < input->width; x++) {
			scanf("%d", &input->topography[y][x]);
		}
	}
}

int** createTimeTable(Input* input) {
	int** timeTo = new int*[input->height];			
	for (int y = 0; y < input->height; y++) {
		timeTo[y] = new int[input->width];
		for (int x = 0; x < input->width; x++) {	
			timeTo[y][x] = INT_MAX;
		}
	}
	timeTo[input->initialY][input->initialX] = 0;
	return timeTo;
}

void freeInput(Input* input) {
	for (int y = 0; y < input->height; y++) {
		for (int x = 0; x < input->width; x++) {
			Lift* current = input->lift[y][x];
			while (current != nullptr) {
				Lift* next = current->next;
				delete current;
				current = next;
			}
		}
		delete[] input->lift[y];
	}
	delete[] input->lift;

	for (int y = 0; y < input->height; y++) {
		delete[] input->topography[y];
	}
	delete[] input->topography;
}

void liftTime(Input* input, MinHeap* minHeap, Node* currentNode, int** &timeTo) {
	Lift* current_lift = input->lift[currentNode->y][currentNode->x];
	while(current_lift != nullptr){
			int waiting_time;

			if (currentNode->time % current_lift->interval == 0) waiting_time = 0;							
			else waiting_time = current_lift->interval - currentNode->time % current_lift->interval;		

			int new_time = currentNode->time + waiting_time + current_lift->time;
			if (new_time < timeTo[current_lift->targetY][current_lift->targetX]) {
				timeTo[current_lift->targetY][current_lift->targetX] = new_time;
				Node* n = new Node{current_lift->targetY, current_lift->targetX, new_time};					
				push(n, minHeap);
			}
		current_lift = current_lift->next;
	}
}

int** shortestPath(Input* input, MinHeap* minHeap, int** &timeTo) {
	if (input == nullptr || minHeap == nullptr) return nullptr;

	Node* n0 = new Node{input->initialY, input->initialX, 0};
	push(n0, minHeap);

	int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};		

	while(minHeap->size > 0) {
		Node* currentNode = pop(minHeap);
		if (currentNode->time > timeTo[currentNode->y][currentNode->x]) {
			delete currentNode;
			continue;
		}

		for	(int d = 0; d < 4; d++) {
			int next_x = currentNode->x + dir[d][0];
			int next_y = currentNode->y + dir[d][1];

			if (next_x < 0 || next_x >= input->width || next_y < 0 || next_y >= input->height) continue;		
			int current_elev = input->topography[currentNode->y][currentNode->x];
			int next_elev = input->topography[next_y][next_x];

			int new_time;
			if (next_elev > current_elev) {																		
				new_time = currentNode->time + next_elev - current_elev + 1;
			}
			else {
				new_time = currentNode->time + 1;																
			}
			if (new_time < timeTo[next_y][next_x]) {															
				timeTo[next_y][next_x] = new_time;
				Node* n = new Node{next_y, next_x, new_time};
				push(n, minHeap);
			}
		}
		liftTime(input, minHeap, currentNode, timeTo);
		delete currentNode;
	}
	return timeTo;
}
