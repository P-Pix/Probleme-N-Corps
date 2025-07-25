#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Body.hpp"
#include "Simulation.hpp"

struct Color {
    Uint8 r, g, b, a;
    Color(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255) : r(r), g(g), b(b), a(a) {}
};

class Renderer {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;
    const char* windowTitle;
    
    // Camera
    Vector2D cameraOffset;
    double zoomLevel;
    
    // Trails
    bool showTrails;
    std::vector<std::vector<Vector2D>> trails;
    int maxTrailLength;
    
public:
    Renderer(int width, int height, const char* title);
    ~Renderer();
    
    // Initialization
    bool initialize();
    void cleanup();
    
    // Rendering
    void clear(Color color = Color(0, 0, 0, 255));
    void present();
    void renderSimulation(const Simulation& simulation);
    void renderBody(const Body& body, Color color = Color(255, 255, 255, 255));
    void renderTrails();
    
    // Utility
    void fillCircle(int centerX, int centerY, int radius, Color color);
    void drawCircle(int centerX, int centerY, int radius, Color color);
    
    // Camera controls
    void setCamera(Vector2D offset, double zoom);
    Vector2D worldToScreen(const Vector2D& worldPos) const;
    Vector2D screenToWorld(const Vector2D& screenPos) const;
    
    // Trail management
    void updateTrails(const Simulation& simulation);
    void clearTrails();
    void setShowTrails(bool show) { showTrails = show; }
    void setMaxTrailLength(int length) { maxTrailLength = length; }
    
    // Getters
    int getWidth() const { return windowWidth; }
    int getHeight() const { return windowHeight; }
    SDL_Renderer* getSDLRenderer() const { return renderer; }
};

#endif
