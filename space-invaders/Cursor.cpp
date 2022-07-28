#include "Cursor.h"

Cursor::Cursor(
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : Object(texture, world, origin, scale, angle) {}

void Cursor::update(sf::RenderWindow & window)
{
	sf::Vector2f point = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	this->setPosition(point);
}