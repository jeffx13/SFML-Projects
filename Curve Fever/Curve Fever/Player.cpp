#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Terrain.h"


void Player::Input() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Direction.rotate(-1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Direction.rotate(1);
    }
    head.move(sf::Vector2f(Direction.x, Direction.y));
    //std::cout << Direction << std::endl;
}

void Player::Draw(sf::RenderWindow& Win){
    Win.draw(head);
    Win.draw(VA);
}

void Player::Update(sf::RenderWindow& Win, std::vector<Vector2D>& OccupiedCoordinates)
{
    HeadCentre = Vector2D(head.getGlobalBounds().left + head.getRadius(), head.getGlobalBounds().top + head.getRadius());
    AddPointToLine();
    Collisions(OccupiedCoordinates);
    Input();
    Draw(Win);
}

void Player::Collisions(std::vector<Vector2D>& OccupiedCoordinates) {
    for (auto& OccupiedCoordinate : OccupiedCoordinates) {
        if (HeadCentre.GetDistance(OccupiedCoordinate) < radius + OccupiedCoordinate.radius) {
            std::cout << "died";
        }
        //std::cout << OccupiedCoordinates.size() <<std::endl;
    }
    OccupiedCoordinates.push_back(Vector2D{ HeadCentre.x, HeadCentre.y, radius });
    

    
    
}

void Player::CalcFront()
{
    front.clear();
    
    Vector2D normal = Direction.GetNormalised()* head.getRadius();
    normal.rotate(90);
    for (int i{ 0 };i <= 180;i++) {
        front.push_back(HeadCentre + normal);
        normal.rotate(i);
    }


}

void Player::AddPointToLine()
{
    Vector2D LastVertex = { VA[VA.getVertexCount() - 1].position.x,VA[VA.getVertexCount() - 1].position.y };
    Vector2D VectorToHead = LastVertex.FindVector(HeadCentre);
    Vector2D Clockwise = VectorToHead.PerpendicularClockwise().GetNormalised() * head.getRadius();
    Vector2D AntiClockwise = VectorToHead.PerpendicularAntiClockwise().GetNormalised() * head.getRadius();
    if (VertexNumber % 2 == 0) {
        Vector2D ClockwisePoint = HeadCentre + Clockwise;
        VA.append(sf::Vector2f(ClockwisePoint.x, ClockwisePoint.y));
    }
    else {
        Vector2D AntiClockwisePoint = HeadCentre + AntiClockwise;
        VA.append(sf::Vector2f(AntiClockwisePoint.x, AntiClockwisePoint.y));
    }
    VertexNumber++;
    

}




