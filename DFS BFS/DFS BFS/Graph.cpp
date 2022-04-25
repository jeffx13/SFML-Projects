#include "Graph.h"

void Graph::dfs()
{
    if (q.back() == start) {
        maze[q.back()] |= CELL_VISITED;
        visited_count++;
    }
    auto neighbours = get_neighbours(q.back());
    
    if (neighbours.empty()) {
        q.pop_back();
        maze[q.back()] |= CELL_VISITED_TWICE;
    }
    else {
        int random_neighbour = intdist(mt) % neighbours.size();
        if (neighbours[random_neighbour] == q.back() - cols) {
            maze[q.back()] |= CELL_NORTH_PATH;
            maze[neighbours[random_neighbour]] |= CELL_VISITED | CELL_SOUTH_PATH;
            q.push_back(neighbours[random_neighbour]);
        }
        if (neighbours[random_neighbour] == q.back() + cols) {
            maze[q.back()] |= CELL_SOUTH_PATH;
            maze[neighbours[random_neighbour]] |= CELL_VISITED | CELL_NORTH_PATH;
            q.push_back(neighbours[random_neighbour]);
        }
        if (neighbours[random_neighbour] == q.back() - 1) {
            maze[q.back()] |= CELL_WEST_PATH;
            maze[neighbours[random_neighbour]] |= CELL_VISITED | CELL_EAST_PATH;
            q.push_back(neighbours[random_neighbour]);
        }
        if (neighbours[random_neighbour] == q.back() + 1) {
            maze[q.back()] |= CELL_EAST_PATH ;
            maze[neighbours[random_neighbour]] |= CELL_VISITED | CELL_WEST_PATH;
            q.push_back(neighbours[random_neighbour]);
        }
        visited_count++;
    }
    
}

void Graph::bfs()
{
    
    if ((maze[q.front()] & CELL_VISITED) == 0) //Not Visited
    {
        maze[q.front()] |= CELL_VISITED;
        visited_count++;
        auto neighbours = get_neighbours(q.front());
        if (!(neighbours.empty())) {
            for (auto neighbour : neighbours) {
                q.push_back(neighbour);
            }
        }
    }
    q.pop_front();
    
}

void Graph::reset()
{
    std::fill(maze.begin(), maze.end(), 0);
    visited_count = 0;
    q.clear();
    start = intdist(mt) % (rows * cols);
    q.push_back(start);
    setted_start = false;
    setted_end = false;
    pathfinding_start = 0;
    pathfinding_end = 0;
    path.clear();
}

void Graph::A_Star()
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<std::pair<int, int>>> priority_q;
    std::map<int, int> gn{};
    for (int i{};i < rows * cols;i++) { gn[i] = 9999; };
    std::map<int, int> fn{};
    for (int i{};i < rows * cols;i++) { fn[i] = 9999; };
    std::map<int, int> came_from{};
    std::set<int> closed;
    
    auto get_hn = [&](const int cell_index) {
        return int((pathfinding_end - cell_index) / cols) + int((pathfinding_end - cell_index) % cols);
    };
    auto get_neighbours = [&](int cell_index) {
        std::vector<int>neighbours;
        neighbours.reserve(4);
        if (((maze[cell_index] & CELL_NORTH_PATH) == CELL_NORTH_PATH) && !closed.contains(cell_index - cols)) { neighbours.push_back(cell_index - cols); }
        if (((maze[cell_index] & CELL_SOUTH_PATH) == CELL_SOUTH_PATH) && !closed.contains(cell_index + cols)) { neighbours.push_back(cell_index + cols); }
        if (((maze[cell_index] & CELL_WEST_PATH) == CELL_WEST_PATH) && !closed.contains(cell_index - 1)) { neighbours.push_back(cell_index - 1); }
        if (((maze[cell_index] & CELL_EAST_PATH) == CELL_EAST_PATH) && !closed.contains(cell_index + 1)) { neighbours.push_back(cell_index + 1); }
        neighbours.shrink_to_fit();
        return neighbours;
    };
    
    std::cout << "start: " << pathfinding_start << std::endl;
    std::cout << "end: " << pathfinding_end << std::endl;

    fn[pathfinding_start] = get_hn(pathfinding_start);
    gn[pathfinding_start] = 0;
    came_from[pathfinding_start] = pathfinding_start;
    priority_q.push(std::make_pair(fn[pathfinding_start], pathfinding_start));
    closed.insert(pathfinding_start);

    while (!(priority_q.empty())) {
        auto current = priority_q.top();
        if (current.second == pathfinding_end) { std::cout <<current.second << " found" <<std::endl; break; }
        auto cost_so_far = gn[current.second];
        auto neigbours = get_neighbours(current.second);
        priority_q.pop();
        for (auto neighbour : neigbours) {
            if (cost_so_far + 1 < gn[neighbour]) {
                gn[neighbour] = cost_so_far + 1;
                fn[neighbour] = gn[neighbour] + get_hn(neighbour);
                came_from[neighbour] = current.second;
                
                if (!(closed.contains(neighbour))) {
                    priority_q.push(std::make_pair(fn[neighbour], neighbour));
                    closed.insert(neighbour);
                }
            }
        }
    }
    auto construct_path = [&]() {
        int current = came_from[pathfinding_end];
        //maze[current] |= PATH;
        path.push_back(current);
        while (came_from[current] != pathfinding_start) {
            current = came_from[current];
            path.insert(path.begin(),current);
            //maze[current] |= PATH;
        }
    };
    construct_path();
    
}

std::vector<unsigned short int> Graph::get_neighbours(const unsigned short int cell_index)
{
    std::vector<unsigned short int> neighbours;
    neighbours.reserve(4);
    if (cell_index >= cols) {
        unsigned short int north = cell_index-cols;
        if ((maze[north]&CELL_VISITED) == 0) {
            neighbours.push_back(north);
        }
    }
    if (cell_index <= cols * rows-1 - cols) {
        unsigned short int south = cell_index + cols;
        if ((maze[south] & CELL_VISITED) == 0) {
            neighbours.push_back(south);
        }
    }
    if ((cell_index % cols)!= 0) {
        unsigned short int west = cell_index -1;
        if ((maze[west] & CELL_VISITED) == 0) {
            neighbours.push_back(west);
        }
    }
    if ((cell_index % cols) != cols-1) {
        unsigned short int east = cell_index + 1;
        if ((maze[east] & CELL_VISITED) == 0)
        {
            neighbours.push_back(east);
        }
    }
    neighbours.shrink_to_fit();
    return neighbours;
}

void Graph::print_maze()
{

    for (int i{};i < rows;++i) {
        for (int j=i*cols;j < (i+1) * cols;++j) {

            if ((maze[j] & CELL_VISITED) == CELL_VISITED) {
                std::cout << " " << 1 << " ";
            }
            else
            {
                std::cout << " " << 0 << " ";
            }

            
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
