#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.h"
#include <algorithm>

void Game::init() {
    colours[0] = sf::Color::Blue;
    colours[1] = sf::Color::Red;
    colours[2] = sf::Color::Green;
    colours[3] = sf::Color::Yellow;
    colours[4] = sf::Color::Cyan;
    colours[5] = sf::Color::Magenta;
	window.create(sf::VideoMode(win_width, win_height), "Particles");
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
        mouse();
        window.clear(sf::Color::White);
        update();
        window.display();
    }
}

void Game::mouse() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, 1000.0);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto mouse_pos = sf::Mouse::getPosition(window);
        
        for (int i{ 0 };i <= 10;i++) {
           sf::Color rand_colour = sf::Color(int(dist(mt)),int(dist(mt)), int(dist(mt)), 255);
           Particle particle(20, rand_colour);//colours[int(dist(mt)) % 6]
           
           particle.particle.setRadius(particle.radius);
           sf::Vector2f particle_pos = particle.normalise(sf::Vector2f(int(dist(mt)) % 10 - 5, int(dist(mt)) % 10 - 5), 1);
           particle.particle.setPosition(mouse_pos.x+particle_pos.x, mouse_pos.y+particle_pos.y);
           particle.particle.setFillColor(particle.colour);
           particle.direction.x = int(dist(mt)) % 10 - 5;
           particle.direction.y = int(dist(mt)) % 10 - 5;
           particles.push_back(particle);

        }
            
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
    for (auto& particle : particles) {
        window.draw(particle.particle);
        particle.update();
    }
    for (auto i = particles.begin();i != particles.end();)
    {
        if ((*i).radius <= 0) {
            i = particles.erase(i);
        }
        else {
            i++;
        }
    }
}

