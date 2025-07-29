#include "CircleConstraint.hpp"
#include <cmath>
#include "../utils/physicsUtils.hpp"

CircleConstraint::CircleConstraint(const sf::Vector2f center, const float radius): m_center(center), m_radius(radius) {
}

void CircleConstraint::apply(std::vector<VerletObject> &objects) const {
    for (VerletObject &object : objects) {
        const sf::Vector2f toObj = object.getPosition() - m_center;
        const float distHypot = std::sqrt(toObj.x * toObj.x + toObj.y * toObj.y);
        float minDist = m_radius - object.getRadius();

        if (distHypot > minDist) {
            sf::Vector2f normalVectToObj = toObj / distHypot;
            const sf::Vector2f newPos = m_center + normalVectToObj * minDist;

            // bounce off the walls
            const sf::Vector2f velocity = object.getPosition() - object.getOldPosition();
            object.setPosition(newPos);
            resolveCollision(object, velocity, normalVectToObj);
        }
    }
}
