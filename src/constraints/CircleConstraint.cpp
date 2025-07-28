#include "CircleConstraint.hpp"
#include <cmath>
#include <iostream>

CircleConstraint::CircleConstraint(sf::Vector2f center, float radius): m_center(center), m_radius(radius) {
}

void CircleConstraint::apply(std::vector<VerletObject> &objects) const {
    for (VerletObject &object : objects) {
        sf::Vector2f toObj = object.getPosition() - m_center;
        float distHypot = std::sqrt(toObj.x * toObj.x + toObj.y * toObj.y);
        float minDist = m_radius - object.getRadius();

        if (distHypot > minDist) {
            sf::Vector2f nVectToObj = toObj / distHypot;
            sf::Vector2f newPos = m_center + nVectToObj * minDist;

            // bounce off the walls
            sf::Vector2f velocity = object.getPosition() - object.getOldPosition();
            float dotProduct = velocity.x * nVectToObj.x + velocity.y * nVectToObj.y;
            sf::Vector2f reflectedVelocity = velocity - (2.0f * dotProduct * nVectToObj);
            object.setOldPosition(newPos - reflectedVelocity);
            object.setPosition(newPos);

            object.setOldPosition(newPos);
            object.setPosition(newPos);
        }
    }

    // for (VerletObject &object : m_objects) {
    //     sf::Vector2f toObj = object.getPosition() - circleConstraint.getPosition();
    //     float distHipotenusa = std::sqrt(toObj.x * toObj.x + toObj.y * toObj.y);
    //     if (distHipotenusa > (circleConstraintRadius - object.getRadius())) {
    //         sf::Vector2f normalVectToObj = toObj/distHipotenusa;
    //         sf::Vector2f pos = circleConstraint.getPosition() + normalVectToObj * (circleConstraintRadius - object.getRadius());
    //         object.setPosition(pos);
    //     }
    // }
}
