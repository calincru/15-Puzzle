## Overview

[**15 puzzle**](http://en.wikipedia.org/wiki/15_puzzle) is a game which
consists of a frame of numbered square tiles in random order with one tile
missing. The goal is to rearrange the blocks so that they are in order, using
as few moves as possible.

## Implementation

It is implemented as a **best-first search**. The solution to the problem
illustrates a general artificial intelligence methodology known as the
[**A* search algorithm**](http://en.wikipedia.org/wiki/A*_search_algorithm).
A **seach node** of the game is represented by the combination of a board, the
number of moves made to reach the board and the previous search node. First,
the initial search node (initial board) is inserted into a *priority queue*.
Then, the search node with the minimum priority is deleted from the priority
queue and all its neighboring search nodes are inserted. This procedure is
repeated until the goal board is dequeued from the priority queue. The success
of this approach hinges on the choice of priority function for a search node.
We consider two priority functions:
* **Hamming priority function**. The number of blocks in the wrong position,
plus the number of moves made so far to get to the search node.
* **Manhattan Priority function**.  The sum of the Manhattan distances (sum of
the vertical and horizontal distance) from the blocks to their goal positions,
plus the number of moves made so far to get to the search node.

## Development

