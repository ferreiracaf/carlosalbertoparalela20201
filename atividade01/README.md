# Activity 01
This activity is a serial version of matrix multiplication (Representated by matrix C = matrix A * matrix B). For ease in analyzing the results of parallelization, the matrices A and B are initialized with all values equals '1.0' and the matrix C with all values '0.0'.

There are also three executable files:
* **maxMultSerial**: version without any OpenMP directives.
* **maxMultParallelNoCollapse**: version with one directive _'parallel for'_ on the first loop of the funcion _'mtxMul'_.
* **maxMultParallel2Collapse**: with one directive _'parallel for'_ on the first loop of the funcion _'mtxMul'_, but with the clause _'collapse(2)'_.

### Results
The results.txt file describes the CPU on which the tests were performed, as well as the amount of RAM and then the respective time values for execution respectively for each executable file.
The values were obtained by the 'time' command and checking the real field for a 2000x2000 matrix.