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

            // collision detection
            sf::Vector2f collisionAxis = obj1.getPosition() - obj2.getPosition();
            float distHip = std::sqrt(collisionAxis.x * collisionAxis.x + collisionAxis.y * collisionAxis.y);
            float minDistance = obj1.getRadius() + obj2.getRadius();
            if (distHip < minDistance) {
                // resolve collision
                sf::Vector2f obj1Velocity = obj1.getPosition() - obj1.getOldPosition();
                sf::Vector2f obj2Velocity = obj2.getPosition() - obj2.getOldPosition();
                float invertedTotalMass = 1.0f/obj1.getMass() + 1.0f/obj2.getMass();

                if (invertedTotalMass == 0.0f) continue;

                float overlapProportionalToMass = (minDistance - distHip) / invertedTotalMass;
                sf::Vector2f normalCollisionDirVect = collisionAxis / distHip; //(obj1 to obj2)
                float correctionPos1ProportionalToMass = (overlapProportionalToMass * 1.0f / obj1.getMass());
                float correctionPos2ProportionalToMass = (overlapProportionalToMass * 1.0f / obj2.getMass());

                obj1.setPosition(obj1.getPosition() + normalCollisionDirVect * correctionPos1ProportionalToMass);
                obj2.setPosition(obj2.getPosition() - normalCollisionDirVect * correctionPos2ProportionalToMass);

                // resolve impulse
                float relativeVelocityAlongNormal = (obj1Velocity.x - obj2Velocity.x) * normalCollisionDirVect.x +
                    (obj1Velocity.y - obj2Velocity.y) * normalCollisionDirVect.y;

                if (relativeVelocityAlongNormal >= 0.0f) {
                    continue; // Já estão se afastando ou deslizando, não aplique impulso
                }

                // formula do impulso J = -(1 + e) * (V_rel . N) / (1/m1 + 1/m2)
                float impulseMag = -(1.0f + 1.0f) * relativeVelocityAlongNormal/invertedTotalMass;
                sf::Vector2f impulse = impulseMag * normalCollisionDirVect;

                sf::Vector2f deltaV1 = impulse / obj1.getMass();
                sf::Vector2f deltaV2 = impulse / obj2.getMass();
                obj1.setOldPosition(obj1.getPosition() - (obj1Velocity + deltaV1));
                obj2.setOldPosition(obj2.getPosition() - (obj2Velocity - deltaV2));
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
        for (std::unique_ptr<Constraint> &constraint: m_constraints) {
            constraint->apply(m_objects);
        }
        solveCollisions();
    }
    updatePositions(dt);
    std::cout << "Energia Cinetica Total: " << calculateTotalSistemKineticEnergy() << std::endl;
}

void Engine::addConstraint(std::unique_ptr<Constraint> constraint) {
    m_constraints.emplace_back(std::move(constraint));
}


const std::vector<VerletObject>& Engine::getObjects() const {
    return m_objects;
}

float Engine::calculateTotalSistemKineticEnergy() const {
    float totalKE = 0.0f;
    for (const VerletObject &object : m_objects) {
        const sf::Vector2f velocity = object.getPosition() - object.getOldPosition();
        const float sqVelocityMagnitude = velocity.x * velocity.x + velocity.y * velocity.y;
        totalKE = totalKE + (0.5f * sqVelocityMagnitude);
    }
    return totalKE;
}
