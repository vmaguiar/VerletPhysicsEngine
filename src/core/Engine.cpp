#include "Engine.hpp"


// Public Methods
Engine::Engine() {

}


void Engine::addObject(VerletObject object) {
    m_objects.emplace_back(object);
}


void Engine::update(float dt) {
    constexpr int SUB_STEPS = 1;
    float subDeltaTime = dt / static_cast<float>(SUB_STEPS); //ajustar aqui os sub passos
    for (int i = 0; i < SUB_STEPS; i++) {
        //applyGravity();
        //applyConstraints();
        //solveCollisions();
        //updatePositions();
    }
}


const std::vector<VerletObject> &Engine::getObjects() const {
    return m_objects;
}
