#include "../../include/Simulation.hpp"
#include <random>
#include <cmath>

Simulation::Simulation(double G, double dt) 
    : gravitationalConstant(G), timeStep(dt) {}

void Simulation::addBody(std::unique_ptr<Body> body) {
    bodies.push_back(std::move(body));
}

void Simulation::addBody(Vector2D position, Vector2D velocity, double mass, double radius) {
    bodies.push_back(std::unique_ptr<Body>(new Body(position, velocity, mass, radius)));
}

void Simulation::step() {
    calculateForces();
    updateBodies();
}

void Simulation::calculateForces() {
    // Reset all accelerations
    for (auto& body : bodies) {
        body->resetAcceleration();
    }
    
    // Calculate gravitational forces between all pairs of bodies
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            Vector2D force = bodies[i]->calculateGravitationalForce(*bodies[j], gravitationalConstant);
            
            // Apply equal and opposite forces
            bodies[i]->applyForce(force);
            bodies[j]->applyForce(force * -1.0);
        }
    }
}

void Simulation::updateBodies() {
    for (auto& body : bodies) {
        body->update(timeStep);
    }
}

void Simulation::setupSolarSystem() {
    bodies.clear();
    
    // Soleil au centre
    addBody(Vector2D(0, 0), Vector2D(0, 0), 1000.0, 20.0);
    
    // Planètes avec orbites approximatives
    addBody(Vector2D(100, 0), Vector2D(0, 30), 1.0, 3.0);    // Mercure
    addBody(Vector2D(150, 0), Vector2D(0, 25), 2.0, 4.0);    // Vénus
    addBody(Vector2D(200, 0), Vector2D(0, 22), 3.0, 5.0);    // Terre
    addBody(Vector2D(250, 0), Vector2D(0, 18), 1.5, 4.0);    // Mars
    addBody(Vector2D(350, 0), Vector2D(0, 12), 50.0, 12.0);  // Jupiter
    addBody(Vector2D(450, 0), Vector2D(0, 10), 40.0, 10.0);  // Saturne
}

void Simulation::setupRandomBodies(int count, double width, double height) {
    bodies.clear();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> posX(-width/2, width/2);
    std::uniform_real_distribution<> posY(-height/2, height/2);
    std::uniform_real_distribution<> vel(-10, 10);
    std::uniform_real_distribution<> mass(1, 20);
    
    for (int i = 0; i < count; ++i) {
        Vector2D position(posX(gen), posY(gen));
        Vector2D velocity(vel(gen), vel(gen));
        double bodyMass = mass(gen);
        double radius = std::sqrt(bodyMass) + 2;
        
        addBody(position, velocity, bodyMass, radius);
    }
}

void Simulation::setupBinarySystem() {
    bodies.clear();
    
    // Système binaire avec deux étoiles
    double separation = 200.0;
    double velocity = 15.0;
    
    addBody(Vector2D(-separation/2, 0), Vector2D(0, -velocity), 100.0, 15.0);
    addBody(Vector2D(separation/2, 0), Vector2D(0, velocity), 100.0, 15.0);
    
    // Ajouter quelques planètes autour
    addBody(Vector2D(0, 300), Vector2D(20, 0), 2.0, 4.0);
    addBody(Vector2D(0, -300), Vector2D(-20, 0), 2.0, 4.0);
}

void Simulation::setupGalaxyCollision() {
    bodies.clear();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle(0, 2 * M_PI);
    std::uniform_real_distribution<> radius(20, 150);
    
    // Première galaxie
    Vector2D center1(-200, 0);
    addBody(center1, Vector2D(5, 0), 200.0, 20.0); // Centre galactique
    
    for (int i = 0; i < 20; ++i) {
        double r = radius(gen);
        double a = angle(gen);
        Vector2D pos = center1 + Vector2D(r * cos(a), r * sin(a));
        Vector2D vel = Vector2D(-sin(a), cos(a)) * sqrt(200.0 / r) * 0.5 + Vector2D(5, 0);
        addBody(pos, vel, 2.0, 3.0);
    }
    
    // Deuxième galaxie
    Vector2D center2(200, 0);
    addBody(center2, Vector2D(-5, 0), 200.0, 20.0); // Centre galactique
    
    for (int i = 0; i < 20; ++i) {
        double r = radius(gen);
        double a = angle(gen);
        Vector2D pos = center2 + Vector2D(r * cos(a), r * sin(a));
        Vector2D vel = Vector2D(-sin(a), cos(a)) * sqrt(200.0 / r) * 0.5 + Vector2D(-5, 0);
        addBody(pos, vel, 2.0, 3.0);
    }
}
