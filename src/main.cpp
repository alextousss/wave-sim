#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>

#include "json/json.h"
#include "node.hpp"
#include "wavesource.hpp"
#include "nodematrix.hpp"

using namespace std;
using namespace sf;



int main() {

    vector<Vector2f> sources;

    Json::Value root;
    ifstream file("parameters.json");  // On vient lire les paramètres dans le fichier JSON
    file >> root;

    unsigned int wavelength          = root["wavelength"].asFloat();
    double delta_shift_per_iteration = root["delta_shift_per_iteration"].asFloat();

    for(unsigned int i = 0 ; i < root["sources"].size() ; i++)
    {  // On ajoute les coordonnées dessources trouvées dans le fichier JSON
        sources.push_back(Vector2f(root["sources"][i]["x"].asFloat(), root["sources"][i]["y"].asFloat()));  
    }

    sf::Vector2f window_size(1000, 1000);
    sf::Vector2f matrix_size = Vector2f(1000, 1000);

    NodeMatrix matrix(matrix_size, root["compute_quantum"].asFloat()); // La on déclare la matrice de "noeuds" de calcul


    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Wave Sim");
    double phase_shift_per_unit = -3.14;   
    // Cette variable contient le décalage de phase entre chaque source, c'est la seule qui change entre les diférentes images
    while (window.isOpen())
    {
        phase_shift_per_unit += delta_shift_per_iteration;  // On lui ajoute sa dérivée, récupérée dans le fichier JSON
        cout << "phase: " << phase_shift_per_unit << "radians" << endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        matrix.reset();     // On remet à zero la matrice


        for(unsigned int i = 0 ; i < sources.size() ; i++)  
            // Pour chaque source, on vient recalculer la matrice en lui donnant les coordonnées, la longueur d'onde et le décalage de phase
            matrix.computeMatrix(WaveSource(sources[i], wavelength, i * phase_shift_per_unit));


        matrix.computeImage(); // On calcule l'image en fonction de la matrice


        window.draw(matrix);
        for(unsigned int i = 0 ; i < sources.size() ; i++)   // Pour chaque source, on dessine un cercle vert 
        {
            sf::CircleShape shape(5.f);
            shape.setFillColor(sf::Color(0, 255, 0));
            shape.setPosition(sources[i]);
            window.draw(shape);
        }
        window.display();
    }

    return 0;

}
