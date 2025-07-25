#include "../include/Application.hpp"
#include <iostream>

int main(int argc, char** argv) {
    (void)argc; // Éviter les warnings de variables non utilisées
    (void)argv;
    
    std::cout << "=== N-Body Problem Simulation ===" << std::endl;
    std::cout << "Lancement de la fenêtre de configuration..." << std::endl;
    
    Application app(1200, 800);
    
    if (!app.initialize()) {
        std::cerr << "Failed to initialize application!" << std::endl;
        return -1;
    }
    
    // Afficher la fenêtre de configuration
    if (!app.showConfigDialog()) {
        std::cout << "Configuration annulée ou fermée." << std::endl;
        return 0;
    }
    
    std::cout << "\n=== Contrôles de la Simulation ===" << std::endl;
    std::cout << "  ESPACE - Pause/Resume simulation" << std::endl;
    std::cout << "  R - Reset simulation" << std::endl;
    std::cout << "  T - Toggle trails" << std::endl;
    std::cout << "  C - Clear trails" << std::endl;
    std::cout << "  1-4 - Préréglages" << std::endl;
    std::cout << "  +/- - Ajuster vitesse" << std::endl;
    std::cout << "  0 - Vitesse normale" << std::endl;
    std::cout << "  WASD/Arrow Keys - Move camera" << std::endl;
    std::cout << "  Ctrl + Mouse Wheel - Zoom" << std::endl;
    std::cout << "  Mouse Wheel - Vitesse" << std::endl;
    std::cout << "  Mouse Drag - Pan camera" << std::endl;
    std::cout << "===============================" << std::endl;
    
    app.run();
    app.cleanup();
    
    return 0;
}

