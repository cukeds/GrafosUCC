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
template<class T>
void renderGraph(sf::RenderWindow& window, sf::Font font, Grafo<T> myGraph) {
    // Render your graph here using SFML drawing functions
    auto nodos = myGraph.getNodos();
    for (size_t i = 0; i < myGraph.getN(); i++) {
        std::shared_ptr<NodoGrafo<T>> nodo = nodos[i];

        // Create a circle for the node
        sf::CircleShape nodeShape(20.0f);
        Color color = nodo->getColor();
        nodeShape.setFillColor(sf::Color(color.r, color.g, color.b));
        nodeShape.setPosition(nodePositions.getDato(i).x - 20.0f, nodePositions.getDato(i).y - 20.0f); // Adjust for circle radius
        // Draw the node
        window.draw(nodeShape);

        sf::Text label;
        label.setFont(font); // Use the loaded font
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::Black);
        label.setString(to_string(nodo->getId())); // Use node index as label (add 1 to start from 1)

        if(nodo->getLabel() != to_string(nodo->getId())){
            sf::Text label;
            label.setFont(font); // Use the loaded font
            label.setCharacterSize(20);
            label.setFillColor(sf::Color::Black);
            label.setString(nodo->getLabel()); // Use node index as label (add 1 to start from 1)
            sf::FloatRect labelBounds = label.getLocalBounds();
            label.setOrigin(labelBounds.width / 2.0f, labelBounds.height * 2.0f); // Center the origin
            label.setPosition(nodePositions.getDato(i));
            window.draw(label);

        }

        // Position the label at the center of the node
        sf::FloatRect labelBounds = label.getLocalBounds();
        label.setOrigin(labelBounds.width / 2.0f, labelBounds.height / 2.0f); // Center the origin
        label.setPosition(nodePositions.getDato(i));
        window.draw(label);
        // Draw connections (edges)
        for (int j = 0; j < nodo->getGrado(); j++) {
            std::shared_ptr<NodoGrafo<T>> connectedNode = nodo->getConexion(j);

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

    Grafo<int> grafo;
    for(int i = 0; i < 10; i++){
        grafo.agregarNodo(i+1);
    }
    grafo.agregarArista(0, 1);
    grafo.agregarArista(1, 2);
    grafo.agregarArista(0, 2);
    grafo.agregarArista(2, 3);
    grafo.agregarArista(3, 4);
    grafo.agregarArista(1, 5);
    grafo.agregarArista(5, 6);
    grafo.agregarArista(6, 4);
    grafo.agregarArista(4, 7);
    grafo.agregarArista(5, 8);
    grafo.agregarArista(8, 9);

    grafo.imprimirGrafo();
    cout<<"--------------------\n";
    cout<<"Matriz de adjacencia: \n";
    grafo.matrizAdjacencia();


    std::vector<int> path = grafo.shortestPath(0, 6);
    int size = path.size();
    if(size > 0){
        grafo.getNodo(path[0])->setLabel("START");
        for(int i = 0; i < size; i++){
            cout<<path[i]<<" ";
            grafo.getNodo(path[i])->setColor(75, (int8_t) (255 / path.size()  * (i + 1)), 50);
            i > 0 ? grafo.getNodo(path[i])->setLabel("step " + to_string(i)) : void(0);
        }
        grafo.getNodo(path[size-1])->setLabel("END");
    }


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

        if(size > 0){
            sf::Text label;
            label.setFont(font); // Use the loaded font
            label.setCharacterSize(32);
            label.setFillColor(sf::Color::Black);
            label.setString("Path Length: " + to_string(path.size())); // Use node index as label (add 1 to start from 1)
            label.setPosition(20, 15);
            window.draw(label);
        }

        // Render your graph here using SFML drawing functions

        window.display();


    }

    return EXIT_SUCCESS;

}
