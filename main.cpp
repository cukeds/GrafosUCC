#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grafo.h"
#include "GrafoLaberinto.h"
#include <cmath>
using namespace std;

Lista<sf::Vector2f> nodePositions;
void setupNodePositions(int n) {
    int numNodes = n;
    float centerX = 400.0f; // X coordinate of the center of the circle
    float centerY = 300.0f; // Y coordinate of the center of the circle
    float radius = 200.0f;  // Radius of the circular pattern

    for (int i = 0; i < numNodes; i++) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numNodes);
        float posX = centerX + radius * std::cos(angle);
        float posY = centerY + radius * std::sin(angle);
        nodePositions.insertarUltimo(sf::Vector2f(posX, posY));
    }
}


// Function to render your graph using SFML
void renderGraph(sf::RenderWindow& window, sf::Font font, Grafo<string> myGraph) {
    // Render your graph here using SFML drawing functions
    for (size_t i = 0; i < myGraph.getN(); i++) {
        NodoGrafo<string>* nodo = myGraph.nodos->getDato(i);

        // Create a circle for the node
        sf::CircleShape nodeShape(20.0f);
        nodeShape.setFillColor(sf::Color::Blue);
        nodeShape.setPosition(nodePositions.getDato(i).x - 20.0f, nodePositions.getDato(i).y - 20.0f); // Adjust for circle radius
        // Draw the node
        window.draw(nodeShape);

        sf::Text label;
        label.setFont(font); // Use the loaded font
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::Black);
        label.setString(nodo->getDato()); // Use node index as label (add 1 to start from 1)

        // Position the label at the center of the node
        sf::FloatRect labelBounds = label.getLocalBounds();
        label.setOrigin(labelBounds.width / 2.0f, labelBounds.height / 2.0f); // Center the origin
        label.setPosition(nodePositions.getDato(i));
        window.draw(label);
        // Draw connections (edges)
        for (int j = 0; j < nodo->getGrado(); j++) {
            NodoGrafo<string>* connectedNode = nodo->getConexion(j);

            // Calculate positions of connected nodes based on nodePositions
            sf::Vector2f startPos = nodePositions.getDato(i);
            sf::Vector2f endPos = nodePositions.getDato(connectedNode->getId() - 1); // Assuming IDs start from 1
            sf::Color lineColor = sf::Color::Red;
            // Create a line for the connection
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(startPos.x, startPos.y), lineColor),
                    sf::Vertex(sf::Vector2f(endPos.x, endPos.y), lineColor)
            };

            // Draw the connection (edge)
            window.draw(line, 2, sf::Lines);
        }
    }
}

int main() {
    Grafo<string> grafo;
    grafo.agregarNodo("Agustin Gallardo");
    grafo.agregarNodo("Francisco Gomez");
    grafo.agregarNodo("Tomas Ossana");
    grafo.agregarNodo("Guido Olguin");
    grafo.agregarNodo("Santiago Rearte");
    grafo.agregarNodo("Ignacio Altamirano");
    grafo.agregarNodo("Nicolas Gomez");
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(1));
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(2));
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(3));
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(4));
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(5));
    grafo.agregarArista(grafo.nodos->getDato(0), grafo.nodos->getDato(6));
    grafo.agregarArista(grafo.nodos->getDato(1), grafo.nodos->getDato(2));
    grafo.agregarArista(grafo.nodos->getDato(4), grafo.nodos->getDato(6));
    grafo.agregarArista(grafo.nodos->getDato(4), grafo.nodos->getDato(5));
    grafo.agregarArista(grafo.nodos->getDato(5), grafo.nodos->getDato(6));

    grafo.imprimirGrafo();
    cout<<"--------------------\n";
    cout<<"Matriz de adjacencia: \n";
    grafo.matrizAdjacencia();
//
//    GrafoLaberinto gl;
//    gl.leerLaberinto("../laberintos/gpt_mazes2.txt");
//    gl.resolverDfs();
//    gl.escribir_recorrido();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

    // Create a font for rendering text
    sf::Font font;
    if (!font.loadFromFile("../SIXTY.ttf")) {
        // Handle font loading error
        return EXIT_FAILURE;
    }

    // Create a graphical representation of your graph here
    // You need to draw nodes and connections based on your graph data
    setupNodePositions(grafo.getN());
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Inside the main loop
        renderGraph(window, font, grafo);

        // Render your graph here using SFML drawing functions

        window.display();


    }

    return EXIT_SUCCESS;

    return 0;
}
