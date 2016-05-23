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
