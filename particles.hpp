#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

class Particles {
  public:
    struct Particle {
      sf::Vector2f velocity;
      int lifetime;
    };

    std::shared_ptr<sf::RenderWindow> window;
    std::vector<Particle> m_particles;
    sf::VertexArray vertices;
    float size;
    std::size_t count;

    const double pi {3.14f}, radius {70.f};
    double angle, x, y, frame1, frame2;
    sf::CircleShape earth, moon;
    sf::Texture t1, t2, t3;
    sf::Sprite bg;

    void reset_particles();
    void reset_particle(std::size_t, bool);
    void update();
    void orbiting();

    Particles();
    void run();
};
