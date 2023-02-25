#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Enemies.h"



using namespace std;

class Bullet
{
public:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	sf::Vector2f m_Direction;
	sf::CircleShape m_Hitbox;
	bool m_Is_Dead = false;
	bool m_Is_Enemy_Proj = false;
	float m_velocityX = 0;
	float m_velocityY = 0;
	float m_accelerationX = 0;
	float m_accelerationY = 0;
	float m_Magnitude = 0;
	int m_Current_Level = 1;
	Bullet(bool is_Enemy);
	void Move_Bullet();
	void Update_Bullets(vector<Bullet*>& bullet_Position, sf::RenderWindow& window, int i);

};


