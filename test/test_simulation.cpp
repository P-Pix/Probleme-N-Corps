#include "../include/Simulation.hpp"
#include "../include/Body.hpp"
#include <iostream>
#include <cassert>

void testBodyCreation() {
    std::cout << "Test: Création d'un corps..." << std::endl;
    Body body(Vector2D(100, 100), Vector2D(10, 5), 50.0, 8.0);
    
    assert(body.getPosition().x == 100);
    assert(body.getPosition().y == 100);
    assert(body.getVelocity().x == 10);
    assert(body.getVelocity().y == 5);
    assert(body.getMass() == 50.0);
    assert(body.getRadius() == 8.0);
    
    std::cout << "✅ Corps créé avec succès" << std::endl;
}

void testVector2D() {
    std::cout << "Test: Opérations Vector2D..." << std::endl;
    
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    Vector2D sum = v1 + v2;
    assert(sum.x == 4 && sum.y == 6);
    
    Vector2D diff = v1 - v2;
    assert(diff.x == 2 && diff.y == 2);
    
    Vector2D scaled = v1 * 2;
    assert(scaled.x == 6 && scaled.y == 8);
    
    double mag = v1.magnitude();
    assert(mag == 5.0); // sqrt(3² + 4²) = 5
    
    std::cout << "✅ Opérations Vector2D correctes" << std::endl;
}

void testSimulation() {
    std::cout << "Test: Simulation basique..." << std::endl;
    
    Simulation sim(50.0, 0.01);
    
    // Ajouter quelques corps
    sim.addBody(Vector2D(0, 0), Vector2D(0, 0), 100.0, 10.0);
    sim.addBody(Vector2D(100, 0), Vector2D(0, 20), 1.0, 3.0);
    
    assert(sim.getBodyCount() == 2);
    
    // Exécuter quelques étapes
    Vector2D initialPos = sim.getBodies()[1]->getPosition();
    
    for (int i = 0; i < 100; ++i) {
        sim.step();
    }
    
    Vector2D finalPos = sim.getBodies()[1]->getPosition();
    
    // Vérifier que la position a changé (le corps a bougé)
    assert(initialPos.x != finalPos.x || initialPos.y != finalPos.y);
    
    std::cout << "✅ Simulation fonctionne" << std::endl;
    std::cout << "   Position initiale: (" << initialPos.x << ", " << initialPos.y << ")" << std::endl;
    std::cout << "   Position finale: (" << finalPos.x << ", " << finalPos.y << ")" << std::endl;
}

void testPresets() {
    std::cout << "Test: Préréglages de simulation..." << std::endl;
    
    Simulation sim(50.0, 0.01);
    
    // Tester le système solaire
    sim.setupSolarSystem();
    assert(sim.getBodyCount() > 0);
    std::cout << "   Système solaire: " << sim.getBodyCount() << " corps" << std::endl;
    
    // Tester le système binaire
    sim.setupBinarySystem();
    assert(sim.getBodyCount() > 0);
    std::cout << "   Système binaire: " << sim.getBodyCount() << " corps" << std::endl;
    
    // Tester les corps aléatoires
    sim.setupRandomBodies(10, 800, 600);
    assert(sim.getBodyCount() == 10);
    std::cout << "   Corps aléatoires: " << sim.getBodyCount() << " corps" << std::endl;
    
    // Tester la collision de galaxies
    sim.setupGalaxyCollision();
    assert(sim.getBodyCount() > 0);
    std::cout << "   Collision de galaxies: " << sim.getBodyCount() << " corps" << std::endl;
    
    std::cout << "✅ Tous les préréglages fonctionnent" << std::endl;
}

int main() {
    std::cout << "=== Tests de la Simulation N-Corps ===" << std::endl << std::endl;
    
    try {
        testVector2D();
        std::cout << std::endl;
        
        testBodyCreation();
        std::cout << std::endl;
        
        testSimulation();
        std::cout << std::endl;
        
        testPresets();
        std::cout << std::endl;
        
        std::cout << "🎉 Tous les tests sont passés avec succès !" << std::endl;
        std::cout << "La simulation est prête à être utilisée." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Erreur pendant les tests: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
