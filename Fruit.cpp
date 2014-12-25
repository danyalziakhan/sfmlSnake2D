#include "Fruit.hpp"

Fruit::Fruit(std::shared_ptr<sf::RenderWindow> window) {
	this->window = window;
	
	fruitTexture.loadFromFile("data/sprites/fruit.png");
	rect.setTexture(fruitTexture);
}
	
void Fruit::spawn(int x, int y) {
	rect.setPosition(x, y);
}

void Fruit::draw() {
	window->draw(rect);
}
