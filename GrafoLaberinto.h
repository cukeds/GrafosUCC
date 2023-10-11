//
// Created by Juan on 10/2/2023.
//

#ifndef GRAFOS_GRAFOLABERINTO_H
#define GRAFOS_GRAFOLABERINTO_H
#include "Grafo.h"
#include "Pila.h"
#include "Cola.h"
#include <fstream>
#include <string>
using namespace std;
class cell{
public:
    cell(){};
    cell(int i, int i1, bool b, bool b1, bool b2, bool b3, bool b4) {
        x = i;
        y = i1;
        goal = b;
        start = b1;
        wall = b2;
        path = b3;
        explored = b4;
    }

    int x;
    int y;
    bool goal = false;
    bool start = false;
    bool explored = false;
    bool wall = false;
    bool path = false;
    bool solution = false;
    cell *parent;

    char getSymbol(){
        if(wall){
            return '#';
        }
        if(path){
            if(!explored){
                return ' ';
            }
            return '*';
        }
        if(goal){
            return 'S';
        }

        return 'I';

    }

    friend std::ostream& operator<<(std::ostream& os, const cell& obj) {
        if(obj.wall){
            os << '#';
        }
        if(obj.path && !obj.explored){
            os << ' ';
        }
        if(obj.goal){
            os << 'S';
        }
        if(obj.start){
            os<< 'I';
        }
        if(obj.explored && obj.path){
            os<< '*';
        }
        return os;
    }
};

class GrafoLaberinto : public Grafo<cell>{
public:
    int explored = 0;
    void leerLaberinto(const string& archivo){
        ifstream file(archivo);
        if (!file.is_open()) {
            cerr << "Error: No se pudo abrir el archivo " << archivo << endl;
            return;
        }
        string line;
        int x, y = 1;
        cell ToAdd;
        NodoGrafo<cell> *nodo, *ultimo;
        cell Celda;
        while (getline(file, line)) {
            x = 0;
            for(char character : line){
                x++;
                ToAdd.x = x;
                ToAdd.y = y;
                ToAdd.goal = false;
                ToAdd.start = false;
                ToAdd.wall = false;
                ToAdd.path = false;
                if(character == '#'){
                    ToAdd.wall = true;
                }
                if(character == 'I'){
                    ToAdd.start = true;
                }
                if(character == 'S'){
                    ToAdd.goal = true;
                }
                if(character == ' '){
                    ToAdd.path = true;
                }
                agregarNodo(ToAdd);
                if(ToAdd.wall){
                    continue;
                }
                ultimo = nodos[n-1];
                for(int i = 0; i < n-1; i++){
                    nodo = nodos->getDato(i);
                    Celda = nodo->getDato();
                    if(!Celda.wall) {
                        if (isAdjacent(Celda, ToAdd)) {
                            agregarArista(ultimo, nodo);
                        }
                    }
                }
            }
            y++;
        }

        file.close();

        imprimirGrafo();
    }

    bool isAdjacent(cell &c1, cell &c2){
        return c1.x == c2.x && abs(c1.y - c2.y) == 1 ||
                c1.y == c2.y && abs(c1.x - c2.x) == 1;
    }

    void resolverDfs(){
        auto *frontier = new Pila<NodoGrafo<cell>*>;
        NodoGrafo<cell> *nodo, *nodo_post;
        for(int i = 0; i < n; i++){
            if(nodos->getDato(i)->getDato().start){
                frontier->push(nodos->getDato(i));
                break;
            }
        }
        while(true){
            if(frontier->esVacia()){
                throw 404;
            }
            nodo = frontier->pop();
            if(nodo->getDato().goal){
                break;
            }
            explored++;
            nodo->setDato(cell(nodo->getDato().x, nodo->getDato().y, nodo->getDato().goal, nodo->getDato().start, nodo->getDato().wall, nodo->getDato().path, true));
            for(int i = 0; i < nodo->getGrado(); i++){
                if(nodo->getConexion(i)->getDato().explored){
                    continue;
                }
                nodo_post->setDato(cell(nodo->getDato().x, nodo->getDato().y, nodo->getDato().goal, nodo->getDato().start, nodo->getDato().wall, nodo->getDato().path, false));
                frontier->push(nodo->getConexion(i));
            }
        }
        cout << "Nodos explorados: "<<explored<<endl;
    }

    void resolverBfs(){
        auto *frontier = new Cola<NodoGrafo<cell>*>;
        NodoGrafo<cell> *nodo;
        for(int i = 0; i < n; i++){
            if(nodos->getDato(i)->getDato().start){
                frontier->encolar(nodos->getDato(i));
                break;
            }
        }
        while(true){
            if(frontier->esVacia()){
                throw 404;
            }
            nodo = frontier->desencolar();
            if(nodo->getDato().goal){
                break;
            }
            explored++;
            nodo->setDato(cell(nodo->getDato().x, nodo->getDato().y, nodo->getDato().goal, nodo->getDato().start, nodo->getDato().wall, nodo->getDato().path, true));
            for(int i = 0; i < nodo->getGrado(); i++){
                if(nodo->getConexion(i)->getDato().explored){
                    continue;
                }

                frontier->encolar(nodo->getConexion(i));
            }
        }

        cout << "Nodos explorados: "<<explored<<endl;
    }

    void escribir_recorrido(){
        string archivo = "../laberintos/recorrido.txt";

        // Create an ofstream object and open the file
        ofstream outFile(archivo);

        if (!outFile.is_open()) {
            cerr << "Error: No se pudo abrir el archivo " << archivo << std::endl;
        }
        int height = 0, width = 0;
        NodoGrafo<cell> *nodo;
        char maze[1000][1000];
        for(int i = 0; i < n; i++){
            nodo = nodos->getDato(i);
            maze[nodo->getDato().x - 1][nodo->getDato().y - 1] = nodo->getDato().getSymbol();
            if(nodo->getDato().wall){
                continue;
            }
            if(height < nodo->getDato().y){
                height = nodo->getDato().y;
            }
            if(width < nodo->getDato().x){
                width = nodo->getDato().x;
            }
        }
        for(int i = 0; i <= height; i++){
            for(int j = 0; j <= width; j++){
                outFile << maze[j][i];
            }
            outFile << '\n';
        }


        // Close the file
        outFile.close();
    }
};

#endif //GRAFOS_GRAFOLABERINTO_H
