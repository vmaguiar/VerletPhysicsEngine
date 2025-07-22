#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include "../core/VerletObject.hpp"

/*
 * Class para renderizar
 */

class Renderer {
    sf::RenderWindow &m_window;
    sf::Font m_font;
    sf::Text m_debugText;
    public:
    explicit Renderer(sf::RenderWindow &window);
    void draw(const std::vector<VerletObject>& objects);
};