#include "Bullet.h"

Bullet::Bullet
(
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : Movable(texture, world, origin, scale, angle) {}

bool Bullet::checkOutBorder()
{
	return 
		(
			this->getPosition().x - (this->getTexture()->getSize().x * this->getScale().x / 2.f) <= sideBorder.x ||
			this->getPosition().x + (this->getTexture()->getSize().x * this->getScale().x / 2.f) >= sideBorder.y ||
			this->getPosition().y - (this->getTexture()->getSize().y * this->getScale().y / 2.f) <= heightBorder.x
		) ? 
	true : false;
}