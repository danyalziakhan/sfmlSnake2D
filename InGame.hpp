#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <memory>
#include <vector>
#include "Snake.hpp"
#include "Fruit.hpp"
#include "Direction.hpp"

class InGame {
	public:
		InGame(std::shared_ptr<sf::RenderWindow> window);
		
		bool go();
	
	private:
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<Snake> snake;
		std::shared_ptr<Fruit> fruit;
		Direction direction;
		sf::Clock clock;
		
		sf::Font font;
		sf::Text scoreTxt, speedTxt, pauseTxt;
		
		sf::Music mainMusic;
		sf::SoundBuffer eatFruitBuffer;
		sf::Sound eatFruitSound;
		
		// Tells if we need to respawn a fruit
		bool mustSpawnFruit = true;
		
		// Coords of the fruit
		int fruitX;
		int fruitY;
		
		bool isPaused = false;
		bool isLost = false;
		
		unsigned int score = 0;
		unsigned int speed = 0;
	
		// Main loop
		sf::Clock frameClock;
};
