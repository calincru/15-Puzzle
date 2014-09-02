## TDD Design


I designed from scratch a *way* to efficiently write tests in c++, being
mostly inspired by the **Qt**'s specific TDD.

There is an *abstract* class which is meant to be inherited by every concrete
test class. This class does all the file/directory parsing and requests the
concrete class to only implement two methods: the public **name()** which,
obviously, returns the name of the test (debugging purposes) and **outFiles()**,
a private one, which receives as parameters the full path where it has to write
the output files, the list of input files and returns the list of output files.

Now, there are some assumptions made regarding the tests **directory structure**.
Briefly, the executable should be in the same directory with a **testfiles**
directory (as in this repo) which contains one directory per each test (in this
case **boardtest** and **solvertest**, which contains three directories:
*input*, *output*, *ref*. Their meaning is hopefully self-explanatory.

Each test in `input/` directory has its associated referential test which
follows the pattern `ref/<test_name>_ref.txt` and its associated current
output file `output/<test_name_out>.txt`.

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
