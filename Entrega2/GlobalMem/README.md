En el algoritmo de Global Memory se transfieren los datos del host

Este algoritmo consiste en realizar el filtro de sobel
utilizando memoria global, pero ya se realiza el proceso con la GPU.


Aqui vamos a desarrollar la aplicacion del filtro de sobel accediendo a la memoria global 
con el fin de que se realice un mejor desempeño.

Se utiliza la memoria global para enviar datos al dispositivo y cada hilo tiene acceso a este núcleo para calcular la convolución.

Se define entonces dos funciones una SobelX y otra sobelY, las dos cumplen la funcion de realizar el recorrido (ancho y alto)
en el eje correspondiente sobre la imagen y se realiza el proceso de convolucion.

Utilizamos el filtro sobel con el que finalmente se obtiene la conversion a escala de grises y se presentan
3 tipos de imagenes: una normal, una con escala de grises y otra con el filtro sobel.

Se realiza el proceso tanto en CPU como en GPU.

La diferencia entre los filtros es que depende si se encuentra la transpuesta del gradiente,
pues esto ya corresponderia al recorrido sobre la imagen en el eje y.

A continuación se muestra la grafica donde se muestra el tiempo de ejecución con el algoritmo de memoria global y su comparación contra el tamaño de las imagenes, que en total fueron 9.

Tiempo de ejecucion vs Tamaño imagen Algoritmo Global Memory: 

![alt text](https://github.com/Diana0205/HPC/blob/master/Entrega2/GlobalMem/TEGM.png "Logo Title Text 1")


Tambien se hizo se saco la acelerecion del algoritmo 
en comparacion al tamaño de las imagenes. 
Tiempo de ejecucion vs Tamaño imagen Algoritmo global memory:

![alt text](https://github.com/Diana0205/HPC/blob/master/Entrega2/GlobalMem/Aceleracio%20%20globlal%20memory.png "Logo Title Text 1")

