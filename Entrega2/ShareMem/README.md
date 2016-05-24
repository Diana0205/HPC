En el algoritmo de memoria compartida se busca minimizar el acceso a la memoria global y
asi tener un mejor rendimiento del algoritmo.


Con el algoritmo de memoria compartida se busca crear submatrices 
y realiza el procedimiento cada n*n para obtimizarlo, pues sebusca que aqui queden guardados los valores
no necesarios de la convolución, y se obtinen haciendo el recorrido de izquierda a derecha y en el centro, luego de esto esos valores
quedan guardados en la memoria compartida en donde se  sincronizan los hilos 
y se procede a realizar la convolución accediendo a la matriz de memoria compartida.

Se hace este prcoceso tanto en el filtro sobel X como en el filtro sobelY.

Utilizamos el filtro sobel con el que finalmente se obtiene la conversion a escala de grises y se presentan 3 tipos de imagenes: una normal, una con escala de grises y otra con el filtro sobel.

Se realiza el proceso tanto en CPU como en GPU.

La diferencia entre los filtros es que depende si se encuentra la transpuesta del gradiente,
pues esto ya corresponderia al recorrido sobre la imagen en el eje y.


A continuación se muestra la grafica donde se muestra el tiempo de ejecución con el algoritmo de memoria global y su comparación contra el tamaño de las imagenes, que en total fueron 9.

Tiempo de ejecucion vs Tamaño imagen Algoritmo Global Memory:

![alt text](https://github.com/Diana0205/HPC/blob/master/Entrega2/ShareMem/TESM.png "Logo Title Text 1")


Tambien se hizo se saco la acelerecion del algoritmo en comparacion al tamaño de las imagenes. Tiempo de ejecucion vs Tamaño imagen Algoritmo global memory:

![alt text](https://github.com/Diana0205/HPC/blob/master/Entrega2/ShareMem/Aceleracion%20Shared%20Memory.png "Logo Title Text 1")
