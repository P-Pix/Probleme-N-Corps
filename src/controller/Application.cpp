#include "../../include/Application.hpp"
#include <iostream>
#include <cstring>
#include <iomanip>

Application::Application(int windowWidth, int windowHeight) 
    : running(false), paused(false), lastTime(0), deltaTime(0.0),
      speedMultiplier(1.0), stepsPerFrame(1),
      mouseX(0), mouseY(0), mousePressed(false) {
    
    // Les objets seront créés après la configuration
    renderer.reset(new Renderer(windowWidth, windowHeight, "N-Body Problem Simulation"));
    
    // Initialiser le tableau des touches
    std::memset(keys, 0, sizeof(keys));
}

bool Application::initialize() {
    if (!renderer->initialize()) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return false;
    }
    
    return true;
}

bool Application::showConfigDialog() {
    ConfigWindow configWindow;
    
    if (!configWindow.initialize()) {
        std::cerr << "Failed to initialize config window!" << std::endl;
        return false;
    }
    
    currentConfig = configWindow.showConfigDialog();
    configWindow.cleanup();
    
    if (currentConfig.preset == -1) {
        return false; // L'utilisateur a annulé
    }
    
    applyConfig(currentConfig);
    running = true;
    lastTime = SDL_GetTicks();
    
    return true;
}

void Application::run() {
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;
        
        handleEvents();
        
        if (!paused) {
            update();
        }
        
        render();
        
        // Limiter le framerate
        SDL_Delay(16); // ~60 FPS
    }
}

void Application::cleanup() {
    renderer->cleanup();
}

void Application::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
                
            case SDL_KEYDOWN:
                if (e.key.keysym.scancode < SDL_NUM_SCANCODES) {
                    keys[e.key.keysym.scancode] = true;
                }
                
                // Touches spéciales
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        togglePause();
                        break;
                    case SDLK_r:
                        resetSimulation();
                        break;
                    case SDLK_t:
                        renderer->setShowTrails(!keys[SDL_SCANCODE_T]);
                        break;
                    case SDLK_c:
                        renderer->clearTrails();
                        break;
                    case SDLK_1:
                        switchPreset(1);
                        break;
                    case SDLK_2:
                        switchPreset(2);
                        break;
                    case SDLK_3:
                        switchPreset(3);
                        break;
                    case SDLK_4:
                        switchPreset(4);
                        break;
                    case SDLK_EQUALS:
                    case SDLK_PLUS:
                    case SDLK_KP_PLUS:
                        adjustSpeed(1.2);
                        break;
                    case SDLK_MINUS:
                    case SDLK_KP_MINUS:
                        adjustSpeed(0.8);
                        break;
                    case SDLK_0:
                        setSpeedMultiplier(1.0);
                        break;
                }
                break;
                
            case SDL_KEYUP:
                if (e.key.keysym.scancode < SDL_NUM_SCANCODES) {
                    keys[e.key.keysym.scancode] = false;
                }
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mousePressed = true;
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                }
                break;
                
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mousePressed = false;
                }
                break;
                
            case SDL_MOUSEMOTION:
                if (mousePressed) {
                    // Pan camera
                    int deltaX = e.motion.x - mouseX;
                    int deltaY = e.motion.y - mouseY;
                    
                    Vector2D currentOffset = Vector2D(0, 0); // Simplification
                    Vector2D newOffset = currentOffset + Vector2D(-deltaX, -deltaY);
                    renderer->setCamera(newOffset, 1.0);
                }
                mouseX = e.motion.x;
                mouseY = e.motion.y;
                break;
                
            case SDL_MOUSEWHEEL:
                // Zoom avec Ctrl, vitesse sans Ctrl
                if (keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_RCTRL]) {
                    double zoomFactor = (e.wheel.y > 0) ? 1.1 : 0.9;
                    renderer->setCamera(Vector2D(0, 0), zoomFactor);
                } else {
                    double speedFactor = (e.wheel.y > 0) ? 1.2 : 0.8;
                    adjustSpeed(speedFactor);
                }
                break;
        }
    }
    
    handleKeyboard();
}

void Application::handleKeyboard() {
    // Contrôles de la caméra
    Vector2D cameraMovement(0, 0);
    double moveSpeed = 5.0;
    
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
        cameraMovement.y -= moveSpeed;
    }
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
        cameraMovement.y += moveSpeed;
    }
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
        cameraMovement.x -= moveSpeed;
    }
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
        cameraMovement.x += moveSpeed;
    }
    
    if (cameraMovement.magnitude() > 0) {
        Vector2D currentOffset = Vector2D(0, 0); // Simplification
        renderer->setCamera(currentOffset + cameraMovement, 1.0);
    }
}

void Application::handleMouse() {
    // Géré dans handleEvents()
}

void Application::update() {
    // Exécuter plusieurs étapes selon la vitesse
    for (int i = 0; i < stepsPerFrame; ++i) {
        simulation->step();
    }
}

void Application::render() {
    renderer->clear(Color(10, 10, 30, 255)); // Fond bleu foncé
    renderer->renderSimulation(*simulation);
    
    // Afficher les instructions (simplifié)
    // TODO: Ajouter du texte avec SDL_ttf
    
    renderer->present();
}

void Application::resetSimulation() {
    renderer->clearTrails();
    // Recharger la configuration actuelle
    switchPreset(1); // Par défaut, système solaire
}

void Application::switchPreset(int preset) {
    renderer->clearTrails();
    
    switch (preset) {
        case 1:
            simulation->setupSolarSystem();
            break;
        case 2:
            simulation->setupBinarySystem();
            break;
        case 3:
            simulation->setupRandomBodies(15, 800, 600);
            break;
        case 4:
            simulation->setupGalaxyCollision();
            break;
        default:
            simulation->setupSolarSystem();
            break;
    }
    
    // Reset camera
    renderer->setCamera(Vector2D(0, 0), 1.0);
}

void Application::adjustSpeed(double factor) {
    speedMultiplier *= factor;
    
    // Limiter la vitesse
    if (speedMultiplier < 0.1) speedMultiplier = 0.1;
    if (speedMultiplier > 10.0) speedMultiplier = 10.0;
    
    // Calculer le nombre d'étapes par frame
    stepsPerFrame = static_cast<int>(speedMultiplier);
    if (stepsPerFrame < 1) stepsPerFrame = 1;
    
    std::cout << "Vitesse: x" << std::fixed << std::setprecision(1) << speedMultiplier << std::endl;
}

void Application::setSpeedMultiplier(double multiplier) {
    speedMultiplier = multiplier;
    stepsPerFrame = static_cast<int>(speedMultiplier);
    if (stepsPerFrame < 1) stepsPerFrame = 1;
    
    std::cout << "Vitesse réinitialisée: x" << std::fixed << std::setprecision(1) << speedMultiplier << std::endl;
}

void Application::applyConfig(const SimulationConfig& config) {
    currentConfig = config;
    
    // Créer la simulation avec les paramètres choisis
    simulation.reset(new Simulation(config.gravitationalConstant, config.timeStep));
    
    if (config.usePreset) {
        switchPreset(config.preset);
    } else {
        setupCustomSimulation(config.numBodies, config.gravitationalConstant);
    }
    
    std::cout << "Configuration appliquée:" << std::endl;
    std::cout << "  Nombre de corps: " << config.numBodies << std::endl;
    std::cout << "  Constante G: " << config.gravitationalConstant << std::endl;
    std::cout << "  Pas de temps: " << config.timeStep << std::endl;
}

void Application::setupCustomSimulation(int numBodies, double G) {
    (void)G; // Éviter le warning - G est déjà configuré dans la simulation
    renderer->clearTrails();
    
    // Créer une simulation personnalisée avec des corps aléatoires
    simulation->setupRandomBodies(numBodies, 800, 600);
    
    std::cout << "Simulation personnalisée créée avec " << numBodies << " corps" << std::endl;
    std::cout << "Utilisez +/- ou la molette pour ajuster la vitesse" << std::endl;
    
    // Reset camera
    renderer->setCamera(Vector2D(0, 0), 1.0);
}
