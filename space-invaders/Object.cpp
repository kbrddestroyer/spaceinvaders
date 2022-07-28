#include "Object.h"

Object::Object
(
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : sf::Sprite()
{
	this->setTexture(texture);
	this->setScale(scale);
	this->setOrigin(origin);
	this->setPosition(world);
	this->setRotation(angle);
}