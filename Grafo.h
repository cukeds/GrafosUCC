//
// Created by alumno on 28/9/2023.
//

#ifndef GRAFOS_GRAFO_H
#define GRAFOS_GRAFO_H
#include "Lista.h"
#include "NodoGrafo.h"
template <class T>
class Grafo {
private:
    int n=0;
public:
    Lista<NodoGrafo<T>*> *nodos;

    Grafo() {
        nodos = new Lista<NodoGrafo<T>*>;
    }
    void agregarNodo(T dato) {
        NodoGrafo<T> *nuevoNodo = new NodoGrafo(dato);
        nodos->insertarUltimo(nuevoNodo);
        n++;
    }

    void agregarArista(NodoGrafo<T> *nodoA, NodoGrafo<T> *nodoB) {
        nodoA->addConexion(nodoB);
        nodoB->addConexion(nodoA);
    }

    void imprimirGrafo() {
        for (int i = 0; i < n; i++) {
            NodoGrafo<T>* nodo = nodos->getDato(i);
            std::cout << "NodoGrafo con dato " << nodo->getDato() << " esta conectado a: ";

            if (nodo->getGrado() > 0) {
                for (int i = 0; i < nodo->getGrado() - 1; i++) {
                    std::cout << nodo->getConexion(i)->getDato() << ", ";
                }
                std::cout << nodo->getConexion(nodo->getGrado() - 1)->getDato();
            } else {
                std::cout << "ningún otro nodo";
            }

            std::cout << std::endl;
        }
    }

};

#endif //GRAFOS_GRAFO_H
