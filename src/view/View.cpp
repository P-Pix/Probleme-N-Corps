#include "../../include/View.hpp"

View::View(std::string name, sf::RenderWindow* window) {
    this->name = name;
    this->window = window;
}

View::~View() {
    delete this->window;
}

void View::render(std::vector<sf::Sprite> sprites) {
    this->window->clear();
    for (sf::Sprite sprite : sprites) {
        this->window->draw(sprite);
    }
    this->window->display();
}