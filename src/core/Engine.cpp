#include "Engine.hpp"

#include <iostream>
#include <cmath>

// private methods
void Engine::applyGravity() {
    for (VerletObject &object : m_objects) {
        object.applyForce(configConsts::GRAVITY_FORCE);
    }
}

void Engine::applyConstraints() {
    // circulo
    float circleConstraintRadius = 400.0f;
    sf::CircleShape circleConstraint(circleConstraintRadius);
    circleConstraint.setOrigin({circleConstraintRadius, circleConstraintRadius});
    circleConstraint.setPosition(sf::Vector2f(configConsts::WINDOW_WIDTH_F * 0.5f, configConsts::WINDOW_HEIGHT_F * 0.5f));


    for (VerletObject &object : m_objects) {
        sf::Vector2f toObj = object.getPosition() - circleConstraint.getPosition();
        float distHipotenusa = std::sqrt(toObj.x * toObj.x + toObj.y * toObj.y);
        if (distHipotenusa > (circleConstraintRadius - object.getRadius())) {
            sf::Vector2f normalVectToObj = toObj/distHipotenusa;
            sf::Vector2f pos = circleConstraint.getPosition() + normalVectToObj * (circleConstraintRadius - object.getRadius());
            object.setPosition(pos);
        }
    }
}
void Engine::solveCollisions() {
    // Lógica de colisão entre bolinhas (muito importante para Verlet)
    for (size_t i = 0; i < m_objects.size(); i++) {
        for (size_t j = i + 1; j < m_objects.size(); j++) {
            VerletObject &obj1 = m_objects[i];
            VerletObject &obj2 = m_objects[j];

            sf::Vector2f collisionAxis = obj1.getPosition() - obj2.getPosition();
            float distHip = std::sqrt(collisionAxis.x * collisionAxis.x + collisionAxis.y * collisionAxis.y);

            float minDistance = obj1.getRadius() + obj2.getRadius();
            if (distHip < minDistance) {
                //Colidiu
                float overlap = minDistance - distHip;
                sf::Vector2f normalCollisionDirVect = collisionAxis / distHip;

                obj1.setPosition(obj1.getPosition() + normalCollisionDirVect * overlap * 0.5f);
                obj2.setPosition(obj2.getPosition() - normalCollisionDirVect * overlap * 0.5f);
            }
        }
    }
}


void Engine::updatePositions(float dt) {
    for (VerletObject &object : m_objects) {
        object.update(dt);
    }
}


// Public Methods
Engine::Engine() = default;

void Engine::addObject(VerletObject object) {
    m_objects.emplace_back(object);
}

void Engine::update(float dt) {
    // float subDeltaTime = dt / static_cast<float>(configConsts::SUB_STEPS);

    applyGravity();
    for (int i = 0; i < configConsts::SUB_STEPS; i++) {
        applyConstraints();
        solveCollisions();
    }
    updatePositions(dt);
}

const std::vector<VerletObject>& Engine::getObjects() const {
    return m_objects;
}