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

La diferencia entre los filtros es que en el SobelY se realiza el proceso con la transpuesta del gradiente.
