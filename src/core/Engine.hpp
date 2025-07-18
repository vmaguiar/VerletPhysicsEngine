#pragma once
#include "VerletObject.hpp"

class Engine {
    std::vector<VerletObject> m_objects;

    // aplica gravidade em todos obj
    // void applyGravity();
    // // aplica a integração de verlet para att posições
    // void updatePositions();
    // // resolve as colisões
    // void solveCollisions();
    // // aplica as retrições de ambiente
    // void applyConstraints();

    public:
    Engine();

    // Add um VerletObject a Engine
    void addObject(VerletObject object);

    void update(float dt);

    // getters
    // pega uma referencia constante do vector de obj para desenhar ou interagir
    const std::vector<VerletObject>& getObjects() const;
};