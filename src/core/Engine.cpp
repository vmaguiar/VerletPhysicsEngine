#include "Engine.hpp"

#include <iostream>

#include "SFML/Audio/Listener.hpp"

// private methods
void Engine::applyGravity() {
    constexpr float GRAVITY_X = 0.0f;
    constexpr float GRAVITY_Y = 100.0f; // ajeitar nas constantes

    for (VerletObject &object : m_objects) {
        object.applyForce(sf::Vector2f(GRAVITY_X, GRAVITY_Y));
    }
}

void Engine::applyConstraints() {
    // primeiro fazer as restrições de tela para nao passar da janela
    for (VerletObject &object : m_objects) {
        sf::Vector2f pos = object.getPosition();
        sf::Vector2f oldPos = object.getOldPosition();
        float radius = object.getRadius();
        constexpr float BOUCINESS = 1.0f; // ajeitar depois

        // se posição do obj.x + raio > width da tela => colidiu com a direita da janela
        // se pos do obj.x - raio < 0 => colidiu com a esquerda da janela
        // se pos do obj.y + raio > height da tela => colidiu parte de baixo da janela
        // se pos do obj.y - raio < 0 => colidiu parte de cima janela
        if (pos.x + radius >= 1920.0f) {
            pos.x = 1080.0f - radius;
            oldPos.x = pos.x + (pos.x - oldPos.x) * BOUCINESS;
        }
        if (pos.x - radius <= 0) {
            pos.x = 0 + radius;
            oldPos.x = pos.x + (pos.x - oldPos.x) * BOUCINESS;
        }
        if (pos.y + radius >= 1080.0f) {
            // resolver colisão -> inverte a velocidade no eixo que houve colisao
            //primeiro evitamos que a bolinha fiquei presa e fazemos ela ficar colada na parede
            // depois vamos inverter (no eixo certo) a "velocidade", no caso (P' - oldP') tem que ser inverso a (P - oldP)
            // mas so podemos mudar oldP', entao isola OldP' -> P' -oldP' = -P + oldP
            // oldP' = P + P' -oldP
            //P' é posição apos se reposicionado
            // P - oldP é "velocidade" antes do rebote
            // oldP' é o valor para velocidade ser invertida
            pos.y = 1080.0f - radius; // reposicionando na borda
            oldPos.y = pos.y + (pos.y - oldPos.y) * BOUCINESS;
        }
        if (pos.y - radius <= 0) {
            pos.y = 0 + radius;
            oldPos.y = pos.y + (pos.y - oldPos.y) * BOUCINESS;
        }

        object.setPosition(pos);
        object.setOldPosition(oldPos);
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
    constexpr int SUB_STEPS = 16;
    float subDeltaTime = dt / static_cast<float>(SUB_STEPS); //ajustar aqui os sub passos

    for (int i = 0; i < SUB_STEPS; i++) {
        applyGravity();
        applyConstraints();
        solveCollisions();
        updatePositions(subDeltaTime);
    }
}

const std::vector<VerletObject>& Engine::getObjects() const {
    return m_objects;
}