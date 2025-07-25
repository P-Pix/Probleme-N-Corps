#include "../../include/Renderer.hpp"
#include <iostream>
#include <cmath>

Renderer::Renderer(int width, int height, const char* title)
    : window(nullptr), renderer(nullptr), windowWidth(width), windowHeight(height),
      cameraOffset(0, 0), zoomLevel(1.0), showTrails(true), maxTrailLength(100) {
    windowTitle = title;
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(windowTitle,
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             windowWidth, windowHeight,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Enable blending for alpha transparency
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    return true;
}

void Renderer::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Renderer::clear(Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::renderSimulation(const Simulation& simulation) {
    updateTrails(simulation);
    
    if (showTrails) {
        renderTrails();
    }
    
    const auto& bodies = simulation.getBodies();
    for (size_t i = 0; i < bodies.size(); ++i) {
        Color bodyColor;
        
        // Couleurs différentes selon la masse
        double mass = bodies[i]->getMass();
        if (mass > 100) {
            bodyColor = Color(255, 255, 0, 255);  // Jaune pour les étoiles
        } else if (mass > 50) {
            bodyColor = Color(255, 165, 0, 255);  // Orange pour les planètes géantes
        } else if (mass > 10) {
            bodyColor = Color(0, 255, 0, 255);    // Vert pour les grosses planètes
        } else {
            bodyColor = Color(100, 150, 255, 255); // Bleu pour les petites planètes
        }
        
        renderBody(*bodies[i], bodyColor);
    }
}

void Renderer::renderBody(const Body& body, Color color) {
    Vector2D screenPos = worldToScreen(body.getPosition());
    int radius = static_cast<int>(body.getRadius() * zoomLevel);
    
    // S'assurer que le rayon est au moins de 1 pixel
    if (radius < 1) radius = 1;
    
    fillCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), radius, color);
    
    // Dessiner un contour plus sombre
    Color borderColor(color.r / 2, color.g / 2, color.b / 2, color.a);
    drawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), radius, borderColor);
}

void Renderer::renderTrails() {
    for (size_t i = 0; i < trails.size(); ++i) {
        const auto& trail = trails[i];
        if (trail.size() < 2) continue;
        
        for (size_t j = 1; j < trail.size(); ++j) {
            Vector2D start = worldToScreen(trail[j-1]);
            Vector2D end = worldToScreen(trail[j]);
            
            // Fade effect basé sur l'âge du point
            int alpha = static_cast<int>(255.0 * j / trail.size());
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, alpha);
            
            SDL_RenderDrawLine(renderer, 
                             static_cast<int>(start.x), static_cast<int>(start.y),
                             static_cast<int>(end.x), static_cast<int>(end.y));
        }
    }
}

void Renderer::fillCircle(int centerX, int centerY, int radius, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

void Renderer::drawCircle(int centerX, int centerY, int radius, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    int x = radius;
    int y = 0;
    int err = 0;
    
    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        
        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

void Renderer::setCamera(Vector2D offset, double zoom) {
    cameraOffset = offset;
    zoomLevel = zoom;
}

Vector2D Renderer::worldToScreen(const Vector2D& worldPos) const {
    Vector2D centered = worldPos - cameraOffset;
    Vector2D scaled = centered * zoomLevel;
    return Vector2D(scaled.x + windowWidth / 2, scaled.y + windowHeight / 2);
}

Vector2D Renderer::screenToWorld(const Vector2D& screenPos) const {
    Vector2D centered = Vector2D(screenPos.x - windowWidth / 2, screenPos.y - windowHeight / 2);
    Vector2D scaled = centered * (1.0 / zoomLevel);
    return scaled + cameraOffset;
}

void Renderer::updateTrails(const Simulation& simulation) {
    const auto& bodies = simulation.getBodies();
    
    // Redimensionner le vecteur de trails si nécessaire
    if (trails.size() != bodies.size()) {
        trails.resize(bodies.size());
    }
    
    // Ajouter les positions actuelles aux trails
    for (size_t i = 0; i < bodies.size(); ++i) {
        trails[i].push_back(bodies[i]->getPosition());
        
        // Limiter la longueur des trails
        if (trails[i].size() > static_cast<size_t>(maxTrailLength)) {
            trails[i].erase(trails[i].begin());
        }
    }
}

void Renderer::clearTrails() {
    for (auto& trail : trails) {
        trail.clear();
    }
}
