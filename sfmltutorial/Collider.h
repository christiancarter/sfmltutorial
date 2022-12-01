#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
	public:
		Collider(sf::RectangleShape& body);
		~Collider();

		void Move(float dx, float dy) const
		{
			body.move(dx, dy);
		}

		bool CheckCollision(const Collider& other, float inertia); // added const
		sf::Vector2f GetPosition() const
		{
			return body.getPosition();
		}
		sf::Vector2f GetHalfSize() const
		{
			return body.getSize() / 2.0f;
		}
		Collider GetCollider()
		{
			return Collider(body);
		}
	private:
		sf::RectangleShape& body;
};