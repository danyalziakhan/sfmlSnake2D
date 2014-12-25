#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <TGUI/TGUI.hpp>

enum CallBackId : unsigned int {
	Start=1,
	Options,
	Exit,
	Back,
	SFXCheck,
	MusicCheck,
	FullScreenCheck
};

class Menu {
	public:
		Menu(std::shared_ptr<sf::RenderWindow> window);
		bool go();
	private:
		void loadMainMenu(tgui::Gui& gui);
		void loadOptions(tgui::Gui& gui);
		std::shared_ptr<sf::RenderWindow> window;
		tgui::Gui gui;
		tgui::Checkbox::Ptr sfxCheck;
		tgui::Checkbox::Ptr musicCheck;
		tgui::Checkbox::Ptr fullscreenCheck;
		
		std::string configFile = "data/Black.conf";
		std::string backgroundImagePath = "data/xubuntu_bg_aluminium.jpg";
		std::string textFont = "data/font/sansation.ttf";
};
