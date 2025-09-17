#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

/**
 * @class Boid
 * @brief Represents a boid object with position, velocity, and color.
 */
class Boid
{
public:
	/**
	 * @brief Constructs a Boid object with the given position, velocity, and color.
	 * @param pos The position of the boid.
	 * @param vel The velocity of the boid.
	 * @param color The color of the boid.
	 */
	Boid(sf::Vector2f pos, sf::Vector2f vel, sf::Color color);

	/**
	 * @brief Draws the boid on the given window with the specified size.
	 * @param size The size of the boid.
	 * @param window The render window to draw the boid on.
	 */
	void draw(int size, sf::RenderWindow &window);

	sf::Vector2f pos; ///< The position of the boid.
	sf::Vector2f vel; ///< The velocity of the boid.
	sf::Color color;  ///< The color of the boid.
};

#endif