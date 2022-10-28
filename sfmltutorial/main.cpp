#include "SFML\Graphics.hpp"
#include "Animation.h"
#include <iostream>

int main()
{
	sf::Event e;
	sf::RenderWindow w(sf::VideoMode(300, 300), "Test", sf::Style::Close | sf::Style::Resize);
	w.setVerticalSyncEnabled(true);
	sf::CircleShape circle(100.0f);
	circle.setPosition(0, -25);
	circle.setFillColor(sf::Color::Yellow);
	/*
		sf::RectangleShape player(sf::Vector2f(static_cast <float> (windowSize.x / 3), static_cast <float> (windowSize.y / 3)));
	*/
	sf::Texture playerTexture;
	playerTexture.loadFromFile("greenlady.jpg");
	const int PLAYER_TEXTURE_COLUMNS = 12, PLAYER_TEXTURE_ROWS = 3;
	sf::Vector2u playerTextureSize = playerTexture.getSize();
	sf::Vector2u windowSize = w.getSize();
	sf::RectangleShape player(sf::Vector2f(static_cast <float> (playerTextureSize.x / PLAYER_TEXTURE_COLUMNS),
		static_cast <float> (playerTextureSize.y / PLAYER_TEXTURE_ROWS)));
	player.setOrigin(sf::Vector2f(static_cast <float> ((playerTextureSize.x / (PLAYER_TEXTURE_COLUMNS * 2))), 
		static_cast <float> (playerTextureSize.y / (PLAYER_TEXTURE_ROWS * 2))));
	player.setPosition(windowSize.x / 2, windowSize.y / 2);
	player.setTexture(&playerTexture);

	Animation animation(&playerTexture, sf::Vector2u(PLAYER_TEXTURE_COLUMNS, PLAYER_TEXTURE_ROWS), 0.15f);
	float deltaTime = 0.0f;
	float totalTime = 0.0f;
	sf::Clock clock;

	/*
	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 3;
	player.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	*/

	sf::Time elapsedTime = clock.getElapsedTime();
	while (w.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		animation.Update(0, deltaTime);
		while (w.pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
					w.close();
					break;
				case sf::Event::Resized:
					printf("New window dimensions: %i, %i\n", e.size.width, e.size.height);
					break;
				case sf::Event::TextEntered:
					if (e.text.unicode < 128)
					{
						printf("%c", e.text.unicode);
					}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				player.move(-1.0f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				player.move(1.0f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				player.move(0.0f, -1.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				player.move(0.0f, 1.0f);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(w);
				if (mousePos.x >= 0 && mousePos.x <= windowSize.x && mousePos.y >= 0 && mousePos.y <= windowSize.y)
				{
					player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				}
			}

		}
		//(windowSize.x)

		circle.move(0.1f, -0.0f);
		// circle1.move(0.01f, -0.01f);
		player.setTextureRect(animation.uvRect);
		w.clear(sf::Color(0, 0, 180));
		w.draw(circle);
		w.draw(player);
		w.display();
	}
	return 0;
}