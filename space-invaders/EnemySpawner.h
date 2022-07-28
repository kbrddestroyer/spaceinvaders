#pragma once
#include <vector>
#include <chrono>
#include <ctime>
#include "Enemy.h"
#include "Settings.h"

/*
	EnemySpawner creates Enemy objects in specific range and time.

	Controller
*/

class EnemySpawner
{
private:
	sf::Texture		texture;
	sf::Texture		texture_alt;
	sf::Vector2f	sideBorder;
	sf::Vector2f	heightBorder;
	float			DEFAULT_SCALE;
	unsigned int	W_WIDTH;
	double			tick = 0;

	std::chrono::time_point<std::chrono::system_clock>	lastUpdate;
public:
	std::vector<Enemy> enemies;
	
	EnemySpawner() : texture(), texture_alt(), sideBorder(), heightBorder(), DEFAULT_SCALE(1), W_WIDTH(), lastUpdate() {}
	
	EnemySpawner(
		sf::Texture texture,
		sf::Texture texture_alt,
		sf::Vector2f sideBorder = {0.f, 0.f},
		sf::Vector2f heightBorder = {0.f, 0.f},
		float DEFAULT_SCALE = 1.f,
		unsigned int W_WIDTH = 0
	);
	
	void update();
};

