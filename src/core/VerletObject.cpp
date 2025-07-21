#include "VerletObject.hpp"
#include <iostream>


VerletObject::VerletObject(sf::Vector2f position, float radius, sf::Color color):m_radius(radius), m_color(color),
m_position(position), m_oldPosition(position), m_acceleration({0.0f, 0.0f}){

}

void VerletObject::update(float passagemDeTempoEntreFrame) {
    constexpr float FRICTION = 1; // ajeitar depois
    sf::Vector2f velocity = m_position - m_oldPosition;
    velocity = velocity * FRICTION;
    m_oldPosition = m_position;

    // Nova posição = Posição atual + Velocidade + Aceleração * dt*dt
    m_position = m_position + velocity + (m_acceleration * (passagemDeTempoEntreFrame * passagemDeTempoEntreFrame));

    m_acceleration = {0.0f, 0.0f};
}


void VerletObject::applyForce(sf::Vector2f force) {
    m_acceleration = m_acceleration + force;
}


void VerletObject::setPosition(sf::Vector2f newPosition) {
    m_position = newPosition;
}

void VerletObject::setOldPosition(sf::Vector2f newPosition) {
    m_oldPosition = newPosition;
}


sf::Vector2f VerletObject::getPosition() const {
    return m_position;
}

sf::Vector2f VerletObject::getOldPosition() const {
    return m_oldPosition;
}

sf::Vector2f VerletObject::getAcceleration() const {
    return m_acceleration;
}

sf::Color VerletObject::getColor() const {
    return m_color;
}

float VerletObject::getRadius() const {
    return m_radius;
}
