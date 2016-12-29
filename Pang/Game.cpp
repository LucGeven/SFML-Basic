#include "stdafx.h"
#include "Game.h"
#include "SpashScreen.h"
#include "MainMenu.h"

void Game::Start() {
	if (Game::_gameState != Uninitialized) return;

	Game::_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
	Game::_gameState = Game::ShowingSplash;

	while (!IsExiting()) {
		GameLoop();
	}
	Game::_mainWindow.close();
}

bool Game::IsExiting() {
	if (Game::_gameState == Exiting) return true;
	else return false;
}

void Game::GameLoop() {

	switch (Game::_gameState) {
	case Game::ShowingMenu: {
		ShowMenu();
		break;
	}
	case Game::ShowingSplash: {
		ShowSplashScreen();
		break;
	}
	case Game::Playing: {
		sf::Event currentEvent;
		while (Game::_mainWindow.pollEvent(currentEvent)) {
			_mainWindow.clear(sf::Color(255, 0, 0));
			_mainWindow.display();
			
			if (currentEvent.type == sf::Event::Closed) {
				Game::_gameState = Exiting;
			}
			if (currentEvent.type == sf::Event::KeyPressed) {
				if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
			}
		}
		break;
	}
	}
}

void Game::ShowSplashScreen() {
	SplashScreen splashScreen;
	splashScreen.show(Game::_mainWindow);
	Game::Game::_gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(Game::_mainWindow);
	switch (result) {
	case MainMenu::Exit: {
		Game::_gameState = Game::Exiting;
		break;
	}

	case MainMenu::Play: {
		Game::_gameState = Game::Playing;
		break;
	}

	}
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;

