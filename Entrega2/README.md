Filtro de Sobel
---------------

Este algoritmo funciona mediante el cálculo del gradiente de la intensidad de la imagen en cada punto , 
la búsqueda de la dirección del cambio de claro a oscuro y de la magnitud del cambio. 
Esta magnitud corresponde a la nitidez del borde.

Para calcular el gradiente de cada punto de la imagen , la imagen se convoluciona con el Sobel Kernel. 
La convolución se realiza moviendo el núcleo a través de la imagen, un píxel a la vez. En cada píxel y
sus vecinos son ponderados por el valor correspondiente en el núcleo , y se
suman para producir un nuevo valor . Esta operación se muestra en el siguiente diagrama .

Gradiente: 
![alt text](https://github.com/Diana0205/HPC/blob/master/Entrega2/gradiente.png "Logo Title Text 1")

Aplicando el núcleo a la primera pixel nos da un valor de salida para ese píxel, 
lo tratamos como si el núcleo ha sido superpuesta sobre la imagen, con el píxel del centro del 
núcleo de la alineación que el primer pixel en la imagen. 
Luego múltiple cada entrada en el núcleo por el valor debajo de ella ,
y las suman para producir un valor de salida única sencillo de ese píxel.
Para los píxeles en el límite , lo ignoramos cualquier entrada en el núcleo que quedan fuera .
La detección de bordes mediante el operador Sobel aplica dos núcleos separados para 
calcular la x y los gradientes de Y en la imagen. La longitud de este gradiente se calcula 
y se normaliza para producir una sola intensidad aproximadamente igual a la nitidez del borde en esa posición.
A continuacion se muestra la matriz que se utiliza.

el gradiente en el Kernel x
~~~~~~~~~~~~~
|-1 | 0 | 1 |
|~~~+~~~+~~~|
|-2 | 0 | 2 |
|~~~+~~~+~~~|
|-1 | 0 | 1 |
~~~~~~~~~~~~~

y el gradiente del kenel
~~~~~~~~~~~~~
|-1 |-2 |-1 |
|~~~+~~~+~~~|
| 0 | 0 | 0 |
|~~~+~~~+~~~|
| 1 | 2 | 1 |
~~~~~~~~~~~~~


El Algoritmo
---------------
Ahora, el algoritmo puede ser descompuesto en sus pasos constitutivos
1 iterar sobre cada píxel de la imagen
2 Aplicar el kernel x gradiente
3 Aplicar el núcleo y gradiente
4 Encontrar la longitud de la pendiente usando el teorema de Pitágoras
5 Normalizar la longitud del gradiente de la gama 0-255
6 Ajuste los píxeles a los nuevos valores

Esto ilustra las etapas principales , a pesar de que se pierda algunos detalles como lo que hacemos cuando nos 
encontramos con el contorno de la imagen .

Tenemos que hacer un truco para que esto funcionará para nuestra detección de bordes .
Cuando estamos iterando sobre la imagen , vamos a cambiar el valor sin embargo cuando nos movemos
a la siguiente píxel , el valor acaba de cambiar todavía estará en el área de influencia de nuestro núcleo.
Por esta razón hay que asegurarse de que n se lee los píxeles de la imagen y escribimos los píxeles 
que son diferentes, y con esto se acaba de crear una imagen vacía, la cual vamos a rellenar con los nuevos valores .

Ahora vamos a leer los píxeles de la imagen original, pero escribir los valores de borde a img_edge
Antes de empezar a colocar los valores de los píxeles, tenemos que decidir cómo vamos a manejar los límites de la imagen. 
Para solucionar esto utilizamos la funcion clamp, encargada de asegurarse que los bordes esten dentro del rango de 0 y 255.

Ahora hablamos de la aplicación de los gradientes. 
Para el gradiente de x, necesitamos la columna de píxeles a la izquierda y derecha, para cada uno de los 6 píxeles 
que el índice que se suman las intensidades de color rojo, verde y azul, se multiplica por el kernel, y 
acumuladas en Gx. También vamos a hacer lo mismo para las y degradado. Como Gx y Gy ambos utilizan los 
mismos píxeles en ocasiones, lo mejor es aplicar los dos núcleos de forma simultánea.
Ahora que se aplican, Gx y Gy contienen valores no normalizado, que son iguales a la longitud 
relativa de la pendiente en sus respectivos ejes. Deseamos calcular la longitud de la pendiente, y normalizarlo
a un rango adecuado para la visualización.

Esto nos da una longitud no normalizada, para obtener la longitud normalizada, necesitamos saber el rango de longitud

Sabemos que el valor de la intensidad de cada píxel tiene un rango de 0 a 765, debido a que es 
la adición de 3 variables con el rango de 0 a 255. Asimismo, podemos ver la 
cantidad máxima que puede acumular es + / - 4 intensidades. Por lo tanto, el rango total de Gx y Gy es de entre 0 y 3060. 

Podemos renormalizar dividiendo entre los límites superiores y multiplicando por 255.
Justo al final del código que necesitamos para cambiar displayImage para mostrar nuestra nueva imagen 
en lugar del original. 
La secuencia de comandos debe producir una nueva imagen en escala de grises, destacando los bordes de la imagen original.
 
 
Se hizo una grafica en donde se toma el tiempo de ejecucion de los 4 tipos de algoritmo: secuencial,
memoria global, memoria constante y memoria compartida. Cada uno de estos algoritmos se compara con el
tamaño de las imagenes con las que se realizo el algoritmo.

![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "Logo Title Text 1")


Tambien se hizo una grafica en donde se compara el tamaño de las imagenes con la aceleración de cada algoritmo.

![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "Logo Title Text 1")





