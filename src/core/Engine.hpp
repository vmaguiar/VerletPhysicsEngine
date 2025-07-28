#pragma once
#include "VerletObject.hpp"
#include "../constraints/Constraint.hpp"
#include "../core/configConsts.hpp"

class Engine {
    std::vector<VerletObject> m_objects;
    std::vector<std::unique_ptr<Constraint>> m_constraints;

    void applyGravity();
    void applyConstraints();
    void solveCollisions();
    void updatePositions(float dt);


    public:
    Engine();

    void addObject(VerletObject object);
    void update(float dt);
    void addConstraint(std::unique_ptr<Constraint> constraint);
    const std::vector<VerletObject>& getObjects() const; // pega uma referencia constante do vector de obj para desenhar ou interagir
};