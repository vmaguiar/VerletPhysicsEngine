#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include "../core/VerletObject.hpp"

/*
 * Class para renderizar
 */

class Renderer {
    sf::RenderWindow &m_window;
    public:
    Renderer(sf::RenderWindow &window);
    void draw(const std::vector<VerletObject>& objects);
};