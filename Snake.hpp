#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <list>
#include "Direction.hpp"
#include "Block.hpp"

class Snake {
	public:
		static const int SIZE = 30;
		
		Snake(std::shared_ptr<sf::RenderWindow> window);
		void flip(Direction newDirection);
		void move(Direction newDirection);
		void grow();
		void shrink();
		void spawn();
		void destroy();
		void draw();
		void reset();
		
		std::list<Block> snake;
		sf::Texture snakeBlockTexture;
		sf::Texture snakeBlockFront;
		std::vector<sf::Sprite> rect;
	private:
		std::shared_ptr<sf::RenderWindow> window;
		Direction direction;
};
