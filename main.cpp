#include <iostream>
#include "Grafo.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Grafo<int> grafo;
    grafo.agregarNodo(1);
    grafo.agregarNodo(2);
    grafo.agregarNodo(3);
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(1));
    grafo.agregarArista(grafo.nodos->getDato(1), grafo.nodos->getDato(2));

    grafo.imprimirGrafo();


    return 0;
}
