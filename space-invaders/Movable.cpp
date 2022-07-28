#include "Movable.h"

Movable::Movable
(
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : Object(texture, world, origin, scale, angle) {
	lastUpdate = std::chrono::system_clock::now();
}

sf::Vector2f Movable::vspeedToCoordinates(float speed, float angle)
{
	return sf::Vector2f{ speed * sin(angle), speed * cos(angle) };
}

void Movable::initSpeed(float speed, float angle)
{
	this->speed = vspeedToCoordinates(speed, angle * PI / 180);
}

void Movable::update()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - lastUpdate;
	lastUpdate = now;
	sf::Vector2f currentPosition = getPosition();
	currentPosition.x += speed.x * elapsed_seconds.count();
	currentPosition.y -= speed.y * elapsed_seconds.count();
	this->setPosition(currentPosition);
}