#include "Engine.hpp"

#include <iostream>
#include <cmath>

// private methods
void Engine::applyGravity() {
    for (VerletObject &object : m_objects) {
        constexpr sf::Vector2f GRAVITY = {0.0f, 100.0f};
        object.applyForce(GRAVITY);
    }
}

void Engine::applyConstraints() {
    constexpr float WINDOW_WIDTH = 1000.0f;
    constexpr float WINDOW_HEIGHT = 800.0f;

    // circulo
    float circleConstraintRadius = 400.0f;
    sf::CircleShape circleConstraint(circleConstraintRadius);
    circleConstraint.setOrigin({circleConstraintRadius, circleConstraintRadius});
    circleConstraint.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));


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
    // for (size_t i = 0; i < m_objects.size(); ++i) {
    //     for (size_t j = i + 1; j < m_objects.size(); ++j) {
    //         VerletObject& obj1 = m_objects[i];
    //         VerletObject& obj2 = m_objects[j];
    //
    //         sf::Vector2f axis = obj1.getPosition() - obj2.getPosition();
    //         float dist = std::sqrt(axis.x * axis.x + axis.y * axis.y); // Distância entre os centros
    //
    //         float minDistance = obj1.getRadius() + obj2.getRadius();
    //
    //         if (dist < minDistance) {
    //             // Colisão detectada!
    //             // Calcular a direção e magnitude da sobreposição
    //             float overlap = minDistance - dist;
    //             sf::Vector2f normal = axis / dist; // Vetor normalizado da colisão
    //
    //             // Mover os objetos para fora da sobreposição
    //             obj1.setPosition(obj1.getPosition() + normal * (overlap * 0.5f));
    //             obj2.setPosition(obj2.getPosition() - normal * (overlap * 0.5f));
    //
    //             // Opcional: Adicionar um pequeno "amortecimento" para a colisão (evita vibrações)
    //             // Isso é geralmente feito ao ajustar o m_oldPosition de cada objeto.
    //             // Mas por enquanto, a fricção global já ajuda a estabilizar.
    //         }
    //     }
    // }
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
    constexpr int SUB_STEPS = 1;
    float subDeltaTime = dt / static_cast<float>(SUB_STEPS); //ajustar aqui os sub passos

    applyGravity();
    for (int i = 0; i < SUB_STEPS; i++) {
        applyConstraints();
        // solveCollisions();
    }
    updatePositions(dt);
}

const std::vector<VerletObject>& Engine::getObjects() const {
    return m_objects;
}