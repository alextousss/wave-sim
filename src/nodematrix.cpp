#include "nodematrix.hpp"
#include <iostream>
using namespace sf;
using namespace std;

NodeMatrix::NodeMatrix(sf::Vector2f size, unsigned int quantum) {
    matrix.resize(size.x / quantum, std::vector<Node>(size.y / quantum, Node(Vector2f(0,0), Vector2f(quantum, quantum))));
    for(unsigned int i = 0 ; i < matrix.size() ; i++)
    {
        for(unsigned int j = 0 ; j < matrix[i].size() ; j++)
        {
            matrix[i][j] = Node(Vector2f(i * quantum , j * quantum), Vector2f(quantum, quantum));
        }
    }
}

void NodeMatrix::computeMatrix(WaveSource source) {
    for(unsigned int i = 0 ; i < matrix.size() ; i++)
    {
        for(unsigned int j = 0 ; j < matrix[i].size() ; j++)
        {
            matrix[i][j].computeIntensity(source);
        }
    }
}

void NodeMatrix::computeImage() {
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize( matrix.size() * matrix[0].size() * 4 );
    double max_intensity = 0;
    for(unsigned int i = 0 ; i < matrix.size() ; i++)
    {
        for(unsigned int j = 0 ; j < matrix[i].size() ; j++)
        {
            if(matrix[i][j].getIntensity() > max_intensity)
            {
                max_intensity = matrix[i][j].getIntensity();
            }
        }
    }
    cout << max_intensity << endl;
    for(unsigned int i = 0 ; i < matrix.size() ; i++)
    {
        for(unsigned int j = 0 ; j < matrix[i].size() ; j++)
        {
            sf::Vertex* quad = &vertices[(i + j * matrix.size()) * 4];  // La, on déclare un tableau de sommets graphiques
            double intensity = matrix[i][j].getIntensity();             // Pour économiser les aller-retours GPU, on le fait une fois pour tout les noeuds
            double ajusted_intensity = intensity / max_intensity * 255.0f;  // pour chaque noeud on calcule l'intensité, 
                                                                            // relative à l'intensité max sur la matrice
            Color color( 
                ajusted_intensity > 0 ?   ajusted_intensity : 0, // Pour le rouge : on prends la partie supérieure à zero de l'intensité
                ajusted_intensity < 0 ? - ajusted_intensity : 0, // Pour le vert  : c'est l'opposé
                0
            );

            Vector2f coord      = matrix[i][j].getPosition();
            Vector2f quantum    = matrix[i][j].getQuantum();

            // Ensuite, on calcule pour chaque quadruplet de sommets la position réelle (sur l'écran)
            quad[0].color = color;
            quad[1].color = color;
            quad[2].color = color;
            quad[3].color = color;

            quad[0].position = sf::Vector2f( coord.x, coord.y + quantum.y);  
            quad[1].position = sf::Vector2f( coord.x, coord.y);
            quad[2].position = sf::Vector2f( coord.x + quantum.x, coord.y);
            quad[3].position = sf::Vector2f( coord.x + quantum.x, coord.y + quantum.y);
        }
    }
}

void NodeMatrix::reset() {
    for(unsigned int i = 0 ; i < matrix.size() ; i++)
    {
        for(unsigned int j = 0 ; j < matrix[i].size() ; j++)
        {
            matrix[i][j].resetIntensity();
        }
    }
}

void NodeMatrix::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(vertices);
}
