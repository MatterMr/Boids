#include "Boid.h"

Boid::Boid(sf::Vector2f pos, sf::Vector2f vel, sf::Color color)
{
	this->pos = pos;
	this->vel = vel;
	this->color = color;
}

void Boid::draw(int size, sf::RenderWindow &window)
{
	float rotation = atan2(vel.y, vel.x) * 180 / M_PI;
	sf::ConvexShape boidShape(4);
	boidShape.setPosition(pos);
	boidShape.setPoint(0, sf::Vector2f(size / 2.0, 0));
	boidShape.setPoint(1, sf::Vector2f(-size / 2.0, -size / 3.0));
	boidShape.setPoint(2, sf::Vector2f(-size / 3.0, 0));
	boidShape.setPoint(3, sf::Vector2f(-size / 2.0, size / 3.0));
	boidShape.setFillColor(color);
	boidShape.setRotation(rotation);

	window.draw(boidShape);
}
