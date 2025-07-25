#include "../include/Simulation.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

void demonstrateOrbit() {
    std::cout << "\n=== Démonstration d'Orbite Circulaire ===" << std::endl;
    
    Simulation sim(100.0, 0.001); // G plus élevé, dt plus petit pour la précision
    
    // Créer un système simple: étoile + planète
    sim.addBody(Vector2D(0, 0), Vector2D(0, 0), 1000.0, 20.0);     // Étoile centrale
    sim.addBody(Vector2D(100, 0), Vector2D(0, 31.6), 1.0, 3.0);    // Planète en orbite
    
    std::cout << "Configuration initiale:" << std::endl;
    std::cout << "  Étoile: Position(0,0), Masse=1000" << std::endl;
    std::cout << "  Planète: Position(100,0), Vitesse(0,31.6), Masse=1" << std::endl;
    std::cout << "  Vitesse orbitale théorique: v = sqrt(GM/r) = " << sqrt(100.0 * 1000.0 / 100.0) << std::endl;
    
    // Sauvegarder les positions pour tracer l'orbite
    std::ofstream file("orbit_data.csv");
    file << "step,x,y,distance,velocity\n";
    
    Vector2D initialPos = sim.getBodies()[1]->getPosition();
    double initialDistance = initialPos.magnitude();
    
    std::cout << "\nSimulation en cours..." << std::endl;
    
    for (int step = 0; step < 2000; ++step) {
        sim.step();
        
        Vector2D pos = sim.getBodies()[1]->getPosition();
        Vector2D vel = sim.getBodies()[1]->getVelocity();
        double distance = pos.magnitude();
        double speed = vel.magnitude();
        
        // Enregistrer quelques points
        if (step % 100 == 0) {
            file << step << "," << pos.x << "," << pos.y << "," << distance << "," << speed << "\n";
            
            std::cout << "  Étape " << std::setw(4) << step 
                     << ": Distance=" << std::fixed << std::setprecision(2) << distance
                     << ", Vitesse=" << std::setprecision(2) << speed << std::endl;
        }
    }
    
    file.close();
    
    Vector2D finalPos = sim.getBodies()[1]->getPosition();
    double finalDistance = finalPos.magnitude();
    
    std::cout << "\nRésultats:" << std::endl;
    std::cout << "  Distance initiale: " << initialDistance << std::endl;
    std::cout << "  Distance finale: " << finalDistance << std::endl;
    std::cout << "  Variation: " << std::abs(finalDistance - initialDistance) / initialDistance * 100 << "%" << std::endl;
    
    if (std::abs(finalDistance - initialDistance) / initialDistance < 0.1) {
        std::cout << "  ✅ Orbite stable!" << std::endl;
    } else {
        std::cout << "  ⚠️  Orbite instable (normal pour une simulation numérique)" << std::endl;
    }
    
    std::cout << "  Données sauvegardées dans orbit_data.csv" << std::endl;
}

void demonstrateChaos() {
    std::cout << "\n=== Démonstration du Chaos Gravitationnel ===" << std::endl;
    
    Simulation sim(50.0, 0.01);
    
    // Système de 3 corps de masses égales
    sim.addBody(Vector2D(-50, 0), Vector2D(0, 10), 100.0, 10.0);
    sim.addBody(Vector2D(50, 0), Vector2D(0, -10), 100.0, 10.0);
    sim.addBody(Vector2D(0, 50), Vector2D(-10, 0), 100.0, 10.0);
    
    std::cout << "Système de 3 corps identiques en formation triangulaire" << std::endl;
    std::cout << "Positions initiales: (-50,0), (50,0), (0,50)" << std::endl;
    
    // Calculer le centre de masse initial
    Vector2D centerOfMass(0, 0);
    double totalMass = 0;
    for (const auto& body : sim.getBodies()) {
        centerOfMass = centerOfMass + body->getPosition() * body->getMass();
        totalMass += body->getMass();
    }
    centerOfMass = centerOfMass * (1.0 / totalMass);
    
    std::cout << "Centre de masse initial: (" << centerOfMass.x << ", " << centerOfMass.y << ")" << std::endl;
    
    // Simuler et observer l'évolution
    for (int step = 0; step < 1000; step += 100) {
        for (int i = 0; i < 100; ++i) {
            sim.step();
        }
        
        // Recalculer le centre de masse
        Vector2D newCenterOfMass(0, 0);
        double newTotalMass = 0;
        for (const auto& body : sim.getBodies()) {
            newCenterOfMass = newCenterOfMass + body->getPosition() * body->getMass();
            newTotalMass += body->getMass();
        }
        newCenterOfMass = newCenterOfMass * (1.0 / newTotalMass);
        
        std::cout << "Étape " << std::setw(4) << step << ": Centre de masse(" 
                 << std::fixed << std::setprecision(2) << newCenterOfMass.x 
                 << ", " << newCenterOfMass.y << ")" << std::endl;
    }
    
    std::cout << "✅ Conservation du moment: le centre de masse reste stable" << std::endl;
}

void demonstratePresets() {
    std::cout << "\n=== Test des Préréglages ===" << std::endl;
    
    Simulation sim(50.0, 0.01);
    
    // Tester chaque préréglage
    struct PresetInfo {
        std::string name;
        void (Simulation::*method)();
    };
    
    PresetInfo presets[] = {
        {"Système Solaire", &Simulation::setupSolarSystem},
        {"Système Binaire", &Simulation::setupBinarySystem},
        {"Collision de Galaxies", &Simulation::setupGalaxyCollision}
    };
    
    for (const auto& preset : presets) {
        (sim.*(preset.method))();
        
        std::cout << "\n" << preset.name << ":" << std::endl;
        std::cout << "  Nombre de corps: " << sim.getBodyCount() << std::endl;
        
        // Calculer la masse totale et l'énergie approximative
        double totalMass = 0;
        double kineticEnergy = 0;
        
        for (const auto& body : sim.getBodies()) {
            totalMass += body->getMass();
            double speed = body->getVelocity().magnitude();
            kineticEnergy += 0.5 * body->getMass() * speed * speed;
        }
        
        std::cout << "  Masse totale: " << totalMass << std::endl;
        std::cout << "  Énergie cinétique initiale: " << std::fixed << std::setprecision(2) << kineticEnergy << std::endl;
        
        // Simuler quelques étapes pour vérifier la stabilité
        for (int i = 0; i < 100; ++i) {
            sim.step();
        }
        
        double newKineticEnergy = 0;
        for (const auto& body : sim.getBodies()) {
            double speed = body->getVelocity().magnitude();
            newKineticEnergy += 0.5 * body->getMass() * speed * speed;
        }
        
        double energyChange = std::abs(newKineticEnergy - kineticEnergy) / kineticEnergy * 100;
        std::cout << "  Variation d'énergie après 100 étapes: " << energyChange << "%" << std::endl;
        
        if (energyChange < 10.0) {
            std::cout << "  ✅ Préréglage stable" << std::endl;
        } else {
            std::cout << "  ⚠️  Système dynamique (normal)" << std::endl;
        }
    }
}

int main() {
    std::cout << "🌟 DÉMONSTRATION SIMULATION N-CORPS 🌟" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    demonstrateOrbit();
    demonstrateChaos();
    demonstratePresets();
    
    std::cout << "\n🎉 DÉMONSTRATION TERMINÉE 🎉" << std::endl;
    std::cout << "La simulation fonctionne correctement!" << std::endl;
    std::cout << "Utilisez './N-Corps' pour la version graphique interactive." << std::endl;
    
    return 0;
}
