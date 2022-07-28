/*
	Game's entry point goes here
	Main file where SFML rendering loop happens
	___________________________________________

	Main file of game engine
*/

/*******************************************************************************************************************************/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>
#include <string>
#include <vector>
#include <Windows.h>

#include "Bullet.h"
#include "Cursor.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Movable.h"
#include "Player.h"
#include "Timer.h"

#include "Settings.h"

// endgame function will be called when the game should be completely stopped / terminated
// usually it's "game over" state
void endgame(sf::RenderWindow& window, sf::Font font, unsigned int score)
{
	sf::Text text;
	char str[256] = "Game Over! Your score is ";
	char buffer[256];
	_itoa_s	(score, buffer, 10);
	strcat_s(str, buffer);

	text.setString			(str);
	text.setFont			(font);
	text.setFillColor		(sf::Color::White);
	text.setCharacterSize	(25);
	text.setOrigin			(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
	text.setPosition		(window.getView().getCenter());

	sf::Event event;
	while (!window.pollEvent(event) || event.type != sf::Event::KeyPressed)
	{
		window.clear();
		window.draw(text);
		window.display();
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	sf::RenderWindow window(sf::VideoMode(WND_WIDTH, WND_HEIGHT), "Space Invaders");
	window.setFramerateLimit(MAX_FRAMERATE);
	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);

	sf::Image icon;
	icon.loadFromFile("sprites\\Bomb.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// 1. Setup stage

	unsigned int	score = 0;
	sf::Event		event;
	sf::Font		font;				// Font for ingame captions
	sf::Text		text;
	sf::Text		timertext;
	// Textures
	sf::Texture		aim;				// Cursor texture
	sf::Texture		background;
	sf::Texture		cannon;
	sf::Texture		cannonball;
	sf::Texture		stand;				// Cannon stand
	sf::Texture		target;
	sf::Texture		target_alt;
	sf::Texture		timer_t;			// Timer label texture
	// Static, non-interactable sprites
	sf::Sprite		back;				// Background image
	sf::Sprite		standSprite;		// Cannon stand
	// Impact sound
	sf::SoundBuffer impactBuffer;		// Sound file will be loaded here
	sf::Sound		impact;				// sf::Sound uses buffer to play sounds
	
	aim.loadFromFile			("sprites\\Aim.png");
	background.loadFromFile		("sprites\\Background.png");
	cannon.loadFromFile			("sprites\\Cannon.png");
	cannonball.loadFromFile		("sprites\\Cannonball.png");
	stand.loadFromFile			("sprites\\stand.png");
	target.loadFromFile			("sprites\\Target.png");
	target_alt.loadFromFile		("sprites\\Bomb.png");
	timer_t.loadFromFile		("sprites\\Clock.png");
	impactBuffer.loadFromFile	("sounds\\impact.wav");
	
	aim.setSmooth				(true);
	timer_t.setSmooth			(true);

	impact.setBuffer			(impactBuffer);
	back.setTexture				(background);
	standSprite.setTexture		(stand);

	back.setScale				(sf::Vector2f{ (float) WND_WIDTH / background.getSize().x, (float) WND_HEIGHT / background.getSize().y });
	standSprite.setOrigin		(sf::Vector2f{ stand.getSize().x / 2.f, stand.getSize().y / 2.f });
	standSprite.setScale		(sf::Vector2f{ DEFAULT_SPRITE_SCALE, DEFAULT_SPRITE_SCALE });
	standSprite.setPosition		(sf::Vector2f{ WND_WIDTH / 2, WND_HEIGHT });

	if (!font.loadFromFile("res\\Roboto-Regular.ttf"))
	{
		MessageBox(NULL, L"Font was not found!", L"Error!", MB_OK);
	}
	text.setFont				(font);
	text.setString				("0");
	text.setCharacterSize		(FONT_SIZE);
	text.setFillColor			(sf::Color::White);
	text.setPosition			({ FONT_SIZE / 2, FONT_SIZE / 2 });
	char buffer[256];
	_itoa_s(TIMER_TIME, buffer, 10);
	timertext.setFont			(font);
	timertext.setString			(buffer);
	timertext.setCharacterSize	(FONT_SIZE);
	timertext.setFillColor		(sf::Color::White);
	Player player
	(
		cannon,														// Texture
		sf::Vector2f(WND_WIDTH / 2, WND_HEIGHT),					// Position
		sf::Vector2f(cannon.getSize().x / 2.f, cannon.getSize().y),	// Origin
		{ DEFAULT_SPRITE_SCALE, DEFAULT_SPRITE_SCALE }				// Scale
	);
	Cursor cursor
	(
		aim,														// Texture
		{ 0.f, 0.f },												// Position
		{ aim.getSize().x / 2.f, aim.getSize().y / 2.f }			// Origin
	);
	Timer timer
	(
		timer_t,													// Texture
		{ WND_WIDTH - WND_WIDTH / 4.f, timer_t.getSize().y * DEFAULT_SPRITE_SCALE / 2.f + 10 }, // Position
		{ timer_t.getSize().x / 2.f, timer_t.getSize().y / 2.f },	// Origin
		{ DEFAULT_SPRITE_SCALE, DEFAULT_SPRITE_SCALE }				// Scale
	);
	EnemySpawner spawner
	(
		target,		
		target_alt,													// Child's texture
		sf::Vector2f{ 0, WND_WIDTH },								// Side border
		sf::Vector2f{ 0, WND_HEIGHT },								// Updown border
		DEFAULT_SPRITE_SCALE,										// Scale
		WND_WIDTH													// Spawn area 
	);
	timertext.setPosition({ WND_WIDTH - WND_WIDTH / 4.f + timer_t.getSize().x * timer.getScale().x, FONT_SIZE / 2 });
	std::vector<Bullet> allBullets;									// Pool of bullets on scene
	timer.setTimer(TIMER_TIME);										// Setup timer
	
	/***********************************************************************************************************************/

	// 2. Main loop stage

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			player.lookAt(mousePos);

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				allBullets.push_back(player.Shoot(cannonball));
				window.setMouseCursorVisible(false);
				window.setMouseCursorGrabbed(true);
			}
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.setMouseCursorVisible(true);
					window.setMouseCursorGrabbed(false);
				}
			}
		}

		// 3. Rendering stage

		window.clear();
		window.draw(back);							// 1st layer - background
		window.draw(standSprite);
		window.draw(player);						// 2nd layer - player
		
		spawner.update();							// Update spawner status
		cursor.update(window);						// Update cursor position

		std::vector<unsigned int> removeEnemiesID;	// Enemies to remove
		std::vector<unsigned int> removeBulletsID;	// Bullets to remove

		for (unsigned int i = 0; i < spawner.enemies.size(); i++)
		{
			Enemy& enemy = spawner.enemies[i];
			enemy.update();							// Update current enemy status
			window.draw(enemy);						// Rendering enemies

			if (enemy.stop())						// If any got to the end
			{
				endgame(window, font, score);		// Stop the game

				spawner.enemies.clear();
				allBullets.clear();
				removeBulletsID.clear();
				removeEnemiesID.clear();			// Clear all containers

				score = 0;							// Remove score
				timer.setTimer(TIMER_TIME);			// Reset timer
				char buffer[256];	
				_itoa_s(TIMER_TIME, buffer, 10);
				timertext.setString(buffer);		// Reset timer label
				break;
			}
		}

		for (unsigned int i = 0; i < allBullets.size(); i++)
		{
			Bullet& bullet = allBullets[i];
			bullet.update();						// Update bullet status
			window.draw(bullet);					// Rendering bullets

			if (std::find(removeBulletsID.begin(), removeBulletsID.end(), i) != removeBulletsID.end()) continue;
				// <- If any is in removal queue - skip the calculations for remove

			if (bullet.checkOutBorder())
				removeBulletsID.push_back(i);		// Remove bullets that are out of borders
			for (unsigned int j = 0; j < spawner.enemies.size(); j++)
			{
				Enemy& enemy = spawner.enemies[j];	
				if (std::find(removeEnemiesID.begin(), removeEnemiesID.end(), j) != removeEnemiesID.end()) continue;
					// <- If any is in removal queue - skip the calculations for remove
				if ((fabs(enemy.getPosition().x - bullet.getPosition().x) <
					(enemy.getTexture()->getSize().x * enemy.getScale().x + bullet.getTexture()->getSize().x * bullet.getScale().x) / 2.f) &&
					(fabs(enemy.getPosition().y - bullet.getPosition().y) <
						(enemy.getTexture()->getSize().y * enemy.getScale().y + bullet.getTexture()->getSize().y * bullet.getScale().y) / 2.f))
				
					/*
					
							( Sprite 1 )
							     | ( Sptire 2 )
					origin1 ---> |      | <------ origin2
								 <------> - Distance between two origin point
					
					If distance is less or equal to summ. (both x and y axis) of two halfs of sprites - got a collision
					*/
				
				{
					enemy.damage();						// Damage on collision
					if (enemy.getHP() <= 0)
					{
						removeEnemiesID.push_back(j);	// Add in removal queue
						impact.play();
					}
					removeBulletsID.push_back(i);		// Add bullet in removal queue
				}
			}
		}

		for (unsigned int bulletID : removeBulletsID)
			if (bulletID < allBullets.size())
				allBullets.erase(allBullets.begin() + bulletID);	// Remove any, that should be removed
		for (unsigned int enemyID : removeEnemiesID)
			if (enemyID < spawner.enemies.size())
			{
				spawner.enemies.erase(spawner.enemies.begin() + enemyID);
				score++;											// For every enemy add points to score
				char buffer[256];
				_itoa_s(score, buffer, 10);
				text.setString(buffer);								// Update label
			}

		removeEnemiesID.clear();
		removeBulletsID.clear();

		window.draw(cursor);

		if (!timer.update(timertext))			// If time is out
		{
			endgame(window, font, score);		// End the game

			spawner.enemies.clear();
			allBullets.clear();
			removeBulletsID.clear();
			removeEnemiesID.clear();

			score = 0;
			timer.setTimer(TIMER_TIME);
			char buffer[256];
			_itoa_s(TIMER_TIME, buffer, 10);
			timertext.setString(buffer);
		}

		window.draw(timer);						// Render timer
		window.draw(text);						// Render UI
		window.draw(timertext);
		window.display();
	}

	return 0;
}