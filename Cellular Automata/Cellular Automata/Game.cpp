#include "Game.h"
#include <SFML/Graphics.hpp>
#include <math.h>

Game::Game()
    : window(sf::VideoMode(win_width, win_height), "Cellular Automata"),
      Map(window)
{
    window.setFramerateLimit(60);
}

void Game::init() {
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                keyboard();
                break;
            case sf::Event::MouseButtonPressed:
                break;
            }
        }
        mouse();
        window.clear(sf::Color::White);
        Map.update();
        Map.draw();
        window.display();
    }
}

void Game::mouse() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto MousePosition = sf::Mouse::getPosition(window);
        //Map.AddElement(MousePosition.x, MousePosition.y, Material::sand);
        int radius = 50;
        for (int r = 0; r <= radius; r++) {
            for (int x = -r; x <= r; x++) {
                int y = std::sqrtf(pow(radius, 2) - pow(x, 2));
                Map.AddElement(MousePosition.x + x, MousePosition.y + y, material_type);
                Map.AddElement(MousePosition.x + x, MousePosition.y - y, material_type);
            }
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        auto MousePosition = sf::Mouse::getPosition(window);
        //Map.AddElement(MousePosition.x, MousePosition.y, Material::sand);
        int radius = 10;
        if ((10 < MousePosition.x && MousePosition.x <= win_width - 10) && (0 <= MousePosition.y && MousePosition.y <= win_height)) {
            for (int r = 0; r <= radius; r++) {
                for (int x = -r; x <= r; x++) {
                    int y = std::sqrtf(pow(radius, 2) - pow(x, 2));
                    Map.AddElement(MousePosition.x + x, MousePosition.y + y, material_type);
                    Map.AddElement(MousePosition.x + x, MousePosition.y - y, material_type);
                }
            }
        }
    }

}

void Game::keyboard() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Map.update();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        material_type = Material::sand;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        material_type = Material::water;
    }
    
}