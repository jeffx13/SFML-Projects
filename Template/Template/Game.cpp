#include "Game.h"
#include <SFML/Graphics.hpp>


void Game::init() {
	window.create(sf::VideoMode(win_width, win_height), "My Game");
	window.setFramerateLimit(60);

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
                mouse();
                break;
            }

        }

        window.clear(sf::Color::White);

        window.display();
    }
}

void Game::mouse() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    }

}

void Game::keyboard() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
}