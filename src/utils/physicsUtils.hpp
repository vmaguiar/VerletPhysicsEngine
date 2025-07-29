#pragma once
#include "../core/VerletObject.hpp"

void resolveCollision(VerletObject &obj, const sf::Vector2f &impactVelocity, const sf::Vector2f &normalCollision);
