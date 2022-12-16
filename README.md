# Assignment 4 - The Perambulations of Denver Long
This program prints out the shortest Hamiltonian path (visits each location only once).
The input must be a graph written in the order:
```
Number of locations
Names of the locations
Edges and their weights as tuples
```

## Building
Build the program with:
```
$ make
```
You can check the formatting using:
```
$ make format
```
Remember to clean up afterwards so there are no object files or executables left over:
```
$ make clean
```

## Running
Run the program using:
```
$ ./tsp
```
followed by a command where:
```
-u use undirected graph
-v print all the Hamiltonian paths 
-i input file
-o output file
-h help
```
For example, you can run the program using ./tsp -i graph (which is the same as ./tsp < graph), 
where graph is a file with the proper format (as specified before).

## Possible Errors
There were no bugs found during scan-build make, and valgrind indicated that all memory was freed.
