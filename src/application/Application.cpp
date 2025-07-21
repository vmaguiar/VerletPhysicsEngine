#include "Application.hpp"

#include <iostream>

Application::Application(): m_engine(), m_render(m_window) {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    m_window.create(sf::VideoMode({1920, 1080}), "Balls of Verlet", sf::State::Fullscreen, settings);
    m_window.setFramerateLimit(60);

    addInitialObjects();
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
    m_engine.update(dt);
}

void Application::render() {
    m_window.clear();
    m_render.draw(m_engine.getObjects());
    m_window.display();
}

void Application::addInitialObjects() {
    // Hardcodando as bolinhas aqui
    m_engine.addObject(VerletObject(sf::Vector2f(100.0f, 100.0f), 15.0f, sf::Color::Red));
    m_engine.addObject(VerletObject(sf::Vector2f(130.0f, 100.0f), 15.0f, sf::Color::Green));
    m_engine.addObject(VerletObject(sf::Vector2f(160.0f, 100.0f), 15.0f, sf::Color::Blue));
    m_engine.addObject(VerletObject(sf::Vector2f(190.0f, 100.0f), 15.0f, sf::Color::Yellow));
    // m_engine.addObject(VerletObject(sf::Vector2f(100.0f, 130.0f), 15.0f, sf::Color::Yellow));
    // m_engine.addObject(VerletObject(sf::Vector2f(130.0f, 130.0f), 15.0f, sf::Color::Blue));
    // m_engine.addObject(VerletObject(sf::Vector2f(160.0f, 130.0f), 15.0f, sf::Color::Green));
    // m_engine.addObject(VerletObject(sf::Vector2f(190.0f, 130.0f), 15.0f, sf::Color::Red));
}
