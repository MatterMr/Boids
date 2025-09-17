/* CSCI 200: FINAL | BOIDS Flocking Simulation
 * Author: Matthew Ryan
 */
#include "Flock.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Flock Configuration Variables (Used for customizing the boid movement biases)
const int BOID_SIZE = 10;
const int V_RANGE = 50;
const int P_RANGE = 20;
const int MAX_SPEED = 10;
const int MIN_SPEED = 4;
const float WALL_AVOIDANCE_STRENGTH = 0.4;
const float SEPERATION_STRENGTH = 0.01;
const float ALIGNMENT_STRENGTH = 0.05;
const float COHESION_STRENGTH = 0.001;
const sf::Vector2i WINDOW_SIZE(1000, 1000);

// Quick Function definition to encapsulate the boid placement inputs
void controls(Flock* flock, RenderWindow& window);

int main() {
    // Defining the render window
    RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "SFML Test");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Event event;
    bool pauseToggle = false;

    // Defining the Flock
    Flock* flock =
        new Flock(BOID_SIZE, V_RANGE, P_RANGE, MIN_SPEED, MAX_SPEED,
                  WALL_AVOIDANCE_STRENGTH, SEPERATION_STRENGTH,
                  ALIGNMENT_STRENGTH, COHESION_STRENGTH, WINDOW_SIZE);

    // Input Stream
    ifstream file("theBoids");
    flock->loadFromFile(file);

    cout << "Instructions:" << endl
         << "\t- Arrow Keys Place Boids at Mouse Position" << endl
         << "\t- \"p\" Pauses\\Unpauses the simulation" << endl
         << "\t- \"x\" saves the boids positions for next runtime and closes"
         << endl
         << "\t- Backspace removes all the boids from the flock" << endl;

    while (window.isOpen()) {
        window.clear();
        if (pauseToggle) {
            flock->update();
        }
        flock->draw(window);

        window.display();

        while (window.pollEvent(event)) {
            controls(flock, window);

            if (event.type == Event::Closed) {
                window.close();
            }
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::X)) {
                ofstream file("theBoids");
                flock->writeToFile(file);
                window.close();
            }
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::P)) {
                pauseToggle = !pauseToggle;
            }
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::BackSpace)) {
                flock->clear();
            }
        }
    }

    return 0;
}

/**
 * Controls the behavior of the flock based on keyboard input.
 *
 * @param flock   Pointer to the Flock object.
 * @param window  Reference to the RenderWindow object.
 */
void controls(Flock* flock, RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        flock->addBoid(sf::Vector2f(localPosition.x, localPosition.y),
                       sf::Vector2f(10, 0), sf::Color::Cyan);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        flock->addBoid(sf::Vector2f(localPosition.x, localPosition.y),
                       sf::Vector2f(-10, 0), sf::Color::Cyan);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        flock->addBoid(sf::Vector2f(localPosition.x, localPosition.y),
                       sf::Vector2f(0, 10), sf::Color::Cyan);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        flock->addBoid(sf::Vector2f(localPosition.x, localPosition.y),
                       sf::Vector2f(0, -10), sf::Color::Cyan);
    }
}
