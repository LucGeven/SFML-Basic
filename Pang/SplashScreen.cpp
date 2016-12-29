#include "stdafx.h"
#include "SpashScreen.h"

void SplashScreen::show(sf::RenderWindow & renderWindow) {
	sf::Texture texture;
	if (!texture.loadFromFile("res/images/splashscreen.png")) return;
	
	sf::Sprite sprite;
	sprite.setTexture(texture);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed) return;
		}
	}
}