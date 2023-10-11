#ifndef GRAFOS_H
#define GRAFOS_H

#include <iostream>
#include <vector>
#include <memory>
#include "NodoGrafo.h"

template <class T>
class Grafo {
private:
    int n = 0;
    std::vector<std::shared_ptr<NodoGrafo<T>>> nodos;
    std::vector<std::vector<bool>> adjacencyMatrix;

public:
    Grafo(){
        adjacencyMatrix = std::vector<std::vector<bool>>(100, std::vector<bool>(100, false));
    }

    Grafo(int expected_n){
        adjacencyMatrix = std::vector<std::vector<bool>>(expected_n, std::vector<bool>(expected_n, false));
    }

    const std::vector<std::shared_ptr<NodoGrafo<T>>> &getNodos() const {
        return nodos;
    }

    int getN() {
        return n;
    }

    void agregarNodo(T dato) {
        auto nuevoNodo = std::make_shared<NodoGrafo<T>>(n, dato);

        // Initialize the new row for the adjacency matrix with 'false' values
        std::vector<bool> newRow(n, false);
        adjacencyMatrix.push_back(newRow);

        // Update existing rows to include a 'false' value for the new node
        for (auto& row : adjacencyMatrix) {
            row.push_back(false);
        }

        nodos.push_back(nuevoNodo);
        n++;
    }

    void agregarArista(int id1, int id2) {
        if (id1 >= 0 && id1 < n && id2 >= 0 && id2 < n) {
            nodos[id1]->addConexion(nodos[id2]);
            nodos[id2]->addConexion(nodos[id1]);

            adjacencyMatrix[id1][id2] = true;
            adjacencyMatrix[id2][id1] = true;
        } else {
            std::cerr<<"Node not in graph"<<std::endl;
        }
    }


    void imprimirGrafo() {
        for (const auto& nodo : nodos) {
            std::cout << "Nodo " << nodo->getId() << " Grado: " << nodo->getGrado() << " - " << nodo->getDato() << " esta conectado a: ";

            if (nodo->getGrado() > 0) {
                for (int i = 0; i < n; i++) {
                    if(adjacencyMatrix[nodo->getId()][i]){
                        std::cout << nodos[i]->getDato() << ", ";
                    }
                }
            } else {
                std::cout << "ningún otro nodo";
            }

            std::cout << '\n';
        }
    }

    void matrizAdjacencia() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjacencyMatrix[i][j]) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << '\n';
        }
    }

    std::shared_ptr<NodoGrafo<T>> getNodo(int pos){
        return nodos[pos];
    }
};

#endif