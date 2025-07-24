#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class View {
    private:
        std::string name;
        sf::RenderWindow* window;

    public:
        View(std::string name, sf::RenderWindow* window);
        ~View();
        void render(std::vector<sf::Sprite> sprites);
};