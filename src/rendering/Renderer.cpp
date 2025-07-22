#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(sf::RenderWindow &window):m_window(window), m_debugText(m_font, "", 13) {
    if (!m_font.openFromFile("assets/fonts/PressStart2P-Regular.ttf")) {
        std::cerr << "Error to load the Game font!" << std::endl;
    }
    m_debugText.setFillColor(sf::Color::Yellow);
}


void Renderer::draw(const std::vector<VerletObject> &objects) {
    sf::CircleShape circleConstraint(400);
    circleConstraint.setOrigin({400, 400});
    circleConstraint.setFillColor(sf::Color::Black);
    circleConstraint.setPosition(sf::Vector2f(500.0f, 400.0f));
    m_window.draw(circleConstraint);

    for (size_t i = 0; i < objects.size(); i++) {
        const VerletObject &object = objects[i];

        // --- Lógica para Desenhar o Texto de Debug --- //
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);

        sf::Vector2f pos = object.getPosition();
        sf::Vector2f oldPos = object.getOldPosition();
        // sf::Vector2f accel = object.getAcceleration();
        sf::Vector2f velocity = pos - oldPos; // Velocidade implícita

        ss << "ID: " << i << "\n"
           << "Pos: (" << pos.x << ", " << pos.y << ")\n"
           // << "OldPos: (" << oldPos.x << ", " << oldPos.y << ")\n" // Opcional, pode poluir
           << "Vel: (" << velocity.x << ", " << velocity.y << ")\n";

        m_debugText.setString(ss.str());

        // Posicionar o texto de debug ligeiramente acima ou ao lado da bolinha
        m_debugText.setPosition({pos.x + object.getRadius() + 5,
                                pos.y - object.getRadius() - m_debugText.getGlobalBounds().size.y});

        // m_window.draw(m_debugText);

        sf::CircleShape circle(object.getRadius());
        circle.setOrigin({object.getRadius(), object.getRadius()});
        circle.setPosition(object.getPosition());
        circle.setFillColor(object.getColor());
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(1.0f);
        m_window.draw(circle);
    }
}
