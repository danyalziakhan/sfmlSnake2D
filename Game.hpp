#pragma once

#include "Menu.hpp"
#include "InGame.hpp"

class Game {
	public:
		Game(std::shared_ptr<sf::RenderWindow> window);
		void go();
		
	private:
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<Menu> menu;
		std::shared_ptr<InGame> ingame;
};
