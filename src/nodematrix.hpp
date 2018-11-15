#ifndef NODEMATRIX
#define NODEMATRIX

#include "node.hpp"
#include "wavesource.hpp"

class NodeMatrix : public sf::Drawable {
public:
    NodeMatrix(sf::Vector2f size, unsigned int quantum);
    void computeMatrix(WaveSource source);
    void computeImage();
    void reset();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::VertexArray vertices;
    std::vector<std::vector<Node>> matrix;
};

#endif
