## Test files structure

Each test in `input/` directory has its associated referential test which
follows the pattern `ref/<text_name>_ref.txt` and its associated current
output file `output/<text_name_out>.txt`.

For the **Board** tests, the output should follow this template:
```bash
3       // Dimension of the Board
1 1     // Position of the empty slot
5       // Priority given by the Hamming function
10      // Priority given by the Manhattan function
0       // 1/0 if this is/is not the goal Board
8 0 3   // The upper neighbour
4 1 2
7 6 5
8 1 3   // The lower neighbour
4 6 2
7 0 5
8 1 3   // The left neighbour
0 4 2
7 6 5
8 1 3   // The right neighbour
4 2 0
7 6 5
```

**Note:** To avoid any diff problem, leave a **newline** at the end of file.
