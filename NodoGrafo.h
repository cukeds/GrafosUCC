//
// Created by alumno on 28/9/2023.
//

#ifndef GRAFOS_NODOGRAFO_H
#define GRAFOS_NODOGRAFO_H
#include "Lista.h"
#include <iostream>

using namespace std;
template<class T>
class NodoGrafo{
private:
    Lista<NodoGrafo<T>*> *conexiones;
    int grado;
    T dato;
    int id;
public:
    NodoGrafo(){
        conexiones = new Lista<NodoGrafo<T>*>;
        grado = 0;
        dato = T();
        id = 0;
    }
    explicit NodoGrafo(int id, T dato){
        conexiones = new Lista<NodoGrafo<T>*>;
        grado = 0;
        this->dato = dato;
        this->id = id;
    }
    ~NodoGrafo() {
        conexiones->vaciar();
        delete conexiones;
    }

    void setDato(T dato){
        this->dato = dato;
    }

    T getDato(){
        return dato;
    }

    void addConexion(NodoGrafo<T> *nodo){
        conexiones->insertarUltimo(nodo);
        grado++;

    }

    int getId(){
        return id;
    }

    NodoGrafo<T>* getConexion(int n){
        return conexiones->getDato(n);
    }

    bool isConnected(int _id){
        for(int i = 0; i < grado; i++){
            if(conexiones->getDato(i)->getId() == _id){
                return true;
            }
        }
        return false;
    }

    void print(){
        std::cout<<dato<<" {";
        for(int i = 0; i < grado; i++){
            std::cout<< "{"<<dato<<","<<(conexiones[i])->getDato()<<"}";
        }
        std::cout<<"}"<<endl;

    }

    int getGrado(){
        return grado;
    }
};


#endif //GRAFOS_NODOGRAFO_H
