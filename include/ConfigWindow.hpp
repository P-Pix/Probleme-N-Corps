/**
 * @file ConfigWindow.hpp
 * @brief Interface de configuration pour la simulation N-Corps
 * @author P-Pix
 * @date 2025
 */

#ifndef CONFIG_WINDOW_HPP
#define CONFIG_WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

/**
 * @struct SimulationConfig
 * @brief Structure contenant les paramètres de configuration de la simulation
 */
struct SimulationConfig {
    int numBodies;                  ///< Nombre de corps dans la simulation
    double gravitationalConstant;   ///< Constante gravitationnelle
    double timeStep;               ///< Pas de temps pour l'intégration numérique
    int preset;                    ///< ID du préréglage sélectionné
    bool usePreset;               ///< Indique si un préréglage est utilisé
    
    /**
     * @brief Constructeur par défaut avec valeurs standard
     */
    SimulationConfig() : numBodies(10), gravitationalConstant(50.0), 
                        timeStep(0.01), preset(1), usePreset(true) {}
};

/**
 * @class ConfigWindow
 * @brief Fenêtre de configuration interactive pour la simulation N-Corps
 * 
 * Cette classe gère l'interface utilisateur permettant de configurer
 * les paramètres de la simulation avant son lancement.
 */
class ConfigWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;
    bool running;
    SimulationConfig config;
    
    // Font for text rendering
    TTF_Font* font;
    TTF_Font* titleFont;
    
    // UI elements state
    int selectedField;
    bool inputActive;
    std::string inputBuffer;
    
    // Button states
    struct Button {
        SDL_Rect rect;
        std::string text;
        bool pressed;
        int id;
    };
    
    std::vector<Button> buttons;
    std::vector<SDL_Rect> inputFields;
    std::vector<std::string> fieldLabels;
    std::vector<std::string> fieldValues;
    
public:
    /**
     * @brief Constructeur de la fenêtre de configuration
     * @param width Largeur de la fenêtre en pixels
     * @param height Hauteur de la fenêtre en pixels
     */
    ConfigWindow(int width = 700, int height = 500);
    
    /**
     * @brief Destructeur
     */
    ~ConfigWindow();
    
    /**
     * @brief Initialise SDL et crée la fenêtre
     * @return true si l'initialisation a réussi, false sinon
     */
    bool initialize();
    
    /**
     * @brief Nettoie les ressources SDL
     */
    void cleanup();
    
    /**
     * @brief Affiche la fenêtre de configuration et retourne la configuration
     * @return Structure SimulationConfig avec les paramètres choisis
     */
    SimulationConfig showConfigDialog();
    
private:
    void handleEvents();
    void render();
    void setupUI();
    void drawText(const std::string& text, int x, int y, SDL_Color color = {255, 255, 255, 255}, TTF_Font* useFont = nullptr);
    void drawTextCentered(const std::string& text, int x, int y, int width, SDL_Color color = {255, 255, 255, 255}, TTF_Font* useFont = nullptr);
    void drawButton(const Button& button);
    void drawInputField(int index);
    void updateConfig();
    bool isPointInRect(int x, int y, const SDL_Rect& rect);
    void handleTextInput(const std::string& text);
    void handleKeyDown(SDL_Keycode key);
};

#endif
