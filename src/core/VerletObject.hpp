#pragma once
#include <SFML/Graphics.hpp>

/*
 * Class inicialmente da bolinha
 */

class VerletObject {
    float m_radius;
    sf::Color m_color;

    sf::Vector2f m_position;
    sf::Vector2f m_oldPosition;
    sf::Vector2f m_acceleration;

    public:
    VerletObject(sf::Vector2f position, float radius, sf::Color color);
    void update(float dt);
    void applyForce(sf::Vector2f force);

    // setters
    void setPosition(sf::Vector2f newPosition);
    void setOldPosition(sf::Vector2f newPosition);

    // getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getOldPosition() const;
    sf::Vector2f getAcceleration() const;
    sf::Color getColor() const;
    float getRadius() const;
};
