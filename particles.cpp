#include "particles.hpp"

Particles::Particles(){
  count = 1024;
  size = 8;

  window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode(1280,720),
    "Moon Orbiting Earth",
    sf::Style::Titlebar | sf::Style::Close
  );
  window->setFramerateLimit(60);
  window->setPosition(sf::Vector2i(10,40));
  reset_particles();

  angle = frame1 = frame2 = {0.f};
  x = std::sin(angle * pi / 180);
  y = std::cos(angle * pi / 180);

  moon.setRadius(radius / 3);
  moon.setPosition(
    (float)window->getSize().x / 2 + radius * 2,
    (float)window->getSize().y / 2 - radius * 2
  );

  earth.setRadius(radius);
  earth.setPosition(
    (float)window->getSize().x / 2 - radius,
    (float)window->getSize().y / 2 - radius
  );

  t1.loadFromFile("./assets/img/moon.png");
  t2.loadFromFile("./assets/img/earth.png");

  moon.setTexture(&t1);
  moon.setTextureRect(sf::IntRect(0,0,400,380));

  earth.setTexture(&t2);
  earth.setTextureRect(sf::IntRect(0,0,300,300));

  t3.loadFromFile("./assets/img/bg.jpg");
  bg.setTexture(t3);
}

void Particles::reset_particles(){
  m_particles = std::vector<Particle>(count);
  vertices = sf::VertexArray(sf::Quads, count * 4);

  for (std::size_t i{}; i < m_particles.size(); ++i){
   reset_particle(i, true); 
  }
}

void Particles::reset_particle(std::size_t index, bool start = false){
  float x = static_cast<float>(window->getSize().x) / 2;
  float y = static_cast<float>(window->getSize().y) / 2;

  vertices[4 * index + 0].position = sf::Vector2f(x,y);
  vertices[4 * index + 1].position = sf::Vector2f(x + size,y);
  vertices[4 * index + 2].position = sf::Vector2f(x + size, y + size);
  vertices[4 * index + 3].position = sf::Vector2f(x,y + size);

  sf::Color color;
  color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
  if(start){
    color.a = 0;
  }

  for (std::size_t i{}; i < 4; ++i){
    vertices[4 * index + i].color = color;
  }

  sf::Vector2f pos = {
    static_cast<float>(rand()) / (float)RAND_MAX * 14 - 7,
    static_cast<float>(rand()) / (float)RAND_MAX * 14 - 7
  };

  m_particles[index].velocity = pos;
  m_particles[index].lifetime = 30 + rand() % 60;
  
}

void Particles::update(){
  for (std::size_t i{}; i < m_particles.size(); ++i){
    if( m_particles[i].lifetime == 0 ){
      reset_particle(i);
    }
    vertices[4 * i + 0].position += m_particles[i].velocity;
    vertices[4 * i + 1].position += m_particles[i].velocity;
    vertices[4 * i + 2].position += m_particles[i].velocity;
    vertices[4 * i + 3].position += m_particles[i].velocity;   
    --m_particles[i].lifetime;
  }
}

void Particles::run(){
  while(window->isOpen()){
    sf::Event e;
    while(window->pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window->close();
      }
    }

    orbiting();
    update();

    window->clear(sf::Color::Black);
    window->draw(bg);
    window->draw(vertices);
    window->draw(earth);
    window->draw(moon);
    window->display();
  }
}

void Particles::orbiting(){
  angle += 2;
  x = std::sin(angle * pi / 180);
  y = std::cos(angle * pi / 180);

  moon.setPosition(
    (float)window->getSize().x / 2 - radius / 3 + x * radius * 3,
    (float)window->getSize().y / 2 - radius / 3 + y * radius * 3
  );


  frame1 += 0.1f;
  if( frame1 > 4 ){
    frame1 -= 4;
  }
  moon.setTextureRect(sf::IntRect(400 * (int)frame1, 0, 400, 300));

  frame2 += 0.3f;
  if( frame2 > 36 ){
    frame2 -= 36;
  }
  earth.setTextureRect(sf::IntRect(300 * (int)frame2, 0, 300, 300));

}
