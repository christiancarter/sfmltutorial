#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) : body(body)
{
	;
}

Collider::~Collider()
{
	;
}

bool Collider::CheckCollision(const Collider& other, float inertia) // added const
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		inertia = std::min(std::max(inertia, 0.0f), 1.0f);

		if (abs(intersectX) > abs(intersectY))
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - inertia), 0.0f);
				other.Move(-intersectX * inertia, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - inertia), 0.0f);
				other.Move(intersectX * inertia, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - inertia));
				other.Move(0.0f, -intersectY * inertia);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - inertia));
				other.Move(0.0f, intersectY * inertia);
			}
		}
	}
	else
	{

	}
	return false;
}
