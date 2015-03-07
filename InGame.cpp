#include "InGame.hpp"
#include <string>

InGame::InGame(std::shared_ptr<sf::RenderWindow> window) {
	this->window = window;
	
	snake = std::make_shared<Snake>(window);
	fruit = std::make_shared<Fruit>(window);
	
	direction = Direction::right;
	srand(time(NULL));
	
	font.loadFromFile("data/font/sansation.ttf");
	scoreTxt.setFont(font);
	scoreTxt.setColor(sf::Color::White);
	scoreTxt.setString("Score: " + std::to_string(score));
	scoreTxt.setPosition(10,0);
	
	speedTxt.setFont(font);
	speedTxt.setColor(sf::Color::White);
	speedTxt.setString("Speed: " + std::to_string(speed));
	speedTxt.setPosition(window->getSize().x-140,0);

	pauseTxt.setFont(font);
	pauseTxt.setColor(sf::Color::White);
	pauseTxt.setString("Pause!\n\n Press Enter to Continue!");
	pauseTxt.setPosition(window->getSize().x/4,window->getSize().y/3);
	
	mainMusic.openFromFile("data/audio/Galaxy - New Electro House Techno by MafiaFLairBeatz.ogg");
	mainMusic.setLoop(true);
	
	eatFruitBuffer.loadFromFile("data/audio/bite.ogg");
	eatFruitSound.setBuffer(eatFruitBuffer);
}

bool InGame::go() {
	mainMusic.play();
	while(window->isOpen()) {
		sf::Event event;
		while(window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			
			if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return) && !isLost) {
				isPaused = !isPaused;
			}
			
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
				direction = Direction::right;
			}
			
			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
				direction = Direction::left;
			}
			
			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
				direction = Direction::up;
			}
			
			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
				direction = Direction::down;
			}
			
			if(isLost) {
				snake->reset();
				isLost = false;
			}
		}
		
		if (clock.getElapsedTime().asSeconds() > 0.1 && !isPaused) {
			snake->move(direction);
			clock.restart();
		}
		
		/**
		 * Spawn a fruit if necessary
		 **/
	
		if (!isLost)
		{
			if(mustSpawnFruit)
			{
				bool safe = true;
				
				// We make sure that it doesn't spawn on the snake
				do
				{
					fruitX = rand() % (800-30) + 30;
					fruitY = rand() % (600-30) + 30;
					for(auto it : snake->snake)
					{
						if(fruitX < it.x)
						{
							safe = false;
							break;
						}
						else 
						{
							safe = true;
						}
					}
				} while(safe != true);
				
				mustSpawnFruit = false;
			}
		}
		
		fruit->spawn(fruitX, fruitY);
		snake->spawn();
		
		//if(snake->snake.front().x >= window->getSize().x || snake->snake.front().x < 0 || snake->snake.front().y >= window->getSize().y || snake->snake.front().y < 0) {
		if(snake->snake.front().x >= 800 || snake->snake.front().y >= 600) {
			snake->flip(direction);
		}
		
		// Check if the snake intersects with fruit
		if(fruit->rect.getGlobalBounds().intersects(snake->rect.front().getGlobalBounds())) {
			eatFruitSound.play();
			mustSpawnFruit = true;
			snake->grow();
		}
		
		// Check if the snake hits itself
		auto it = snake->snake.begin();
		it++;
		for(it; it != snake->snake.end(); ++it) {
			if(snake->snake.front().x == it->x && snake->snake.front().y == it->y) {
				isLost = true;
			}
		}
		
		window->clear();
		fruit->draw();
		snake->draw();
		
		if (isPaused && !isLost) {
			sf::Image oldScreen = window->capture();
			sf::Texture oldTex;
			oldTex.loadFromImage(oldScreen);
			sf::Sprite oldScreenSprite;
			oldScreenSprite.setTexture(oldTex);

			float scaleX = window->getView().getSize().x / oldScreenSprite.getLocalBounds().width;
			float scaleY = window->getView().getSize().y / oldScreenSprite.getLocalBounds().height;

			oldScreenSprite.setPosition(window->mapPixelToCoords(sf::Vector2i(0,0)));
			oldScreenSprite.setScale(scaleX, scaleY);

			sf::RectangleShape overlay;
			overlay.setPosition(window->mapPixelToCoords(sf::Vector2i(0,0)));
			overlay.setSize(sf::Vector2f(window->getView().getSize().x, window->getView().getSize().y));
			overlay.setFillColor(sf::Color(0,0,0,130));
			window->draw(oldScreenSprite);
			window->draw(overlay);
			
			window->draw(pauseTxt);	
		}

		
		window->draw(scoreTxt);
		window->draw(speedTxt);
		//window->draw(system, sf::BlendAdd);
		
		window->display();
	}
	
	return true;
}
