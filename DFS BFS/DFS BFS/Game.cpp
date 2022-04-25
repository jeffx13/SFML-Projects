#include "Game.h"
#include <SFML/Graphics.hpp>

void Game::init() {

	window.create(sf::VideoMode(win_width, win_height), "DFS, BFS, A*");
	window.setFramerateLimit(60);
    window.clear(sf::Color::White);
    draw();
    window.display();
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
    }
}

void Game::draw()
{
    auto vertical_wall = sf::RectangleShape { sf::Vector2f(cell_wall_thickness,cell_size) };
    vertical_wall.setFillColor(sf::Color::Black);
    auto horizontal_wall = sf::RectangleShape{ sf::Vector2f(cell_size,cell_wall_thickness) };
    horizontal_wall.setFillColor(sf::Color::Black);

    for (int i{};i < maze.rows;++i) {
        for (int j = i * maze.cols;j < (i + 1) * maze.cols;++j) {
            auto cell{ sf::RectangleShape(sf::Vector2f(cell_size, cell_size)) };
            cell.setPosition((j % maze.cols) * cell_size, i * cell_size);
            if (maze.visited_count == maze.cols * maze.rows) { 
                
                if ((maze.maze[j] & maze.START_CELL) == maze.START_CELL) { cell.setFillColor(sf::Color::Green); }
                else if ((maze.maze[j] & maze.END_CELL) == maze.END_CELL) { cell.setFillColor(sf::Color::Red); }
                else if ((maze.maze[j] & maze.PATH) == maze.PATH) { cell.setFillColor(sf::Color::Magenta); }
            }
            else {
                
                if ((maze.maze[j] & maze.CELL_VISITED_TWICE) == maze.CELL_VISITED_TWICE) { cell.setFillColor(sf::Color::Green); }
                else if ((maze.maze[j] & maze.CELL_VISITED) == maze.CELL_VISITED) { cell.setFillColor(sf::Color::Yellow); }
                else { cell.setFillColor(sf::Color::Red); }
            }
            window.draw(cell);
            

            if ((maze.maze[j] & maze.CELL_EAST_PATH) != maze.CELL_EAST_PATH)
            {
                vertical_wall.setPosition((j % maze.cols) * cell_size + cell_size - cell_wall_thickness, i * cell_size);
                window.draw(vertical_wall);
            }
            if ((maze.maze[j] & maze.CELL_SOUTH_PATH) != maze.CELL_SOUTH_PATH)
            {
                horizontal_wall.setPosition((j % maze.cols) * cell_size, i * cell_size + cell_size - cell_wall_thickness);
                window.draw(horizontal_wall);
            }
        }
    }
}

void Game::mouse() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        std::cout << "cell: " << (floor(sf::Mouse::getPosition(window).y / cell_size) * maze.cols) + (sf::Mouse::getPosition(window).x / cell_size) << std::endl;
        if (maze.visited_count == maze.rows * maze.cols) {
            if (!maze.setted_start) {
                maze.maze[(floor(sf::Mouse::getPosition(window).y / cell_size) * maze.cols) + (sf::Mouse::getPosition(window).x / cell_size)] |= maze.START_CELL;
                maze.set_start(floor(sf::Mouse::getPosition(window).y / cell_size), (sf::Mouse::getPosition(window).x / cell_size));
                window.clear(sf::Color::White);
                draw();
                window.display();
            }
            if (!maze.setted_end && maze.setted_start) {
                if (!((maze.maze[(floor(sf::Mouse::getPosition(window).y / cell_size) * maze.cols) + (sf::Mouse::getPosition(window).x / cell_size)] & maze.START_CELL) == maze.START_CELL)) {
                    maze.maze[(floor(sf::Mouse::getPosition(window).y / cell_size) * maze.cols) + (sf::Mouse::getPosition(window).x / cell_size)] |= maze.END_CELL;
                    maze.set_end(floor(sf::Mouse::getPosition(window).y / cell_size), (sf::Mouse::getPosition(window).x / cell_size));
                    window.clear(sf::Color::White);
                    draw();
                    window.display();
                }
            }
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        //maze.maze[(floor(sf::Mouse::getPosition(window).y / cell_size) * maze.cols) + (sf::Mouse::getPosition(window).x / cell_size)] &= maze.CELL_NORTH_PATH
    }

}

void Game::keyboard() {
    auto draw_lambda = [&]() {};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window.close();}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        maze.A_Star();
        
        for (auto cell : maze.path) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { break; window.close(); }
            maze.maze[cell] |= maze.PATH;
            window.clear(sf::Color::White);
            draw();
            window.display();

        }
        
    }
    if (maze.visited_count < maze.rows* maze.cols){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
        {
        maze.dfs();
        window.clear(sf::Color::White);
        draw();
        window.display();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {
            maze.bfs();
            window.clear(sf::Color::White);
            draw();
            window.display();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            do {
                maze.dfs();
                window.clear(sf::Color::White);
                draw();
                window.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { break; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { break; window.close(); }
            } while (maze.visited_count < maze.rows * maze.cols);
            maze.q.clear();
            for (auto& cell : maze.maze) {
                cell &= (~(1 << (5 - 1)));
                cell &= (~(1 << (6 - 1)));
            }
            window.clear(sf::Color::White);
            draw();
            window.display();
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            do {
                maze.bfs();
                window.clear(sf::Color::White);
                draw();
                window.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { break; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { break; window.close(); }
            } while (maze.visited_count < maze.rows * maze.cols);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        maze.reset();
        do {
            maze.dfs();
        } while (maze.visited_count < maze.rows * maze.cols);
        maze.q.clear();
        for (auto& cell : maze.maze) {
            cell &= (~(1 << (5 - 1)));
            cell &= (~(1 << (6 - 1)));
        }
        window.clear(sf::Color::White);
        draw();
        window.display();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        maze.reset();
        window.clear(sf::Color::White);
        draw();
        window.display();
    }
}

