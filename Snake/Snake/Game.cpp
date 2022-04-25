#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Game::init() {
	
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
        SnakeMoveCounter++;
        window.clear(sf::Color::White);
        snek.Draw();
        if (SnakeMoveCounter > SnakeMovePeriod) {
            SnakeMoveCounter = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { snek.Grow(); }
            if (snek.Dead) { DeltaLoc.x = 0, DeltaLoc.y = 0; };
            snek.MoveBy(DeltaLoc);
        }
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window.close();}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { DeltaLoc.y = -1; DeltaLoc.x = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { DeltaLoc.y = 1; DeltaLoc.x = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { DeltaLoc.y = 0; DeltaLoc.x = -1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { DeltaLoc.y = 0; DeltaLoc.x = 1; }
}