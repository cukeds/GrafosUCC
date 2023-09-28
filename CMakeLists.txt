cmake_minimum_required(VERSION 3.24)
project(grafos)

set(CMAKE_CXX_STANDARD 23)

add_executable(grafos main.cpp Grafo.h NodoGrafo.h Lista.h NodoLista.h)
