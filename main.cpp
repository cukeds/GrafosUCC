#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grafo.h"
// #include "GrafoLaberinto.h"
#include <cmath>
#include "Lista.h"
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
    auto nodos = myGraph.getNodos();
    for (size_t i = 0; i < myGraph.getN(); i++) {
        std::shared_ptr<NodoGrafo<string>> nodo = nodos[i];

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
            std::shared_ptr<NodoGrafo<string>> connectedNode = nodo->getConexion(j);

            // Calculate positions of connected nodes based on nodePositions
            sf::Vector2f startPos = nodePositions.getDato(i);
            sf::Vector2f endPos = nodePositions.getDato(connectedNode->getId() - 1); // Assuming IDs start from 1
            sf::Color lineColor = sf::Color(0, 0, 0);
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
    grafo.agregarNodo("Luana Rolon");
    grafo.agregarNodo("Selena Saad");
    grafo.agregarNodo("Agustin Gallardo");
    grafo.agregarArista(0, 1);
    grafo.agregarArista(1,2);
    grafo.agregarArista(0,2);
    grafo.agregarNodo("Tobias Nicolas");
    grafo.agregarNodo("Nicolas Rojas");
    grafo.agregarNodo("Mateo Velasquez");
    grafo.agregarNodo("Agustina Perez");
    grafo.agregarArista(3,4);
    grafo.agregarArista(3,5);
    grafo.agregarArista(3,6);
    grafo.agregarArista(4,5);
    grafo.agregarArista(4,6);
    grafo.agregarArista(5,6);

    grafo.agregarNodo("Delfina Salinas");
    grafo.agregarNodo("Virginia Rodriguez");
    grafo.agregarNodo("Constanza Strumia");
    grafo.agregarNodo("Belen Triachi");
    grafo.agregarNodo("Ignacio Altamirano");
    grafo.agregarNodo("Margarita De Marcos");
    grafo.agregarNodo("Bautista Juncos");
    grafo.agregarNodo("Paulina Ortiz");
    grafo.agregarNodo("Valentina Rivarola");
    grafo.agregarNodo("Sofia Oliveto");
    grafo.agregarNodo("Marcos Bugliotti");
    grafo.agregarNodo("Arnon Nahamias");
    grafo.agregarNodo("Dante Ojeda");
    grafo.agregarNodo("Joaquin Lista");

    grafo.agregarArista(7, 8);
    grafo.agregarArista(7, 9);
    grafo.agregarArista(7, 10);
    grafo.agregarArista(7, 11);
    grafo.agregarArista(7, 12);
    grafo.agregarArista(7, 13);
    grafo.agregarArista(7, 14);
    grafo.agregarArista(7, 15);
    grafo.agregarArista(7, 16);
    grafo.agregarArista(7, 17);
    grafo.agregarArista(7, 18);
    grafo.agregarArista(7, 19);
    grafo.agregarArista(8, 9);
    grafo.agregarArista(8, 10);
    grafo.agregarArista(8, 11);
    grafo.agregarArista(8, 12);
    grafo.agregarArista(8, 13);
    grafo.agregarArista(8, 14);
    grafo.agregarArista(8, 15);
    grafo.agregarArista(8, 16);
    grafo.agregarArista(8, 17);
    grafo.agregarArista(8, 18);
    grafo.agregarArista(8, 19);
    grafo.agregarArista(8, 20);
    grafo.agregarArista(9, 10);
    grafo.agregarArista(9, 11);
    grafo.agregarArista(9, 12);
    grafo.agregarArista(9, 13);
    grafo.agregarArista(9, 14);
    grafo.agregarArista(9, 15);
    grafo.agregarArista(9, 16);
    grafo.agregarArista(9, 17);
    grafo.agregarArista(9, 18);
    grafo.agregarArista(9, 19);
    grafo.agregarArista(9, 20);
    grafo.agregarArista(10, 11);
    grafo.agregarArista(10, 12);
    grafo.agregarArista(10, 13);
    grafo.agregarArista(10, 14);
    grafo.agregarArista(10, 15);
    grafo.agregarArista(10, 16);
    grafo.agregarArista(10, 17);
    grafo.agregarArista(10, 18);
    grafo.agregarArista(10, 19);
    grafo.agregarArista(10, 20);
    grafo.agregarArista(11, 12);
    grafo.agregarArista(11, 13);
    grafo.agregarArista(11, 14);
    grafo.agregarArista(11, 15);
    grafo.agregarArista(11, 16);
    grafo.agregarArista(11, 17);
    grafo.agregarArista(11, 18);
    grafo.agregarArista(11, 19);
    grafo.agregarArista(11, 20);
    grafo.agregarArista(12, 13);
    grafo.agregarArista(12, 14);
    grafo.agregarArista(12, 15);
    grafo.agregarArista(12, 16);
    grafo.agregarArista(12, 17);
    grafo.agregarArista(12, 18);
    grafo.agregarArista(12, 19);
    grafo.agregarArista(12, 20);
    grafo.agregarArista(13, 15);
    grafo.agregarArista(13, 16);
    grafo.agregarArista(13, 17);
    grafo.agregarArista(13, 18);
    grafo.agregarArista(13, 19);
    grafo.agregarArista(13, 20);
    grafo.agregarArista(14, 15);
    grafo.agregarArista(14, 16);
    grafo.agregarArista(14, 17);
    grafo.agregarArista(14, 18);
    grafo.agregarArista(14, 19);
    grafo.agregarArista(14, 20);
    grafo.agregarArista(15, 16);
    grafo.agregarArista(15, 17);
    grafo.agregarArista(15, 18);
    grafo.agregarArista(15, 19);
    grafo.agregarArista(15, 20);
    grafo.agregarArista(16, 17);
    grafo.agregarArista(16, 18);
    grafo.agregarArista(16, 19);
    grafo.agregarArista(16, 20);
    grafo.agregarArista(17, 18);
    grafo.agregarArista(17, 19);
    grafo.agregarArista(17, 20);
    grafo.agregarArista(18, 19);
    grafo.agregarArista(18, 20);
    grafo.agregarArista(19, 20);


    grafo.agregarNodo("Martina Becerra");
    grafo.agregarNodo("Pablo Venica");
    grafo.agregarNodo("Victoria Sponton");
    grafo.agregarNodo("Manuel Ferreras");
    grafo.agregarNodo("Franco Casavecchia");
    grafo.agregarNodo("Agustin Ditomasso");
    grafo.agregarNodo("Marcos Don");
    grafo.agregarNodo("Matias Carbel");

    grafo.agregarArista(23, 2);
    grafo.agregarArista(24, 25);
    grafo.agregarArista(24, 26);
    grafo.agregarArista(24, 27);
    grafo.agregarArista(25, 26);
    grafo.agregarArista(25, 27);
    grafo.agregarArista(26, 27);


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

}
