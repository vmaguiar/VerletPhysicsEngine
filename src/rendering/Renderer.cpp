#include "Renderer.hpp"

Renderer::Renderer(sf::RenderWindow &window):m_window(window) {

}


void Renderer::draw(const std::vector<VerletObject> &objects) {
    for (const VerletObject &object : objects) {
        sf::CircleShape circle(object.getRadius());
        circle.setOrigin({object.getRadius(), object.getRadius()});
        circle.setPosition(object.getPosition());
        circle.setFillColor(object.getColor());
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(1.0f);
        m_window.draw(circle);
    }
}
