# Algorithm to Find Minimum Spanning Tree in a Dynamic Graph

This is the codebase for the Data Structures and Algorithms Course Project. We were required to implement an algorithm to find Minimum Spanning Tree in a Dynamic Graph. We did it by recursively implementing Kruskal's Algorithm of finding Minimum Spanning Tree.\
The codebase will look something like this:
```bash
.
├── graph.c
├── graph.h
├── Makefile
├── mst.c
```

- `graph.h`: It is the file containing all the declarations related to the graph data structure we have used (which is edge-list data structure).
- `graph.c`: It is the file containing all the definitions for the functions given in `graph.h`.
- `mst.c`: This is the main file containing the implementation of the kruskal's algorithm of finding Minimum Spanning Tree using the Union-Find method.
- `Makefile`: This is the makefile to be used to compile the codebase.

### Usage Instructions

The given codebase can be compiled using the following command (as makefile is already defined to compile the program to `./dynamicMST`):\
For Linux/Unix based systems:
```bash
make
./dynamicMST
```

For Windows:
```bash
gcc -w -o dynamicMST mst.c graph.c
./dynamicMST
```

After it starts executing it prompts the user as follows:

```bash
Select the operation you wish to conduct:
1. Add Edge
2. Remove Edge
3. Remove Vertex
4. Exit
```

### Important Note

The program might give unexpected output on unexpected inputs as it is not optimised for edge-cases. So, the following needs to be ensured while using the program:

- Vertex Names should always start with $0$ and should never exeed the total number of vertices.
- While deleting edges or vertices, user is requested to ensure that the edge/vertex being deleted exists in the graph.

---
