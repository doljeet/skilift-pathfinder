# Ski Lift Pathfinder 

This repository contains a C++ solution to a pathfinding problem in a mountainous terrain, originally developed for an "Algorithms and Data Structures" university course. 

The core of the project is to find the fastest route between two points on a topographical grid, taking into account elevation changes and scheduled ski lifts. The algorithm utilizes **Dijkstra's Algorithm** with a custom implementation of a **Min-Heap** priority queue.

## The Problem

The terrain is divided into a grid where each cell has a specific elevation. Moving from a cell of height `B` to a cell of height `A` takes:
* `A - B + 1` minutes if `A > B` (moving uphill)
* `1` minute if `A <= B` (moving downhill or on flat terrain)
* Movement is restricted to 4 adjacent directions (up, down, left, right).

Additionally, there are **ski lifts** on the map:
* Lifts are one-way and have specific travel times.
* Lifts operate on intervals (e.g., a lift might depart every 5 minutes). Waiting time is taken into account when calculating the optimal path.

## Input Format

The program expects standard input (stdin) in the following format:
1. Map dimensions: `[width] [height]`
2. Start coordinates: `[x] [y]`
3. Target coordinates: `[x] [y]`
4. Number of ski lifts: `[N]`
5. Next `N` lines describe the lifts: `[start_x] [start_y] [target_x] [target_y] [travel_time] [departure_interval]`
6. A grid of heights representing the map topography.

### Example Input
```text
9 8 0 0 8 7 0
0 0 0 0 0 0 0 0 8 
0 9 9 9 9 9 9 9 0 
0 1 0 1 0 0 0 9 0 
