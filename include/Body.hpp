#ifndef BODY_HPP
#define BODY_HPP

#include <cmath>

struct Vector2D {
    double x, y;
    
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    
    Vector2D normalize() const {
        double mag = magnitude();
        if (mag == 0) return Vector2D(0, 0);
        return Vector2D(x / mag, y / mag);
    }
};

class Body {
private:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    double mass;
    double radius;
    
public:
    Body(Vector2D pos, Vector2D vel, double m, double r = 5.0);
    
    // Getters
    Vector2D getPosition() const { return position; }
    Vector2D getVelocity() const { return velocity; }
    double getMass() const { return mass; }
    double getRadius() const { return radius; }
    
    // Setters
    void setPosition(const Vector2D& pos) { position = pos; }
    void setVelocity(const Vector2D& vel) { velocity = vel; }
    void setAcceleration(const Vector2D& acc) { acceleration = acc; }
    
    // Physics
    void applyForce(const Vector2D& force);
    void update(double deltaTime);
    void resetAcceleration();
    
    // Calculate gravitational force to another body
    Vector2D calculateGravitationalForce(const Body& other, double G = 6.67430e-11) const;
};

#endif
