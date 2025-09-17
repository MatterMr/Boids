#include "Flock.h"
#include <iostream>

Flock::Flock(int BOID_SIZE, int V_RANGE, int P_RANGE, int MIN_SPEED,
             int MAX_SPEED, float W, float S, float A, float C,
             sf::Vector2i WINDOW_SIZE)
    : BOID_SIZE(BOID_SIZE), V_RANGE(V_RANGE), P_RANGE(P_RANGE),
      MIN_SPEED(MIN_SPEED), MAX_SPEED(MAX_SPEED), WALL_AVOIDANCE_STRENGTH(W),
      SEPARATION_STRENGTH(S), ALIGNMENT_STRENGTH(A), COHESION_STRENGTH(C),
      WINDOW_SIZE(WINDOW_SIZE) {}

Flock::~Flock() {
    for (size_t i = 0; i < boids.size(); i++) {
        delete boids.at(i);
    }
}

void Flock::update() {
    for (size_t i = 0; i < boids.size(); i++) {
        Boid* boid = boids.at(i);
        std::vector<Boid*>* boidsInVisualRange = new std::vector<Boid*>();
        std::vector<Boid*>* boidsInProtectedRange = new std::vector<Boid*>();
        findBoidsInRange(boid, boidsInVisualRange, boidsInProtectedRange);

        boid->vel += separation(boid, boidsInProtectedRange) +
                     alignment(boid, boidsInVisualRange) +
                     cohesion(boid, boidsInVisualRange) + wallCollision(boid);

        speedLimit(boid);
    }
    for (size_t i = 0; i < boids.size(); i++) {
        boids.at(i)->pos += boids.at(i)->vel;
    }
}
void Flock::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < boids.size(); i++) {
        boids.at(i)->draw(BOID_SIZE, window);
    }
}

void Flock::addBoid(sf::Vector2f pos, sf::Color color) {
    addBoid(pos, sf::Vector2f(0, 0), color);
}

void Flock::addBoid(sf::Vector2f pos, sf::Vector2f vel, sf::Color color) {
    boids.push_back(new Boid(pos, vel, color));
}

void Flock::clear() {
    for (size_t i = 0; i < boids.size(); i++) {
        delete boids.at(i);
    }
    boids.clear();
}

sf::Vector2f Flock::separation(Boid* b,
                               std::vector<Boid*>* boidsInProtectedRange) {
    sf::Vector2f delta_v(0, 0);
    for (size_t i = 0; i < boidsInProtectedRange->size(); i++) {
        delta_v += b->pos - boidsInProtectedRange->at(i)->pos;
    }
    return delta_v * SEPARATION_STRENGTH;
}

sf::Vector2f Flock::alignment(Boid* b, std::vector<Boid*>* boidsInVisualRange) {
    sf::Vector2f delta_v(0, 0);
    if (boidsInVisualRange->size() > 0) {
        sf::Vector2f average_v(0, 0);
        for (size_t i = 0; i < boidsInVisualRange->size(); i++) {
            average_v += boidsInVisualRange->at(i)->vel;
        }
        average_v.x /= boidsInVisualRange->size();
        average_v.y /= boidsInVisualRange->size();

        delta_v.x = (average_v.x - b->vel.x) * ALIGNMENT_STRENGTH;
        delta_v.y = (average_v.y - b->vel.y) * ALIGNMENT_STRENGTH;
    }
    return delta_v;
}

sf::Vector2f Flock::cohesion(Boid* b, std::vector<Boid*>* boidsInVisualRange) {
    sf::Vector2f delta_v(0, 0);
    if (boidsInVisualRange->size() > 0) {
        sf::Vector2f average_p(0, 0);
        for (size_t i = 0; i < boidsInVisualRange->size(); i++) {
            average_p += boidsInVisualRange->at(i)->pos;
        }
        average_p.x /= boidsInVisualRange->size();
        average_p.y /= boidsInVisualRange->size();

        delta_v.x = (average_p.x - b->pos.x) * COHESION_STRENGTH;
        delta_v.y = (average_p.y - b->pos.y) * COHESION_STRENGTH;
    }
    return delta_v;
}

sf::Vector2f Flock::wallCollision(Boid* b) {
    int wallRange = BOID_SIZE * 10;
    sf::Vector2f delta_v(0, 0);
    bool outOfBounds =
        b->pos.x >= WINDOW_SIZE.x - BOID_SIZE || b->pos.x <= BOID_SIZE ||
        b->pos.y >= WINDOW_SIZE.y - BOID_SIZE || b->pos.y <= BOID_SIZE;

    float turnFactor = outOfBounds ? 5 : WALL_AVOIDANCE_STRENGTH;

    if (b->pos.x > WINDOW_SIZE.x - wallRange) {
        delta_v.x = -turnFactor;
    }
    if (b->pos.x < wallRange) {
        delta_v.x = turnFactor;
    }
    if (b->pos.y > WINDOW_SIZE.y - wallRange) {
        delta_v.y = -turnFactor;
    }
    if (b->pos.y < wallRange) {
        delta_v.y = turnFactor;
    }
    return delta_v;
}

void Flock::speedLimit(Boid* b) {
    float vel_mag = sqrt(pow(b->vel.x, 2) + pow(b->vel.y, 2));
    if (vel_mag < MIN_SPEED) {
        b->vel *= MIN_SPEED / vel_mag;
    } else if (vel_mag > MAX_SPEED) {
        b->vel *= MAX_SPEED / vel_mag;
    }
}

void Flock::loadFromFile(std::ifstream& file) {
    if (file.fail()) {
        std::cerr << "Error opening input file" << std::endl;
    } else {
        sf::Vector2f pos, vel;
        while (!file.eof()) {
            file >> pos.x >> pos.y >> vel.x >> vel.y;
            this->addBoid(pos, vel, sf::Color::Cyan);
        }
        file.close();
        std::cout << "File loaded" << std::endl;
    }
}
void Flock::writeToFile(std::ofstream& file) {
    if (file.fail()) {
        std::cerr << "Error opening output file" << std::endl;
    } else {
        for (size_t i = 0; i < boids.size(); i++) {
            Boid* b = boids.at(i);
            file << b->pos.x << " " << b->pos.y << " " << b->vel.x << " "
                 << b->vel.y << std::endl;
        }
        file.close();
        std::cout << "File Saved ;)" << std::endl;
    }
}

void Flock::findBoidsInRange(Boid* b, std::vector<Boid*>* boidsInVisualRange,
                             std::vector<Boid*>* boidsInProtectedRange) {
    for (size_t h = 0; h < boids.size(); h++) {
        Boid* other = boids.at(h);
        if (other->pos != b->pos) {
            float dis = sqrt(pow(other->pos.x - b->pos.x, 2) +
                             pow(other->pos.y - b->pos.y, 2));

            if (dis <= P_RANGE) {
                boidsInProtectedRange->push_back(other);
            } else if (dis <= V_RANGE) {
                boidsInVisualRange->push_back(other);
            }
        }
    }
}
