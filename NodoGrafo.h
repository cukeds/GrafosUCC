//
// Created by alumno on 28/9/2023.
//

#ifndef GRAFOS_NODOGRAFO_H
#define GRAFOS_NODOGRAFO_H
#include <iostream>

using namespace std;
template<class T>
class NodoGrafo{
private:
    int max_grado = 100;
    NodoGrafo<T> **conexiones;
    int grado;
    T dato;
public:
    NodoGrafo(){
        max_grado = 100;
        conexiones = new NodoGrafo<T>*[max_grado];
        grado = 0;
        dato = T();
    }
    explicit NodoGrafo(T dato){
        max_grado = 100;
        conexiones = new NodoGrafo<T>*[max_grado];
        grado = 0;
        this->dato = dato;
    }
    ~NodoGrafo() {
        delete[] conexiones;
    }

    void setDato(T dato){
        this->dato = dato;
    }

    T getDato(){
        return dato;
    }

    void addConexion(NodoGrafo<T> *nodo){
        if(grado < max_grado){
            conexiones[grado] = nodo;
            grado++;
        }else{
            throw 400;
        }
    }

    NodoGrafo<T>* getConexion(int n){
        return conexiones[n];
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
