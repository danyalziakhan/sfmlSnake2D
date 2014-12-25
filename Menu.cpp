#include "Menu.hpp"

void Menu::loadMainMenu(tgui::Gui& gui) {
	gui.removeAllWidgets();
	
    // Create the background image
    tgui::Picture::Ptr picture(gui);
    picture->load(backgroundImagePath);

    // Create the username label
    tgui::Label::Ptr labelUsername(gui);
    labelUsername->setText("Snake2D");
    labelUsername->setPosition(250, 50);
	labelUsername->setTextSize(70);
	
    // Create the start button
    tgui::Button::Ptr button(gui);
    button->load(configFile);
    button->setSize(260, 60);
    button->setPosition(270, 200);
    button->setText("Start Game");
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setCallbackId(CallBackId::Start);
    
    tgui::Button::Ptr optionsButton(gui);
    optionsButton->load(configFile);
    optionsButton->setSize(260, 60);
    optionsButton->setPosition(270, 300);
    optionsButton->setText("Options");
    optionsButton->bindCallback(tgui::Button::LeftMouseClicked);
    optionsButton->setCallbackId(CallBackId::Options);
    
    tgui::Button::Ptr exitButton(gui);
    exitButton->load(configFile);
    exitButton->setSize(260, 60);
    exitButton->setPosition(270, 400);
    exitButton->setText("Exit");
    exitButton->bindCallback(tgui::Button::LeftMouseClicked);
    exitButton->setCallbackId(CallBackId::Exit);
}

void Menu::loadOptions(tgui::Gui& gui) {
	gui.removeAllWidgets();
	
	// Create the background image
    tgui::Picture::Ptr picture(gui);
    picture->load(backgroundImagePath);

    // Create the username label
    tgui::Label::Ptr labelUsername(gui);
    labelUsername->setText("Options");
    labelUsername->setPosition(250, 50);
	labelUsername->setTextSize(70);
	
	sfxCheck = tgui::Checkbox::Ptr(gui);
	sfxCheck->load(configFile);
	sfxCheck->setText("SFX");
	sfxCheck->setTextColor(sf::Color::Red);
	sfxCheck->setPosition(270, 200);
	sfxCheck->check();
	sfxCheck->bindCallback(tgui::Button::LeftMouseClicked);
    sfxCheck->setCallbackId(CallBackId::SFXCheck);
    
	musicCheck = tgui::Checkbox::Ptr(gui);
	musicCheck->load(configFile);
	musicCheck->setText("Music");
	musicCheck->setTextColor(sf::Color::Red);
	musicCheck->setPosition(270, 300);
	musicCheck->check();
	musicCheck->bindCallback(tgui::Button::LeftMouseClicked);
    musicCheck->setCallbackId(CallBackId::MusicCheck);
    
	fullscreenCheck = tgui::Checkbox::Ptr(gui);
	fullscreenCheck->load(configFile);
	fullscreenCheck->setText("FullScreen");
	fullscreenCheck->setTextColor(sf::Color::Red);
	fullscreenCheck->setPosition(270, 400);
	fullscreenCheck->check();
	fullscreenCheck->bindCallback(tgui::Button::LeftMouseClicked);
    fullscreenCheck->setCallbackId(CallBackId::FullScreenCheck);
    
    // Create the start button
    tgui::Button::Ptr backButton(gui);
    backButton->load(configFile);
    backButton->setSize(260, 60);
    backButton->setPosition(270, 500);
    backButton->setText("Back");
    backButton->bindCallback(tgui::Button::LeftMouseClicked);
    backButton->setCallbackId(CallBackId::Back);
}

Menu::Menu(std::shared_ptr<sf::RenderWindow> window) {
	this->window = window;
	gui.setWindow(*this->window.get());
	
	// Load the font (you should check the return value to make sure that it is loaded)
    gui.setGlobalFont(textFont);
	loadMainMenu(gui);
}

bool Menu::go() {
	while(window->isOpen()) {
		sf::Event event;
		while(window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
			
			if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return)) {
				return false;
			}
			
			// Pass the event to all the widgets
            gui.handleEvent(event);
		}
        
        // The callback loop
        tgui::Callback callback;
        while (gui.pollCallback(callback)) {
            // Make sure tha callback comes from the button
            if (callback.id == CallBackId::Start) {
                return false; // run the game
            }
            
            if (callback.id == CallBackId::Options) {
                loadOptions(gui);
            }
            
            if (callback.id == CallBackId::Exit) {
                window->close();
            }
            
            if (callback.id == CallBackId::Back) {
                loadMainMenu(gui);
            }
            
            if (callback.id == CallBackId::SFXCheck) {
                if (sfxCheck->isChecked()) {
					sfxCheck->uncheck();
				}
				else {
					sfxCheck->check();
				}
            }
            
            if (callback.id == CallBackId::MusicCheck) {
				if (musicCheck->isChecked()) {
					musicCheck->uncheck();
				}
				else {
					musicCheck->check();
				}
            }
            
            if (callback.id == CallBackId::FullScreenCheck) {
                if (fullscreenCheck->isChecked()) {
					fullscreenCheck->uncheck();
				}
				else {
					fullscreenCheck->check();
				}
            }
        }
        
		window->clear();
		// Draw all created widgets
        gui.draw();
		window->display();
	}
	
	return true;
}
