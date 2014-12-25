#include "Snake.hpp"

Snake::Snake(std::shared_ptr<sf::RenderWindow> window) {
	this->window = window;
	
	snake.push_back(Block(SIZE, 0));
	snake.push_back(Block(SIZE*2, 0));
	
	direction = Direction::right;
	snakeBlockTexture.loadFromFile("data/sprites/snake.png");
	snakeBlockFront.loadFromFile("data/sprites/snakefront.png");
}

void Snake::flip(Direction newDirection)
{
	direction = newDirection;
	if(newDirection == Direction::up) {
		if(direction != Direction::down) {
			snake.front() = (Block(snake.front().x, snake.front().y + window->getSize().y));
			direction = Direction::up;
		}
		else {
			snake.front() = (Block(snake.front().x, snake.front().y - window->getSize().y));
		}
	}

	else if(newDirection == Direction::right) {
		if(direction != Direction::left) {
			snake.front() = (Block(snake.front().x - window->getSize().x, snake.front().y));
			direction = Direction::right;	
		}
		else {
			snake.front() = (Block(snake.front().x + window->getSize().x, snake.front().y));
		}
	}

	else if(newDirection == Direction::down) {
		if(direction != Direction::up) {
			snake.front() = (Block(snake.front().x, snake.front().y - window->getSize().y));
			direction = Direction::down;
		}
		else {
			snake.front() = (Block(snake.front().x, snake.front().y + window->getSize().y));
		}
	}

	else if(newDirection == Direction::left) {
		if(direction != Direction::right) {
			snake.front() = (Block(snake.front().x + window->getSize().x, snake.front().y));
			direction = Direction::left;	
		}
		else {
			snake.front() = (Block(snake.front().x - window->getSize().x, snake.front().y));
		}
	}
}

void Snake::move(Direction newDirection) {
	shrink();
	direction = newDirection;
	if(newDirection == Direction::right) {
		if(direction != Direction::left) {
			snake.push_front(Block(snake.front().x + 30, snake.front().y));
			direction = Direction::right;	
		}
		else  {
			snake.push_front(Block(snake.front().x - 30, snake.front().y));
		}
	}
	
	else if(newDirection == Direction::left) {
		if(direction != Direction::right) {
			snake.push_front(Block(snake.front().x - 30, snake.front().y));
			direction = Direction::left;	
		}
		
		else  {
			snake.push_front(Block(snake.front().x + 30, snake.front().y));
		}
	}
	
	else if(newDirection == Direction::up) {
		if(direction != Direction::down) {
			snake.push_front(Block(snake.front().x, snake.front().y - 30));
			direction = Direction::up;
		}
		else {
			snake.push_front(Block(snake.front().x, snake.front().y + 30));
		}
	}
	
	else if(newDirection == Direction::down) {
		if(direction != Direction::up) {
			snake.push_front(Block(snake.front().x, snake.front().y + 30));
			direction = Direction::down;
		}
		
		else {
			snake.push_front(Block(snake.front().x, snake.front().y - 30));
		}
	}
}

void Snake::grow() {
	snake.push_back(Block(snake.back().x, snake.back().y));
}

void Snake::shrink() {
	snake.pop_back();
}

void Snake::spawn() {
		rect.clear();
		auto i = snake.begin();
		sf::Sprite shape;
		shape.setTexture(snakeBlockFront);
		shape.setPosition(400+i->x, 200+i->y);
		
		if (direction == Direction::left) {
			shape.setTextureRect(sf::IntRect(35, 0, -35, 35));
		}
		
		if (direction == Direction::up) {
			shape.setRotation(-90);
			shape.setPosition(shape.getPosition().x, shape.getPosition().y+35);
		}
		
		if (direction == Direction::down) {
			shape.setRotation(90);
			shape.setPosition(shape.getPosition().x+35, shape.getPosition().y);
		}
		
		rect.push_back(shape);
		i++; // skip the front element
		
	for(i; i != snake.end(); ++i) {
		sf::Sprite shape;
		shape.setTexture(snakeBlockTexture);
		shape.setPosition(400+i->x, 200+i->y);
		rect.push_back(shape);
	}
}

void Snake::destroy() {
	shrink();
	snake.clear();
}

void Snake::draw() {
	for(auto i : rect) {
		window->draw(i);
	}
}

void Snake::reset() {
	destroy();
	snake.push_front(Block(SIZE,0));
	snake.push_front(Block(SIZE*2,0));
	move(Direction::right);
	move(Direction::down);
}
