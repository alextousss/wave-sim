#ifndef WAVE_SOURCE
#define WAVE_SOURCE

#include <SFML/Graphics.hpp>


class WaveSource {
public:
    WaveSource(sf::Vector2f position, unsigned int length, double phase) : position(position), length(length), phase(phase) {}
    sf::Vector2f getPosition()  { return position; }
    double getLength()          { return length; }
    double getPhase(){return phase; }
private:
    sf::Vector2f position;
    double length;
    double phase;
};

#endif
