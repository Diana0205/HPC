El lenguaje CUDA pone a disposición otro tipo de memoria conocida como memoria constante .
Como su nombre lo indica, utilizamos la memoria constante para los datos que no 
cambiarán en el transcurso de la ejecución de un kernel.

Aqui vamos a desarrollar la aplicacion del filtro de sobel con memoria compartida con el fin
de encontrar un mejor desempeño dado que recurrimos a la paralelización de hilos y bloques.

Se define entonces dos funciones una SobelX y otra sobelY, las dos cumplen la funcion de 
realizar el recorrido (ancho y alto) en el eje correspondiente sobre la imagen y se realiza 
el proceso de convolucion.

Utilizamos el filtro sobel con el que finalmente se obtiene la conversion a escala de grises 
y se presentan 3 tipos de imagenes: una normal, una con escala de grises y otra con el filtro sobel.

La diferencia entre los filtros es que en el SobelY se realiza el proceso con la transpuesta del gradiente
