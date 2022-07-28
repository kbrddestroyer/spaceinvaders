#pragma once
#include "Object.h"
#include "Bullet.h"

/*
	Player class is controllable by user
	Inherits object
	Defines control behaviour
	Does angle calculation and bullet generation

	Drawable, Interactive
*/

class Player :
    virtual public Object
{
private:
	sf::SoundBuffer sb;
	sf::Sound shoot;
public:
	Player();

    Player(
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);

	Bullet& Shoot(sf::Texture&);
    void lookAt(sf::Vector2f);  // Face the direction on world point
};

