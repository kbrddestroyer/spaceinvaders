#pragma once
#include "Movable.h"

/*
	Enemy. Target for player. Has health points and very hit by Bullet decrements hp.

	Inherits Movable interface

	Drawable, Movable, Interactive
*/

class Enemy :
    public Movable
{
private:
	bool stopGame = false;

	unsigned int hp;
public:
	Enemy();

	Enemy(
		unsigned int hp,
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);

	unsigned int getHP() { return hp; }
	bool		 stop()	 { return stopGame; }
	
	void damage();
	void checkBorders();
	void bounce();

	void update() override;
};
