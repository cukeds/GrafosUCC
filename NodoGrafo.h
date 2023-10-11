#ifndef GRAFOS_NODOGRAFO_H
#define GRAFOS_NODOGRAFO_H

#include <iostream>
#include <vector>
#include <memory>

template<class T>
class NodoGrafo {
private:
    std::vector<std::shared_ptr<NodoGrafo<T>>> conexiones;
    int grado;
    T dato;
    int id;

public:
    NodoGrafo() : grado(0), dato(T()), id(0) {}

    explicit NodoGrafo(int id, T dato) : grado(0), dato(dato), id(id) {}

    void setDato(T dato) {
        this->dato = dato;
    }

    T getDato() const {
        return dato;
    }

    void addConexion(std::shared_ptr<NodoGrafo<T>> nodo) {
        conexiones.push_back(nodo);
        grado++;
    }

    int getId() const {
        return id;
    }

    std::shared_ptr<NodoGrafo<T>> getConexion(int n) const {
        if (n >= 0 && n < grado) {
            return conexiones[n];
        }
        return nullptr;
    }

    bool isConnected(int _id) const {
        for (const auto& conexion : conexiones) {
            if (conexion->getId() == _id) {
                return true;
            }
        }
        return false;
    }

    void print() const {
        std::cout << dato << " {";
        for (int i = 0; i < grado; i++) {
            std::cout << "{" << dato << "," << conexiones[i]->getDato() << "}";
        }
        std::cout << "}" << std::endl;
    }

    int getGrado() const {
        return grado;
    }
};

#endif //GRAFOS_NODOGRAFO_H
