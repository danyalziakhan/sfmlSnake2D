#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Block.hpp"

class Fruit {
	public:
		Fruit(std::shared_ptr<sf::RenderWindow> window);
		
		void spawn(int x, int y);
		void draw();
		
		Block fruit;
		sf::Texture fruitTexture;
		sf::Sprite rect;
	private:
		std::shared_ptr<sf::RenderWindow> window;
};
