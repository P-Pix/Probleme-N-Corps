#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Body.hpp"
#include <vector>
#include <memory>

class Simulation {
private:
    std::vector<std::unique_ptr<Body>> bodies;
    double gravitationalConstant;
    double timeStep;
    
public:
    Simulation(double G = 1.0, double dt = 0.01);
    ~Simulation() = default;
    
    // Body management
    void addBody(std::unique_ptr<Body> body);
    void addBody(Vector2D position, Vector2D velocity, double mass, double radius = 5.0);
    
    // Simulation
    void step();
    void calculateForces();
    void updateBodies();
    
    // Getters
    const std::vector<std::unique_ptr<Body>>& getBodies() const { return bodies; }
    size_t getBodyCount() const { return bodies.size(); }
    
    // Presets
    void setupSolarSystem();
    void setupRandomBodies(int count, double width, double height);
    void setupBinarySystem();
    void setupGalaxyCollision();
};

#endif
