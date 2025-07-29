#include "physicsUtils.hpp"
#include <iostream>

void resolveCollision(VerletObject &obj, const sf::Vector2f &impactVelocity, const sf::Vector2f &normalCollision) {
    const float dotProduct = impactVelocity.x * normalCollision.x + impactVelocity.y * normalCollision.y;
    const sf::Vector2f reflectedVelocity = impactVelocity - (2.0f * dotProduct * normalCollision);
    //reflectedVelocity = reflectedVelocity * damping;

    obj.setOldPosition(obj.getPosition() - reflectedVelocity);
}
