#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Firework.h"


void Game::init() {
    window.create(current_videomode, "My Game");
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
            case sf::Event::Resized:
                
                sf::FloatRect visibleArea(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
                window.setView(sf::View(visibleArea));
            }

        }
        int randxpos = rand() % 1280;
        //Firework firework(5.0f, sf::Vector2i(randxpos, 600));
        //fireworks.push_back(firework);
        window.clear(sf::Color(0x0b0b62ff));
        update();
        window.display();
    }
}

void Game::mouse() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        Firework firework(5, sf::Mouse::getPosition(window));
        fireworks.push_back(firework);

    }


    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    }

}

void Game::keyboard() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
}

void Game::update() {
    if (!fireworks.empty()) {
        for (auto firework = fireworks.begin(); firework != fireworks.end(); ++firework)
        {
            firework->update();

            if (firework->exploded && !firework->explosion.empty()) {
                for (auto bit = firework->explosion.begin(); bit != firework->explosion.end(); ++bit) {
                    if (bit->radius >= 2) {
                        bit->update();
                        window.draw(bit->circle);
                    }
                    else {
                        firework->explosion.erase(bit);
                        break;
                    }
                }
            }
            if (!firework->exploded) {
                window.draw(firework->firework);
            }
            if (firework->finished) {
                fireworks.erase(firework);
                break;
            }
        }
    }
    

}