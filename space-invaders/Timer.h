#pragma once
#include <chrono>
#include <ctime>
#include "Object.h"

/*
	Timer object. Sets up with number of seconds to work. 
	When time expires, update() function return false

	Inherits Object to be drawable

	Drawable (label). Controller
*/

class Timer :
    public Object
{
private:
	sf::Text		count;
	sf::SoundBuffer sb;
	sf::Sound		alarm;
	int				seconds;
	double			tick = 0;

	std::chrono::time_point<std::chrono::system_clock>	lastUpdate;
public:
	Timer() : Object(), seconds(), lastUpdate() {}

	Timer(
		sf::Texture& texture,
		sf::Vector2f world = { 0, 0 },
		sf::Vector2f origin = { 0, 0 },
		sf::Vector2f scale = { 1, 1 },
		float angle = 0.f
	);

	void setTimer(unsigned int seconds) { this->seconds = seconds; }
	unsigned int getSeconds() { return this->seconds; }
	bool update(sf::Text&);
};

