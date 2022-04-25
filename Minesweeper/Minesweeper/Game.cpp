#include "Game.h"
#include <SFML/Graphics.hpp>


void Game::init() {
	window.create(sf::VideoMode(win_width, win_height), "Minesweeper");
	window.setFramerateLimit(60);
    board.create();
    draw();
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
        
    }
}

void Game::mouse() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (CheckMouseBounds(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            
            //MASS REVEAL
            if (Mass_Reveal) {
                MassReveal(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
            else {
                board.reveal(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
            draw();
        }
        
        
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (sf::Mouse::getPosition(window).x < win_width &&
            0 < sf::Mouse::getPosition(window).x &&
            sf::Mouse::getPosition(window).y < win_height &&
            0 < sf::Mouse::getPosition(window).y
            ) {
            board.flag(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            draw();
        }
    }

}

void Game::keyboard() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        board.RevealAll();
        draw();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        board.create();
        draw();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        Mass_Reveal = true;
    }
}

void Game::draw()
{
    window.clear(sf::Color::White);
    board.draw(window);
    window.display();
}

void Game::MassReveal(int MousePosX, int MousePosY)
{
    for (int i{ MousePosX - MassRevealRectSize };i <= MousePosX + MassRevealRectSize;i++)
        for (int j{ MousePosY - MassRevealRectSize };j <= MousePosY + MassRevealRectSize;j++)
        {
            if (CheckMouseBounds(i, j)) { board.reveal(i, j); }
        }
}

bool Game::CheckMouseBounds(int MousePosX, int MousePosY)
{
    if (MousePosX < win_width && 0 < MousePosX && MousePosY < win_height && 0 < MousePosY) 
    { return true; }

    return false; 
}

