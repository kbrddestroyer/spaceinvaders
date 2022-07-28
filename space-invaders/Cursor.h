#pragma once
#include "Object.h"

/*
	Cursor replacement. Locks to mouse position

	Ingerits Object interface

	Drawable, Interactive
*/

class Cursor :
    public Object
{
public:
    Cursor() : Object() {}

	Cursor(
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);

	void update(sf::RenderWindow&);
};

