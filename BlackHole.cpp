#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const float PI = 3.14159265359f;

struct Vector2f {
    float x, y;
    
    Vector2f(float x = 0, float y = 0) : x(x), y(y) {}
    
    Vector2f operator+(const Vector2f& other) const {
        return Vector2f(x + other.x, y + other.y);
    }
    
    Vector2f operator-(const Vector2f& other) const {
        return Vector2f(x - other.x, y - other.y);
    }
    
    Vector2f operator*(float scalar) const {
        return Vector2f(x * scalar, y * scalar);
    }
    
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    
    Vector2f normalized() const {
        float mag = magnitude();
        if (mag > 0) return Vector2f(x / mag, y / mag);
        return Vector2f(0, 0);
    }
};

class BlackHole {
private:
    Vector2f position;
    float mass;
    float schwarzschildRadius;
    sf::CircleShape shape;
    sf::CircleShape eventHorizon;
    
public:
    BlackHole(Vector2f pos, float m) : position(pos), mass(m) {
        // Schwarzschild radius (simplified for visualization)
        schwarzschildRadius = mass * 0.01f;
        
        // Visual representation of the black hole
        shape.setRadius(schwarzschildRadius);
        shape.setFillColor(sf::Color::Black);
        shape.setOrigin(schwarzschildRadius, schwarzschildRadius);
        shape.setPosition(position.x, position.y);
        
        // Event horizon visualization
        eventHorizon.setRadius(schwarzschildRadius * 1.5f);
        eventHorizon.setFillColor(sf::Color::Transparent);
        eventHorizon.setOutlineColor(sf::Color(100, 100, 100, 100));
        eventHorizon.setOutlineThickness(2);
        eventHorizon.setOrigin(schwarzschildRadius * 1.5f, schwarzschildRadius * 1.5f);
        eventHorizon.setPosition(position.x, position.y);
    }
    
    Vector2f getPosition() const { return position; }
    float getMass() const { return mass; }
    float getSchwarzschildRadius() const { return schwarzschildRadius; }
    
    void draw(sf::RenderWindow& window) {
        window.draw(eventHorizon);
        window.draw(shape);
    }
};

class LightRay {
private:
    std::vector<Vector2f> path;
    Vector2f currentPosition;
    Vector2f currentVelocity;
    sf::Color color;
    float impactParameter;
    bool absorbed;
    
public:
    LightRay(Vector2f startPos, Vector2f initialVel, sf::Color c) 
        : currentPosition(startPos), currentVelocity(initialVel), color(c), absorbed(false) {
        path.push_back(startPos);
        // Impact parameter is the perpendicular distance from the trajectory to the black hole
        impactParameter = std::abs(startPos.y - WINDOW_HEIGHT / 2.0f);
    }
    
    void update(const BlackHole& blackHole, float deltaTime) {
        if (absorbed) return;
        
        Vector2f blackHolePos = blackHole.getPosition();
        Vector2f toBlackHole = blackHolePos - currentPosition;
        float distance = toBlackHole.magnitude();
        
        // Check if ray is absorbed by black hole
        if (distance < blackHole.getSchwarzschildRadius()) {
            absorbed = true;
            return;
        }
        
        // Gravitational acceleration using simplified general relativity
        // F = G*M/r^2, but for light we use deflection angle approximation
        float gravitationalConstant = blackHole.getMass() * 10000.0f;
        
        // Calculate gravitational acceleration
        Vector2f acceleration = toBlackHole.normalized() * (gravitationalConstant / (distance * distance));
        
        // Apply relativistic correction for light deflection
        // Deflection angle ≈ 4GM/(c²b) where b is impact parameter
        float deflectionFactor = 1.0f + (gravitationalConstant * 0.001f) / (distance * impactParameter + 1.0f);
        acceleration = acceleration * deflectionFactor;
        
        // Update velocity and position using Verlet integration
        currentVelocity = currentVelocity + acceleration * deltaTime;
        
        // Maintain approximately constant speed for light
        float lightSpeed = 200.0f;
        currentVelocity = currentVelocity.normalized() * lightSpeed;
        
        currentPosition = currentPosition + currentVelocity * deltaTime;
        
        // Add point to path for visualization
        if (path.size() == 0 || (currentPosition - path.back()).magnitude() > 2.0f) {
            path.push_back(currentPosition);
        }
    }
    
    void draw(sf::RenderWindow& window) const {
        if (path.size() < 2) return;
        
        // Draw the light ray path
        for (size_t i = 1; i < path.size(); i++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(path[i-1].x, path[i-1].y), color),
                sf::Vertex(sf::Vector2f(path[i].x, path[i].y), color)
            };
            window.draw(line, 2, sf::Lines);
        }
        
        // Draw current position as a small circle
        if (!absorbed && currentPosition.x >= 0 && currentPosition.x <= WINDOW_WIDTH) {
            sf::CircleShape photon(3);
            photon.setFillColor(color);
            photon.setOrigin(3, 3);
            photon.setPosition(currentPosition.x, currentPosition.y);
            window.draw(photon);
        }
    }
    
    bool isOffScreen() const {
        return (currentPosition.x > WINDOW_WIDTH + 100 || 
                currentPosition.x < -100 ||
                currentPosition.y > WINDOW_HEIGHT + 100 || 
                currentPosition.y < -100) && !absorbed;
    }
    
    bool isAbsorbed() const { return absorbed; }
};

class BlackHoleSimulation {
private:
    sf::RenderWindow window;
    BlackHole blackHole;
    std::vector<LightRay> lightRays;
    sf::Clock clock;
    sf::Font font;
    sf::Text infoText;
    float raySpawnTimer;
    int rayCount;
    
public:
    BlackHoleSimulation() 
        : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Black Hole - Gravitational Lensing"),
          blackHole(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 50.0f),
          raySpawnTimer(0), rayCount(0) {
        
        window.setFramerateLimit(60);
        
        // Setup info text
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            // If Arial not found, continue without text
            std::cout << "Font not loaded, text will not display\n";
        } else {
            infoText.setFont(font);
            infoText.setCharacterSize(20);
            infoText.setFillColor(sf::Color::White);
            infoText.setPosition(10, 10);
        }
    }
    
    void spawnLightRay() {
        // Spawn rays from the left side with varying heights
        float y = 50 + (rayCount % 15) * 50; // Spread rays vertically
        Vector2f startPos(-50, y);
        Vector2f velocity(200, 0); // Moving right
        
        // Vary colors for better visualization
        sf::Color colors[] = {
            sf::Color::Red, sf::Color::Green, sf::Color::Blue, 
            sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan, sf::Color::White
        };
        sf::Color rayColor = colors[rayCount % 7];
        
        lightRays.emplace_back(startPos, velocity, rayColor);
        rayCount++;
    }
    
    void update() {
        float deltaTime = clock.restart().asSeconds();
        
        // Spawn new light rays periodically
        raySpawnTimer += deltaTime;
        if (raySpawnTimer > 0.3f) { // Spawn every 0.3 seconds
            spawnLightRay();
            raySpawnTimer = 0;
        }
        
        // Update all light rays
        for (auto& ray : lightRays) {
            ray.update(blackHole, deltaTime);
        }
        
        // Remove rays that are off-screen
        lightRays.erase(
            std::remove_if(lightRays.begin(), lightRays.end(),
                [](const LightRay& ray) { return ray.isOffScreen(); }),
            lightRays.end()
        );
        
        // Update info text
        if (font.getInfo().family != "") {
            infoText.setString("Light Rays: " + std::to_string(lightRays.size()) + 
                             "\nTotal Spawned: " + std::to_string(rayCount) +
                             "\nPress ESC to exit" +
                             "\nPress R to reset");
        }
    }
    
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::R) {
                    // Reset simulation
                    lightRays.clear();
                    rayCount = 0;
                }
            }
        }
    }
    
    void render() {
        window.clear(sf::Color::Black);
        
        // Draw grid for reference
        drawGrid();
        
        // Draw black hole
        blackHole.draw(window);
        
        // Draw light rays
        for (const auto& ray : lightRays) {
            ray.draw(window);
        }
        
        // Draw info text
        if (font.getInfo().family != "") {
            window.draw(infoText);
        }
        
        window.display();
    }
    
    void drawGrid() {
        // Draw a subtle grid for reference
        sf::Color gridColor(30, 30, 30);
        
        // Vertical lines
        for (int x = 0; x < WINDOW_WIDTH; x += 50) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, 0), gridColor),
                sf::Vertex(sf::Vector2f(x, WINDOW_HEIGHT), gridColor)
            };
            window.draw(line, 2, sf::Lines);
        }
        
        // Horizontal lines
        for (int y = 0; y < WINDOW_HEIGHT; y += 50) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0, y), gridColor),
                sf::Vertex(sf::Vector2f(WINDOW_WIDTH, y), gridColor)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
    
    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }
};

int main() {
    try {
        BlackHoleSimulation simulation;
        simulation.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}