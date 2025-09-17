#ifndef FLOCK_H
#define FLOCK_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Boid.h"
#include <fstream>
#include <iostream>

/**
 * @class Flock
 * @brief Represents a flock of boids in a simulation.
 *
 * The Flock class manages a collection of boids and provides functionality for updating and drawing them.
 * It also includes methods for adding, clearing, and loading/saving boids from/to a file.
 */
class Flock
{
public:
	/**
	 * @brief Constructs a Flock object with the specified parameters.
	 *
	 * @param BOID_SIZE The size of each boid.
	 * @param V_RANGE The visual range of each boid.
	 * @param P_RANGE The protected range of each boid.
	 * @param MIN_SPEED The minimum speed of each boid.
	 * @param MAX_SPEED The maximum speed of each boid.
	 * @param W The wall avoidance strength.
	 * @param S The separation strength.
	 * @param A The alignment strength.
	 * @param C The cohesion strength.
	 * @param WINDOW_SIZE The size of the simulation window.
	 */
	Flock(int BOID_SIZE, int V_RANGE, int P_RANGE, int MIN_SPEED, int MAX_SPEED, float W, float S, float A, float C, sf::Vector2i WINDOW_SIZE);

	/**
	 * @brief Destructor for the Flock object.
	 */
	~Flock();

	/**
	 * @brief Updates the flock by applying the flocking rules to each boid.
	 */
	void update();

	/**
	 * @brief Draws the flock on the specified window.
	 *
	 * @param window The render window to draw the flock on.
	 */
	void draw(sf::RenderWindow &window);

	/**
	 * @brief Adds a new boid to the flock with the specified position and color.
	 *
	 * @param pos The position of the new boid.
	 * @param color The color of the new boid.
	 */
	void addBoid(sf::Vector2f pos, sf::Color color);

	/**
	 * @brief Adds a new boid to the flock with the specified position, velocity, and color.
	 *
	 * @param pos The position of the new boid.
	 * @param vel The velocity of the new boid.
	 * @param color The color of the new boid.
	 */
	void addBoid(sf::Vector2f pos, sf::Vector2f vel, sf::Color color);

	/**
	 * @brief Clears the flock, removing all boids.
	 */
	void clear();

	/**
	 * @brief Loads the flock from the specified file.
	 *
	 * @param file The input file stream to read the flock data from.
	 */
	void loadFromFile(std::ifstream &file);

	/**
	 * @brief Writes the flock to the specified file.
	 *
	 * @param file The output file stream to write the flock data to.
	 */
	void writeToFile(std::ofstream &file);

private:
	// Private Member Data
	std::vector<Boid *> boids;			 /**< The collection of boids in the flock. */
	const int BOID_SIZE;				 /**< The size of each boid. */
	const int V_RANGE;					 /**< The visual range of each boid. */
	const int P_RANGE;					 /**< The protected range of each boid. */
	const int MIN_SPEED;				 /**< The minimum speed of each boid. */
	const int MAX_SPEED;				 /**< The maximum speed of each boid. */
	const float WALL_AVOIDANCE_STRENGTH; /**< The wall avoidance strength. */
	const float SEPARATION_STRENGTH;	 /**< The separation strength. */
	const float ALIGNMENT_STRENGTH;		 /**< The alignment strength. */
	const float COHESION_STRENGTH;		 /**< The cohesion strength. */
	const sf::Vector2i WINDOW_SIZE;		 /**< The size of the simulation window. */

	// Private Functionality
	/**
	 * @brief Finds the boids within the visual and protected range of a given boid.
	 *
	 * @param b The boid for which to find the boids within range.
	 * @param boidsInVisualRange A pointer to a vector to store the boids within visual range.
	 * @param boidsInProtectedRange A pointer to a vector to store the boids within protected range.
	 */
	void findBoidsInRange(Boid *b, std::vector<Boid *> *boidsInVisualRange, std::vector<Boid *> *boidsInProtectedRange);

	/**
	 * @brief Calculates the separation vector for a given boid based on the boids within its protected range.
	 *
	 * @param b The boid for which to calculate the separation vector.
	 * @param boidsInProtectedRange A pointer to a vector containing the boids within the protected range.
	 * @return The separation vector for the given boid.
	 */
	sf::Vector2f separation(Boid *b, std::vector<Boid *> *boidsInProtectedRange);

	/**
	 * @brief Calculates the alignment vector for a given boid based on the boids within its visual range.
	 *
	 * @param b The boid for which to calculate the alignment vector.
	 * @param boidsInVisualRange A pointer to a vector containing the boids within the visual range.
	 * @return The alignment vector for the given boid.
	 */
	sf::Vector2f alignment(Boid *b, std::vector<Boid *> *boidsInVisualRange);

	/**
	 * @brief Calculates the cohesion vector for a given boid based on the boids within its visual range.
	 *
	 * @param b The boid for which to calculate the cohesion vector.
	 * @param boidsInVisualRange A pointer to a vector containing the boids within the visual range.
	 * @return The cohesion vector for the given boid.
	 */
	sf::Vector2f cohesion(Boid *b, std::vector<Boid *> *boidsInVisualRange);

	/**
	 * @brief Calculates the collision avoidance vector for a given boid based on its proximity to walls.
	 *
	 * @param b The boid for which to calculate the collision avoidance vector.
	 * @return The collision avoidance vector for the given boid.
	 */
	sf::Vector2f wallCollision(Boid *b);

	/**
	 * @brief Limits the speed of a given boid to the specified minimum and maximum speeds.
	 *
	 * @param b The boid for which to limit the speed.
	 */
	void speedLimit(Boid *b);
};

#endif
