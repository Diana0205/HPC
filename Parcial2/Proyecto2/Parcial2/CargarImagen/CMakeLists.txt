cmake_minimum_required(VERSION 2.8)
project( CargarImagen)
find_package( OpenCV REQUIRED )
add_executable( CargarImagen CargarImagen.cpp )
target_link_libraries( CargarImagen ${OpenCV_LIBS} )
