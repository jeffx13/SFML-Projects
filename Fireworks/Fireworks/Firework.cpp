#include "Firework.h"
#include <random>
#include <chrono>
#include <iostream>

void Firework::init()
{
}

void Firework::explode()
{   
    int speed = 1;
    std::random_device rd;
    std::mt19937 mt{ rd() };
    //std::uniform_real_distribution<float> randnum(-100, 100);
    std::vector<int> explosion_radii{ 2,4,6,8 }; 
    float centrex = firework.getGlobalBounds().left + firework.getRadius();
    float centrey = firework.getGlobalBounds().top + firework.getRadius();

    for (auto radius:explosion_radii) {
        std::uniform_real_distribution<float> randnum(-radius, radius);
        float speed = 5 + rand() % 6;
        for (size_t i = 0; i < 25; i++)
        {
            std::cout << radius << std::endl;
            float randx = randnum(mt);
            
            float randy = -1 + rand() % 3;
            if (randy == 0) { randy++; }
            randy *= sqrtf(pow(radius, 2) - pow(randx, 2));
            int rand_colour = rand() % colours.size();
            float x = centrex + randx;
            float y = centrey + randy;
            if (randy == 1) { ; }
            
            float xdir = randx / speed;
            float ydir = randy / speed;
            //std::cout << randx << " " << randy << std::endl;

            Exploded_bit bit{ explosion_bit_radius, sf::Vector2f(x,y),sf::Vector2f(xdir,ydir), colours[rand_colour] };
            explosion.push_back(bit);

        }
       
    }






    /*for (size_t i = 0; i < 100; i++) 
    {
        float randx = randnum(mt);
        float randy = -1 + rand() % 3;
        if (randy == 0) { randy++  ;}
        randy *= sqrtf(pow(explosion_radius, 2) - pow(randx, 2));
        int rand_colour = rand() % colours.size();
        int x = centrex + randx;
        int y = centrey + randy;
        if (randy == 1) { ; }
        int xdir = randx/5;
        int ydir = randy/5;
        std::cout << randx << " " << randy << std::endl;
        
        Exploded_bit bit{ explosion_bit_radius, sf::Vector2f(x,y),sf::Vector2f(xdir,ydir), colours[rand_colour] };
        explosion.push_back(bit);
        
        }*/
            
}

void Firework::update()
{
    current = std::chrono::system_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(current - init_time) < explosion_countdown) {
        firework.move(0, -speed);
        for (size_t i{}; i < 10; i++)
        {
            unsigned char randxdir = -1 + rand() % 3;
            unsigned char randydir = -10 + rand() % 21;
            Smoke_particle particle(firework.getPosition() , sf::Vector2f(randxdir, randydir));
            smoke.push_back(particle);
            }
    }
    else if (not exploded) {
        explode();
        exploded = true;
    }

    if (exploded && explosion.empty()) {
        finished = true;
    }
}

void Exploded_bit::update()
{   
    
    
    
    if (angle_rotated <=60) {
        direction.x = direction.x * cos(rotation_angle * 3.1415926 / 180) + direction.y * -sin(rotation_angle * 3.1415926 / 180);
        direction.y = direction.x * sin(rotation_angle * 3.1415926 / 180) + direction.y * cos(rotation_angle * 3.1415926 / 180);
        angle_rotated += rotation_angle;
        circle.move(direction);
    }
    else {
        if (colour.a >= 15) {
            colour.a -= 15;
            if (colour.a > 100) {
                radius -= 1;
            }
        }
    } 
    circle.move(direction);
    circle.setRadius(radius);
    circle.setFillColor(colour);
    
}


void Smoke_particle::update()
{
    

}