#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
	sf::Event e;
	sf::RenderWindow w(sf::VideoMode(400, 400), "Test", sf::Style::Close | sf::Style::Resize);
	sf::CircleShape circle1(75.f);
	sf::CircleShape circle2(20.f);
	/*
		sf::RectangleShape player(sf::Vector2f(static_cast <float> (windowSize.x / 3), static_cast <float> (windowSize.y / 3)));
	*/
	sf::Texture playerTexture;
	playerTexture.loadFromFile("frisk.png");
	sf::Vector2u playerTextureSize = playerTexture.getSize();
	sf::RectangleShape player(sf::Vector2f(static_cast <float> (playerTextureSize.x / 4), static_cast <float> (playerTextureSize.y)));
	player.setOrigin(sf::Vector2f(static_cast <float> (playerTextureSize.x / 8), static_cast <float> (playerTextureSize.y / 2)));
	player.setTexture(&playerTexture);
	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 4;

	player.setTextureRect(sf::IntRect(0, 0, textureSize.x - 1, textureSize.y));

	circle1.setFillColor(sf::Color::Blue);
	circle2.setFillColor(sf::Color::Yellow);
	while (w.isOpen())
	{
		while (w.pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
					w.close();
					break;
				case sf::Event::Resized:
					/*
					std::cout << '(' << e.size.width << ", " << e.size.height << ')'
						<< '\n';
					*/
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
				player.move(-2.5f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				player.move(2.5f, 0.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				player.move(0.0f, -2.5f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				player.move(0.0f, 2.5f);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(w);
				player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			}

			w.clear();
			w.draw(circle1);
			w.draw(circle2);
			w.draw(player);
			w.display();
		}
	}
	return 0;
}