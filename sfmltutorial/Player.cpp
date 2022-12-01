#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2u windowSize) : animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	//printf("%i, %i", windowSize.x / 2, windowSize.y / 2); // prints correctly
	body.setSize(sf::Vector2f(90.0f, 132.0f)); // want size dependant on picture size
	body.setPosition(150.0f, 125.0f); // want position dependant on window size
	// body.setPosition(static_cast <float> (windowSize.x / 2), static_cast <float> (windowSize.y / 2)); // want position dependent on window, center of window
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);

	/*
	sf::Vector2u playerTextureSize = texture.getSize();
	sf::Vector2u windowSize = window.getSize();
	sf::RectangleShape player(sf::Vector2f(static_cast <float> (playerTextureSize.x / PLAYER_TEXTURE_COLUMNS),
		static_cast <float> (playerTextureSize.y / PLAYER_TEXTURE_ROWS)));
	player.setOrigin(sf::Vector2f(static_cast <float> ((playerTextureSize.x / (PLAYER_TEXTURE_COLUMNS * 2))),
		static_cast <float> (playerTextureSize.y / (PLAYER_TEXTURE_ROWS * 2))));
	player.setPosition(windowSize.x / 2, windowSize.y / 2);
	player.setTexture(&playerTexture);
	*/
	
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		movement.x += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		movement.y += speed * deltaTime;
	}
	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (movement.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(body);
}
