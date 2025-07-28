#pragma once
#include "Constraint.hpp"

class CircleConstraint : public Constraint {
    sf::Vector2f m_center;
    float m_radius;

public:
    CircleConstraint(sf::Vector2f center, float radius);
    void apply(std::vector<VerletObject>& objects) const override;
};