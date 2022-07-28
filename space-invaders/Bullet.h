#pragma once
#include "Movable.h"

/*
	Bullet class. Creates by Player class when shoot
	Destroys when hits the Enemy object
	Inherits Movable interfase

	Drawable, Movable
*/

class Bullet :
    public Movable
{
public:
	Bullet() : Movable() {}

	Bullet(
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);

	bool checkOutBorder();
};

