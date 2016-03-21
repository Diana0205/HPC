Este algortimo ejecuta varios hilos en paralelo, en este algoritmo se accede a la GPU en donde
Se determino un tamaño de vector con los multiplos de 32 hasta el 320
con una cantidad de bloques igual a 10, en donde se determino que blocSize=1024.


En este algoritmo se habla de:
•Se puede acceder por los threads de un mismo bloque.
• Acceso más veloz.
• Dimensión pequeña.

A continuación se muestran los datos y la grafica obtenida en donde se ve como aumneta el tiempo a medida que tambien incrementa el tamaño de los vectores.

[Datos obtenidos multiplicación paralela](https://docs.google.com/spreadsheets/d/1VwPIax58od-4EpQKq0AsxRAumjRPU5qznPx5cSa6qJ0/edit#gid=1712626559)
