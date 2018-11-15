#ifndef DEF_NODE
#define DEF_NODE

#include <SFML/Graphics.hpp>
#include <math.h>
#include "wavesource.hpp"

class Node {
public:
    Node(sf::Vector2f position, sf::Vector2f size);
    void computeIntensity(WaveSource wave_source);
    void resetIntensity() { intensity = 0; }

    int getIntensity()         { return intensity; }
    sf::Vector2f getPosition() { return position; }
    sf::Vector2f getQuantum()  { return size; }

private:
    sf::Vector2f position;
    sf::Vector2f size;
    int intensity;
};

#endif
