#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>
#include <string>

#include <cmath>
#include "Settings.h"
#define PI 3.141592653589

/*
	Basic object interface class
	Defines constructors and inherits sf::Sprite

	Drawable
*/

class Object : 
	public sf::Sprite
{
public:
	Object() : sf::Sprite() {}

	Object(
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);
};

