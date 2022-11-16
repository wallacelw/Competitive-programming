## Euler Path

### Definitions:

An **Eulerian Path** or **Eulerian Trail** (*Caminho Euleriano*) consists of a path that transverses all **Edges**. 

A special case is the closed path, which is an **Eulerian Circuit** or **Eulerian Cycle** (*Circuito/Ciclo Euleriano*). A graph is considered *eulerian* (**Eulerian Graph**) if it has an Eulerian Circuit.

Similarly, a **Hamiltonian Path** consists of a path that transverses all **Vertices**.

### Eulerian Path

To check if it is possible, there are only two conditions: 

**connectivity**, all vertices are connected, but there is no need for it to be strongly connected.

**same entry degree and leave degree for all vertices**, all vertices require *in-degree = out-degree*, which an exception to the initial vertice (1 more out-degree) and the final vertice (1 more in-degree).

## Hierholzer Algorithm

Find a Eulerian Path with a linear complexity of *O(Edges)*.



