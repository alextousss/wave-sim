#include "node.hpp"
#include <iostream>



using namespace sf;
using namespace std;

unsigned int distanceBetweenPoints(Vector2f point1, Vector2f point2)
{
    return sqrt(
        pow(point1.x - point2.x, 2) +  pow(point1.y - point2.y, 2)
    );
}


Node::Node(sf::Vector2f position, sf::Vector2f size) {
    this->position = position;
    this->size = size;
    this->intensity = 155;
}

void Node::computeIntensity(WaveSource wave_source) {
    unsigned int distance = distanceBetweenPoints(position, wave_source.getPosition());
    intensity += sin(((2*3.14*distance))/wave_source.getLength() + wave_source.getPhase()) * 255;
}
