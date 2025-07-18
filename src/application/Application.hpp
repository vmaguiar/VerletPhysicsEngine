#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Engine.hpp"
#include "../rendering/Renderer.hpp"

/*
 * Class logica de alto nivel "gerenciamento"
 */

class Application {
    sf::RenderWindow m_window;
    Engine m_engine;
    Renderer m_render;
    // std::vector<VerletObject> m_vectorBolinhas{};

    void handleEvents();
    void update(float dt);
    void render();

    void addInitialObjects();


    public:
    Application();
    void run();
};