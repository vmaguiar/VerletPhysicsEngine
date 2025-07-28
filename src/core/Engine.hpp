#pragma once
#include "VerletObject.hpp"
#include "../core/configConsts.hpp"

class Engine {
    std::vector<VerletObject> m_objects;

    void applyGravity();
    void applyConstraints();
    void solveCollisions();
    void updatePositions(float dt);


    public:
    Engine();

    void addObject(VerletObject object);
    void update(float dt);
    const std::vector<VerletObject>& getObjects() const; // pega uma referencia constante do vector de obj para desenhar ou interagir
};