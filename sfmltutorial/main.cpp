#include "SFML\Graphics.hpp"
#include "Player.h"
#include <iostream>
#include "Platform.h"

static const float VIEW_HEIGHT = 480.0f;

int main();

void ResizeView(const sf::RenderWindow& window, sf::View& view);

int main()
{
	sf::Event e;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Test", sf::Style::Close | sf::Style::Resize);
	sf::CircleShape circle(100.0f);
	circle.setPosition(0, 0);
	circle.setFillColor(sf::Color::Yellow);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("greenlady.jpg");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	/*
		sf::RectangleShape player(sf::Vector2f(static_cast <float> (windowSize.x / 3), static_cast <float> (windowSize.y / 3)));
	*/

	/*
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
	*/

	sf::Vector2u windowSize = window.getSize();
	Player player(&playerTexture, sf::Vector2u(12, 3), 0.08f, 300.0f, sf::Vector2u(windowSize.x, windowSize.y));
	float deltaTime = 0.0f;
	sf::Clock clock;
	Platform platform1(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(200.0f, 300.0f));
	Platform platform2(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(200.0f, 0.0f));

	/*
	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 12;
	textureSize.y /= 3;
	player.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
	*/

	sf::Time elapsedTime = clock.getElapsedTime();
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		player.Update(deltaTime);

		platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		platform2.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		view.setCenter(player.GetPosition());
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					// printf("New window dimensions: %i, %i\n", e.size.width, e.size.height);
					ResizeView(window, view);
					break;
				case sf::Event::TextEntered:
					if (e.text.unicode < 128)
					{
						printf("%c", e.text.unicode);
					}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				/*
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				if (mousePos.x >= 0 && mousePos.x <= windowSize.x && mousePos.y >= 0 && mousePos.y <= windowSize.y)
				{
					player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				}
				*/
			}

		}
		//(windowSize.x)

		//circle.move(0.01f, 0.0f);
		window.clear(sf::Color(0, 0, 180));
		window.setView(view);
		window.draw(circle);
		player.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);
		window.display();
	}
	return 0;
}

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}