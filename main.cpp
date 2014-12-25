#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "SettingsParser.hpp"

int main(int argc, char** argv) {
	//SettingsParser settings;
    //if(!settings.loadFromFile("data/config.cfg")) {
        //std::cout << "Error loading settings file!" << std::endl;
        //return -1;
    //}
	
	int width = 800;
    int height = 600;
    //settings.get("width", width);
    //settings.get("height", height);
    
	auto window = std::make_shared<sf::RenderWindow>();
	window->create(sf::VideoMode(width, height), "Snake2D");
	
	auto game = std::make_shared<Game>(window);
    game->go();
}
