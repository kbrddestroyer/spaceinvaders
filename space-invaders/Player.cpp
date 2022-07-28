#include "Player.h"

Player::Player() : Object() {
	if (!sb.loadFromFile("sounds\\cannon.wav"))
	{
		MessageBox(NULL, L"Sound can not be loaded!", L"Error!", MB_OK);
	}
	shoot.setBuffer(sb);					// Sound setup
};

Player::Player
(
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : Object(texture, world, origin, scale, angle) {
	if (!sb.loadFromFile("sounds\\cannon.wav"))
	{
		MessageBox(NULL, L"Sound can not be loaded!", L"Error!", MB_OK);
	}
	shoot.setBuffer(sb);
}

Bullet& Player::Shoot(sf::Texture& cannonball)
{
	sf::Vector2f spawnpos(
		getPosition().x + sin(getRotation() * PI / 180) * getTexture()->getSize().y * getScale().y,
		getPosition().y - cos(getRotation() * PI / 180) * getTexture()->getSize().y * getScale().y
	);
	Bullet bullet(cannonball, spawnpos, sf::Vector2f{ cannonball.getSize().x / 2.f, cannonball.getSize().y / 2.f }, { DEFAULT_SPRITE_SCALE, DEFAULT_SPRITE_SCALE });
	bullet.setSideBorder(sf::Vector2f{ 0, (float) WND_WIDTH });
	bullet.setHeightBorder(sf::Vector2f{ 0, (float) WND_HEIGHT });
	bullet.initSpeed(BULLET_DEFAULT_SPEED, getRotation());
	shoot.play();
	return bullet;
}

void Player::lookAt(sf::Vector2f mousePos)
{
	float dx = mousePos.x - WND_WIDTH / 2;	// dinstance X
	float dy = WND_HEIGHT - mousePos.y;			// dinstance Y
	float angle = atan2(dx, dy) * 180 / PI;	// angle in RAD

	this->setRotation(angle);
}