#pragma once
#include "SFML/System/Vector2.hpp"

namespace configConsts {
    // Window Config
    constexpr float WINDOW_WIDTH_F = 1280.0f;
    constexpr float WINDOW_HEIGHT_F = 720.0f;
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr int MAX_FPS = 60;

    // Physics Config
    constexpr int SUB_STEPS = 1;
    constexpr sf::Vector2f GRAVITY_FORCE = {0.0f, 100.0f};
    constexpr float FRICTION = 1.0f; // 0.0 - 1.0
    constexpr float COLLISION_DAMPING = 1.0f; // 0.0 - 1.0
    constexpr float STICKY_THRESHOLD = 0.01f; // Limiar para evitar que objetos grudem nas restrições

    // Environment Constrains
    constexpr float CIRCLE_CONSTRAINT_RADIUS = 325.0f;

    // Verlet Objects
    constexpr float VERLET_BALL_RADIUS = 15.0f;
    constexpr float SPAWN_INTERVAL_SECONDS = 1.0f;
    constexpr int MAX_SPAWNED_OBJECTS = 10;
}
