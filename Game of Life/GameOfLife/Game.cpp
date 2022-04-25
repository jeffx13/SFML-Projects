#include "Game.h"
#include <SFML/Graphics.hpp>


Game::Game():
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
                mouse();
                break;
            }
        }
        frame++;
        window.clear(sf::Color::White);
        if (frame >= framerate && update) {
            Map.update();
            //frame = 0;

        }
        
        Map.draw();
       
        window.display();
    }
}

void Game::mouse() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        Map.AddGlider(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    }

}

void Game::keyboard() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Map.update();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        update = true;
    }
}