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
    ifstream file("sources.json");
    file >> root;

    unsigned int wavelength          = root["wavelength"].asFloat();
    double delta_shift_per_iteration = root["delta_shift_per_iteration"].asFloat();

    for(unsigned int i = 0 ; i < root["sources"].size() ; i++)
    {
        sources.push_back(Vector2f(root["sources"][i]["x"].asFloat(), root["sources"][i]["y"].asFloat()));
    }

    sf::Vector2f window_size(1000, 1000);
    sf::Vector2f matrix_size = window_size;

    NodeMatrix matrix(matrix_size, 1);


    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Wave Sim");
    double phase_shift_per_unit = -3.14;
    while (window.isOpen())
    {
        phase_shift_per_unit += delta_shift_per_iteration;
        cout << "phase: " << phase_shift_per_unit << "radians" << endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        matrix.reset();


        for(unsigned int i = 0 ; i < sources.size() ; i++)
            matrix.computeMatrix(WaveSource(sources[i], wavelength, i * phase_shift_per_unit));


        matrix.computeImage();

        window.draw(matrix);
        for(unsigned int i = 0 ; i < sources.size() ; i++)
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
