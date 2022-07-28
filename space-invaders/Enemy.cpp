#include "Enemy.h"

Enemy::Enemy() : Movable(), hp()
{}

Enemy::Enemy
(
	unsigned int hp,
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : Movable(texture, world, origin, scale, angle) 
{
	this->hp = hp;
	this->setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2);
}

void Enemy::checkBorders()
{
	sf::Vector2f position = this->getPosition();
	if (position.y >= heightBorder.y)
	{
		stopGame = true;
	}
	if (position.x - (this->getTexture()->getSize().x * this->getScale().x / 2.f) <= sideBorder.x || position.x + (this->getTexture()->getSize().x * this->getScale().x / 2.f) >= sideBorder.y)
	{
		bounce();
	}
}

void Enemy::damage()
{
	hp -= 1;
}

void Enemy::bounce()
{
	speed.x *= -1;
}

void Enemy::update()
{
	checkBorders();
	Movable::update();
}