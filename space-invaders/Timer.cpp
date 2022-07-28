#include "Timer.h"

Timer::Timer(
	sf::Texture& texture,
	sf::Vector2f world,
	sf::Vector2f origin,
	sf::Vector2f scale,
	float angle
) : Object(texture, world, origin, scale, angle), seconds()
{
	sb.loadFromFile("sounds\\alarm.wav");
	alarm.setBuffer(sb);

	lastUpdate = std::chrono::system_clock::now();
}

bool Timer::update(sf::Text& text)
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - lastUpdate;
	lastUpdate = now;
	
	tick += elapsed_seconds.count();
	if (tick >= 1)
	{
		tick = 0;
		seconds--;
		char buffer[256];
		_itoa_s(seconds, buffer, 10);
		text.setString(buffer);
	}
	if (seconds == 5) alarm.play();
	return (seconds > 0) ? true : false;
}