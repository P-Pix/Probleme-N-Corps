#include "../../include/Body.hpp"

Body::Body(Vector2D pos, Vector2D vel, double m, double r) 
    : position(pos), velocity(vel), acceleration(0, 0), mass(m), radius(r) {}

void Body::applyForce(const Vector2D& force) {
    // F = ma, donc a = F/m
    acceleration = acceleration + force * (1.0 / mass);
}

void Body::update(double deltaTime) {
    // Intégration de Verlet pour une meilleure stabilité
    velocity = velocity + acceleration * deltaTime;
    position = position + velocity * deltaTime;
}

void Body::resetAcceleration() {
    acceleration = Vector2D(0, 0);
}

Vector2D Body::calculateGravitationalForce(const Body& other, double G) const {
    Vector2D direction = other.position - position;
    double distance = direction.magnitude();
    
    // Éviter la singularité quand les corps sont trop proches
    if (distance < (radius + other.radius)) {
        distance = radius + other.radius;
    }
    
    // Force gravitationnelle: F = G * m1 * m2 / r²
    double forceMagnitude = G * mass * other.mass / (distance * distance);
    
    // Direction normalisée
    Vector2D forceDirection = direction.normalize();
    
    return forceDirection * forceMagnitude;
}
