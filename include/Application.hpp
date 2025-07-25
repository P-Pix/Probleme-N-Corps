#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SDL2/SDL.h>
#include "Simulation.hpp"
#include "Renderer.hpp"
#include "ConfigWindow.hpp"
#include <memory>

class Application {
private:
    std::unique_ptr<Simulation> simulation;
    std::unique_ptr<Renderer> renderer;
    bool running;
    bool paused;
    
    // Timing and speed control
    Uint32 lastTime;
    double deltaTime;
    double speedMultiplier;
    int stepsPerFrame;
    
    // Configuration
    SimulationConfig currentConfig;
    
    // Input state
    bool keys[SDL_NUM_SCANCODES];
    int mouseX, mouseY;
    bool mousePressed;
    
public:
    Application(int windowWidth = 1200, int windowHeight = 800);
    ~Application() = default;
    
    // Main loop
    bool initialize();
    bool showConfigDialog();
    void run();
    void cleanup();
    
    // Event handling
    void handleEvents();
    void handleKeyboard();
    void handleMouse();
    
    // Updates
    void update();
    void render();
    
    // Controls
    void togglePause() { paused = !paused; }
    void resetSimulation();
    void switchPreset(int preset);
    void adjustSpeed(double factor);
    void setSpeedMultiplier(double multiplier);
    
    // Configuration
    void applyConfig(const SimulationConfig& config);
    void setupCustomSimulation(int numBodies, double G);
};

#endif
