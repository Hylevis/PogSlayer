#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemies.h"

class Bullet;

using namespace std;

class Player
{

public:
	vector<Bullet*> bullets;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::RectangleShape m_Hit_Box;
	float m_velocityX = 4;
	float m_velocityY = 0;
	float m_accelerationX = 0;
	float m_accelerationY = 0;
	int m_Current_Level = 1;
	int m_Health = 5;

	Player();
	void Move();
	void look_At_Mouse(sf::RenderWindow& win);
	void Player_Shoot(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, vector<Enemies*> enemies1, bool& game_Over);
};

