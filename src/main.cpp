#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>

#include "json/json.h"
#include "node.hpp"
#include "wavesource.hpp"
#include "nodematrix.hpp"

using namespace std;
using namespace sf;




int main() {

    vector<Vector2f> sources ({
        Vector2f(500, 500),
        Vector2f(500, 510),
        Vector2f(510, 500)
    });
    unsigned int wavelength = 20;


    sf::Vector2f window_size(1000, 1000);
    sf::Vector2f matrix_size = window_size;

    NodeMatrix matrix(matrix_size, 1);


    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Wave Sim");
    double phase_shift_per_unit = -3.14;
    while (window.isOpen())
    {
        phase_shift_per_unit += 0.2;
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
