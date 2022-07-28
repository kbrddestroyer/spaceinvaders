#pragma once
#include <chrono>
#include <ctime>
#include "Object.h"

/*
	Objects, that need calculations for speed, etc.

	Defines interface, inherits Object class (and sf::Sprite)
	Defines moving patterns, does most of calculations

	Contains borders information

	Drawable, Movable
*/

class Movable :
    public Object
{
protected:
	sf::Vector2f sideBorder;		// min -> max
	sf::Vector2f heightBorder;		// min -> max
	sf::Vector2f speed;				// pixels per second

	std::chrono::time_point<std::chrono::system_clock>	lastUpdate;
public:
	Movable() : Object(), lastUpdate() {}

	Movable(
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);

	void setSideBorder(sf::Vector2f border) { this->sideBorder = border; }
	void setHeightBorder(sf::Vector2f border) { this->heightBorder = border; }

	void initSpeed(float, float);
	sf::Vector2f vspeedToCoordinates(float, float);

	virtual void update();
};

