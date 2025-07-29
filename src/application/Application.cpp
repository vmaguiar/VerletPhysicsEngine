#include "Application.hpp"
#include <iostream>
#include "../constraints/CircleConstraint.hpp"

Application::Application(): m_render(m_window) {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    m_window.create(sf::VideoMode({configConsts::WINDOW_WIDTH, configConsts::WINDOW_HEIGHT}), "Balls of Verlet", sf::State::Windowed, settings);
    m_window.setFramerateLimit(configConsts::MAX_FPS);

    m_spawnTimer.restart();

    m_engine.addConstraint(std::make_unique<CircleConstraint>(sf::Vector2f(configConsts::WINDOW_WIDTH_F * 0.5f, configConsts::WINDOW_HEIGHT_F * 0.5f),
        configConsts::CIRCLE_CONSTRAINT_RADIUS));

    // addInitialObjects();
}

void Application::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds(); // passagem de tempo entre frames
        handleEvents();
        update(dt);
        render();
    }
}


// private methods
void Application::handleEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // fechar tela
            m_window.close();
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                // clicar na tecla "esc"
                m_window.close();
            }
        }
    }
}


void Application::update(float dt) {
    if (m_spawnTimer.getElapsedTime().asSeconds() >= configConsts::SPAWN_INTERVAL_SECONDS && m_bolinhaCont < configConsts::MAX_SPAWNED_OBJECTS) {
        // Meio = 640, 360 - maxX = 965 - raio da bolinha, maxY = 685 - raio da bolinha
        m_engine.addObject(VerletObject(sf::Vector2f(340.0f, 360.0f), sf::Vector2f(340.0f, 363.0f), configConsts::VERLET_BALL_RADIUS, sf::Color::Red));
        // m_engine.addObject(VerletObject(sf::Vector2f(640.0f, 500.0f), sf::Vector2f(640.0f, 505.0f), configConsts::VERLET_BALL_RADIUS, sf::Color::Yellow));
        m_spawnTimer.restart();
        m_bolinhaCont++;
    }
    m_engine.update(dt);
}

void Application::render() {
    m_window.clear(sf::Color::White);
    // m_window.clear();
    m_render.draw(m_engine.getObjects());
    m_window.display();
}

void Application::addInitialObjects() {
    // Hardcodando as bolinhas aqui
    // m_engine.addObject(VerletObject(sf::Vector2f(300.0f, 85.0f), 15.0f, sf::Color::Red));
    // m_engine.addObject(VerletObject(sf::Vector2f(250.0f, 200.0f), 15.0f, sf::Color::Green));
    // m_engine.addObject(VerletObject(sf::Vector2f(260.0f, 200.0f), 15.0f, sf::Color::Blue));
    // m_engine.addObject(VerletObject(sf::Vector2f(290.0f, 200.0f), 15.0f, sf::Color::Yellow));
    // m_engine.addObject(VerletObject(sf::Vector2f(200.0f, 190.0f), 15.0f, sf::Color::Yellow));
    // m_engine.addObject(VerletObject(sf::Vector2f(230.0f, 130.0f), 15.0f, sf::Color::Blue));
    // m_engine.addObject(VerletObject(sf::Vector2f(260.0f, 195.0f), 15.0f, sf::Color::Green));
    // m_engine.addObject(VerletObject(sf::Vector2f(200.0f, 170.0f), 15.0f, sf::Color::Red));
}
