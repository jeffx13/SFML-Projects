#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <typeinfo>

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

                break;
            case sf::Event::MouseButtonPressed:
                mouse();
                break;
            }

        }


        window.clear(sf::Color::Black);
        update();
        window.display();
    }
}

void Game::update() {
    mouse();
    keyboard();
    terrain.Update();
    
    

}

void Game::mouse() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    }
}

void Game::keyboard() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    

}

void Game::init_players() {
   /* players.clear();
    srand((unsigned)time(NULL));
    for (int i = 1; i <= player_count; i++) {
        Player player{ i };
        player.colour.r = rand() % 256 + 127;
        player.colour.g = rand() % 256 + 127;
        player.colour.b = rand() % 256 + 127;
        player.circle.setFillColor(player.colour);
        player.circle.setPosition(rand() % (win_width - 10), rand() % (win_height - 10));
        player.last_break_done = std::chrono::steady_clock::now();
        player.last_break = std::chrono::steady_clock::now();
        player.type = "player";
        players.push_back(player);
    }
    for (int i = player_count + 1; i <= player_count + 1 + cpu_count; i++) {
        Player player{ i };
        player.colour.r = rand() % 256;
        player.colour.g = rand() % 256;
        player.colour.b = rand() % 256;
        player.circle.setFillColor(player.colour);
        player.circle.setPosition(rand() % (win_width - 10), rand() % (win_height - 10));
        player.last_break_done = std::chrono::steady_clock::now();
        player.last_break = std::chrono::steady_clock::now();
        player.type = "cpu";
        players.push_back(player);
    }*/
}
