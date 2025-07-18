#include "VerletObject.hpp"
#include <iostream>


// Public Methods
// Consturctor
VerletObject::VerletObject(sf::Vector2f position, float radius, sf::Color color):m_radius(radius), m_color(color),
m_position(position), m_oldPosition(position), m_acceleration({0.0f, 0.0f}){

}


void VerletObject::update(float passagemDeTempoEntreFrame) {
    m_position = m_position + (m_acceleration * passagemDeTempoEntreFrame);
}


void VerletObject::applyForce(sf::Vector2f force) {
    m_position = m_position + force;
}


void VerletObject::setPosition(sf::Vector2f newPosition) {
    std::cout<< "seta nova posição" << std::endl;
}


sf::Vector2f VerletObject::getPosition() const {
    return m_position;
}

sf::Vector2f VerletObject::getOldPosition() const {
    return m_oldPosition;
}

sf::Color VerletObject::getColor() const {
    return m_color;
}

float VerletObject::getRadius() const {
    return m_radius;
}
