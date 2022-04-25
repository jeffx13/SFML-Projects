#include "Game.h"
#include <SFML/Graphics.hpp>


void Game::init() {
	window.create(sf::VideoMode(win_width, win_height), "Sorting Algorith Visualiser");
	window.setFramerateLimit(60);
    int highest = 0;
    for (int i{};i < sorting_array_size;i++) { 
        int element = intdist(mt) % 100; 
        if (element > highest) { highest = element; }
        sorting_array.push_back(element);
    }
    scale_factor = max_height / highest;

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
        draw();
        
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        sorting_array.clear();
        int highest = 0;
        for (int i{};i < sorting_array_size;i++) {
            int element = intdist(mt) % 100;
            if (element > highest) { highest = element; }
            sorting_array.push_back(element);
        }
        scale_factor = max_height / highest;
        draw();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        bubblesort(sorting_array);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        selectionsort(sorting_array);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        quicksort(sorting_array,0,sorting_array_size-1);
        
    }

}

void Game::draw()
{
    window.clear(sf::Color::White);
    int index = 0;
    for (auto element : sorting_array) {
        sf::RectangleShape element_rect{ sf::Vector2f(element_width, element * scale_factor) };
        element_rect.setFillColor(sf::Color::Cyan);
        element_rect.setOutlineColor(sf::Color::Black);
        element_rect.setOutlineThickness(-1.0f);
        element_rect.setPosition(sf::Vector2f(offset + index * element_width, win_height-offset - element * scale_factor));
        window.draw(element_rect);
        index++;
    }

    window.display();
}

void Game::bubblesort(std::vector<int>& list)
{
    for (int i{1};i < sorting_array.size();i++) {
        int flag{ 0 };
        for (int j{};j < sorting_array.size() - i;j++) {
            if (list[j] > list[j + 1]) {
                auto temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
                flag ++;
            }
        }
        draw();
        if (flag == 0) { break; }
        
    }
        
}

void Game::mergesort(std::vector<int>& list)
{
}

void Game::quicksort(std::vector<int>& list,int lower, int upper)
{
    auto partition = [&](std::vector<int>& list, int lower, int upper)
    {
        auto pivot = list[lower];
        auto leftwall = lower;
        for (int i{ lower + 1 }; i <= upper;i++) {
            if (list[i] < pivot) {
                auto temp = list[leftwall];
                list[leftwall] = list[i];
                list[i] = temp;
                leftwall++;
                draw();
            };
            draw();
            
        }
        auto temp = list[leftwall];
        list[leftwall] = pivot;
        draw();
        pivot = temp;
        return leftwall;
    };

    if (lower < upper) {
        auto pivot = partition(list, lower, upper);
        quicksort(list, lower, pivot);
        draw();
        quicksort(list, pivot+1, upper);
        draw();
    }
    

}

void Game::selectionsort(std::vector<int>& list)
{
    for (int i{ 0 };i < list.size();i++) {
        auto smallest = list[i];
        auto smallest_index = i;
        for (int j{ i+1 };j < list.size();j++) {
            if (list[j] < smallest) {smallest = list[j]; smallest_index = j;}
        }
        auto temp = list[i];
        list[i] = smallest;
        list[smallest_index] = temp;
        draw();
    }
    
}

void Game::insertionsort(std::vector<int>& list)
{
}
