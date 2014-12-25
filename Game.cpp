#include "Game.hpp"

Game::Game(std::shared_ptr<sf::RenderWindow> window) {
	this->window = window;
	menu.reset(new Menu(window));
	ingame.reset(new InGame(window));
}

void Game::go() {
	menu->go();
	ingame->go();
}
