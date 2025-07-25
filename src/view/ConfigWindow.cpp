#include "../../include/ConfigWindow.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

ConfigWindow::ConfigWindow(int width, int height) 
    : window(nullptr), renderer(nullptr), windowWidth(width), windowHeight(height),
      running(true), font(nullptr), titleFont(nullptr), selectedField(-1), inputActive(false) {}

ConfigWindow::~ConfigWindow() {
    cleanup();
}

bool ConfigWindow::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Configuration de la Simulation N-Corps",
                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             windowWidth, windowHeight,
                             SDL_WINDOW_SHOWN);
    
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Charger les polices
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
    if (!font) {
        // Essayer une police alternative
        font = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 16);
        if (!font) {
            std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            std::cerr << "Utilisation de texte simulé..." << std::endl;
        }
    }
    
    titleFont = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 20);
    if (!titleFont && font) {
        titleFont = font; // Utiliser la police normale comme fallback
    }
    
    setupUI();
    return true;
}

void ConfigWindow::cleanup() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (titleFont && titleFont != font) {
        TTF_CloseFont(titleFont);
        titleFont = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    TTF_Quit();
}

SimulationConfig ConfigWindow::showConfigDialog() {
    running = true;
    
    while (running) {
        handleEvents();
        render();
        SDL_Delay(16); // ~60 FPS
    }
    
    return config;
}

void ConfigWindow::setupUI() {
    // Clear existing UI elements
    buttons.clear();
    inputFields.clear();
    fieldLabels.clear();
    fieldValues.clear();
    
    int yOffset = 80;
    int fieldHeight = 30;
    int fieldSpacing = 50;
    
    // Preset buttons
    buttons.push_back({{50, 30, 140, 40}, "Systeme Solaire", false, 1});
    buttons.push_back({{200, 30, 140, 40}, "Etoiles Binaires", false, 2});
    buttons.push_back({{350, 30, 140, 40}, "Corps Aleatoires", false, 3});
    buttons.push_back({{500, 30, 140, 40}, "Galaxies", false, 4});
    
    // Configuration personnalisée
    fieldLabels.push_back("Nombre de corps:");
    fieldValues.push_back("10");
    inputFields.push_back({200, yOffset, 150, fieldHeight});
    yOffset += fieldSpacing;
    
    fieldLabels.push_back("Constante gravitationnelle:");
    fieldValues.push_back("50.0");
    inputFields.push_back({200, yOffset, 150, fieldHeight});
    yOffset += fieldSpacing;
    
    fieldLabels.push_back("Pas de temps:");
    fieldValues.push_back("0.01");
    inputFields.push_back({200, yOffset, 150, fieldHeight});
    yOffset += fieldSpacing;
    
    // Boutons de contrôle
    buttons.push_back({{200, yOffset + 30, 120, 50}, "Demarrer", false, 100});
    buttons.push_back({{340, yOffset + 30, 120, 50}, "Quitter", false, 101});
}

void ConfigWindow::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                running = false;
                config.preset = -1; // Indicateur d'annulation
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    
                    // Vérifier les boutons
                    for (auto& button : buttons) {
                        if (isPointInRect(mouseX, mouseY, button.rect)) {
                            button.pressed = true;
                            
                            if (button.id >= 1 && button.id <= 4) {
                                // Preset selectionne
                                config.preset = button.id;
                                config.usePreset = true;
                                running = false;
                            } else if (button.id == 100) {
                                // Demarrer avec configuration personnalisee
                                updateConfig();
                                config.usePreset = false;
                                running = false;
                            } else if (button.id == 101) {
                                // Quitter
                                running = false;
                                config.preset = -1;
                            }
                        }
                    }
                    
                    // Vérifier les champs de saisie
                    selectedField = -1;
                    for (size_t i = 0; i < inputFields.size(); ++i) {
                        if (isPointInRect(mouseX, mouseY, inputFields[i])) {
                            selectedField = static_cast<int>(i);
                            inputActive = true;
                            inputBuffer = fieldValues[i];
                            SDL_StartTextInput();
                            break;
                        }
                    }
                    
                    if (selectedField == -1) {
                        inputActive = false;
                        SDL_StopTextInput();
                    }
                }
                break;
                
            case SDL_TEXTINPUT:
                if (inputActive && selectedField >= 0) {
                    handleTextInput(e.text.text);
                }
                break;
                
            case SDL_KEYDOWN:
                if (inputActive && selectedField >= 0) {
                    handleKeyDown(e.key.keysym.sym);
                }
                break;
        }
    }
}

void ConfigWindow::render() {
    // Fond
    SDL_SetRenderDrawColor(renderer, 30, 30, 50, 255);
    SDL_RenderClear(renderer);
    
    // Titre
    drawTextCentered("Configuration de la Simulation N-Corps", 0, 10, windowWidth, {255, 255, 255, 255}, titleFont);
    
    // Prereglages
    for (const auto& button : buttons) {
        drawButton(button);
    }
    
    // Champs de configuration
    for (size_t i = 0; i < fieldLabels.size(); ++i) {
        drawText(fieldLabels[i], 20, inputFields[i].y + 8, {200, 200, 200, 255});
        drawInputField(static_cast<int>(i));
    }
    
    // Instructions
    drawText("Choisissez un prereglage ou configurez manuellement:", 20, windowHeight - 60, {150, 150, 150, 255});
    drawText("Vitesse reglable en jeu avec +/- ou molette", 20, windowHeight - 40, {150, 150, 150, 255});
    
    SDL_RenderPresent(renderer);
}

void ConfigWindow::drawText(const std::string& text, int x, int y, SDL_Color color, TTF_Font* fontToUse) {
    if (!fontToUse) fontToUse = font;
    if (!fontToUse) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(fontToUse, text.c_str(), color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void ConfigWindow::drawTextCentered(const std::string& text, int x, int y, int width, SDL_Color color, TTF_Font* fontToUse) {
    if (!fontToUse) fontToUse = font;
    if (!fontToUse) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(fontToUse, text.c_str(), color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    int centeredX = x + (width - surface->w) / 2;
    SDL_Rect destRect = {centeredX, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void ConfigWindow::drawButton(const Button& button) {
    // Couleur du bouton
    if (button.pressed || (button.id >= 1 && button.id <= 4 && config.preset == button.id)) {
        SDL_SetRenderDrawColor(renderer, 100, 150, 200, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255);
    }
    
    SDL_RenderFillRect(renderer, &button.rect);
    
    // Contour
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawRect(renderer, &button.rect);
    
    // Texte centré avec SDL_ttf
    if (font) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, button.text.c_str(), {255, 255, 255, 255});
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture) {
                int textX = button.rect.x + (button.rect.w - surface->w) / 2;
                int textY = button.rect.y + (button.rect.h - surface->h) / 2;
                SDL_Rect destRect = {textX, textY, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, nullptr, &destRect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
    }
}

void ConfigWindow::drawInputField(int index) {
    const SDL_Rect& field = inputFields[index];
    
    // Fond du champ
    if (selectedField == index) {
        SDL_SetRenderDrawColor(renderer, 80, 80, 120, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
    }
    SDL_RenderFillRect(renderer, &field);
    
    // Contour
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderDrawRect(renderer, &field);
    
    // Texte
    std::string displayText = (selectedField == index && inputActive) ? inputBuffer : fieldValues[index];
    drawText(displayText, field.x + 5, field.y + 8, {255, 255, 255, 255});
    
    // Curseur
    if (selectedField == index && inputActive) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int cursorX = field.x + 5 + static_cast<int>(inputBuffer.length()) * 8;
        SDL_RenderDrawLine(renderer, cursorX, field.y + 5, cursorX, field.y + field.h - 5);
    }
}

void ConfigWindow::updateConfig() {
    try {
        config.numBodies = std::stoi(fieldValues[0]);
        config.gravitationalConstant = std::stod(fieldValues[1]);
        config.timeStep = std::stod(fieldValues[2]);
        
        // Validation des valeurs
        if (config.numBodies < 1) config.numBodies = 1;
        if (config.numBodies > 100) config.numBodies = 100;
        if (config.gravitationalConstant < 0.1) config.gravitationalConstant = 0.1;
        if (config.gravitationalConstant > 1000.0) config.gravitationalConstant = 1000.0;
        if (config.timeStep < 0.001) config.timeStep = 0.001;
        if (config.timeStep > 0.1) config.timeStep = 0.1;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur de conversion des valeurs: " << e.what() << std::endl;
        // Utiliser les valeurs par defaut
        config.numBodies = 10;
        config.gravitationalConstant = 50.0;
        config.timeStep = 0.01;
    }
}

bool ConfigWindow::isPointInRect(int x, int y, const SDL_Rect& rect) {
    return x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h;
}

void ConfigWindow::handleTextInput(const std::string& text) {
    if (selectedField >= 0 && selectedField < static_cast<int>(fieldValues.size())) {
        // Filtrer les caracteres valides selon le champ
        char c = text[0];
        if (selectedField == 0) {
            // Nombre de corps : seulement des chiffres
            if (c >= '0' && c <= '9') {
                inputBuffer += c;
            }
        } else {
            // Valeurs decimales : chiffres, point, signe moins
            if ((c >= '0' && c <= '9') || c == '.' || c == '-') {
                inputBuffer += c;
            }
        }
        
        // Limiter la longueur
        if (inputBuffer.length() > 10) {
            inputBuffer = inputBuffer.substr(0, 10);
        }
    }
}

void ConfigWindow::handleKeyDown(SDL_Keycode key) {
    if (selectedField >= 0 && selectedField < static_cast<int>(fieldValues.size())) {
        switch (key) {
            case SDLK_BACKSPACE:
                if (!inputBuffer.empty()) {
                    inputBuffer.pop_back();
                }
                break;
                
            case SDLK_RETURN:
            case SDLK_KP_ENTER:
                fieldValues[selectedField] = inputBuffer;
                selectedField = -1;
                inputActive = false;
                SDL_StopTextInput();
                break;
                
            case SDLK_ESCAPE:
                inputBuffer = fieldValues[selectedField];
                selectedField = -1;
                inputActive = false;
                SDL_StopTextInput();
                break;
        }
    }
}
