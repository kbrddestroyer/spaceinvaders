#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(
	sf::Texture texture,
	sf::Texture texture_alt,
	sf::Vector2f sideBorder,
	sf::Vector2f heightBorder,
	float DEFAULT_SCALE,
	unsigned int W_WIDTH
) : texture(texture), texture_alt(texture_alt), sideBorder(sideBorder), heightBorder(heightBorder), DEFAULT_SCALE(DEFAULT_SCALE), W_WIDTH(W_WIDTH)
{
	lastUpdate = std::chrono::system_clock::now();
}

void EnemySpawner::update()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - lastUpdate;
	lastUpdate = now;

	tick += elapsed_seconds.count();
	if (tick >= SPAWN_TIME)
	{
		tick = 0;
		unsigned int minPos = texture.getSize().x * DEFAULT_SCALE / 2.f;
		unsigned int maxPos = W_WIDTH - minPos;
		unsigned int hp = rand() % (ENEMY_MAX_HEALTH - ENEMY_MIN_HEALTH) + ENEMY_MIN_HEALTH;
		Enemy enemy(hp, (hp <= SPRITECHANGE_HP) ? texture : texture_alt, sf::Vector2f(rand() % (maxPos - minPos) + minPos, 0), sf::Vector2f{ texture.getSize().x / 2.f, texture.getSize().y / 2.f }, { DEFAULT_SCALE, DEFAULT_SCALE });
		enemy.setSideBorder(sideBorder);
		enemy.setHeightBorder(heightBorder);
		enemy.initSpeed((rand() % (ENEMY_MAX_SPEED - ENEMY_MIN_SPEED) + ENEMY_MIN_SPEED) * -1, (rand() % (ENEMY_MAX_ANGLE - ENEMY_MIN_ANGLE) + ENEMY_MIN_ANGLE) * (rand() % 2 ? -1 : 1));

		enemies.push_back(enemy);
	}
}
