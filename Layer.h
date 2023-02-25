#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Enemies.h"
#include "Bullet.h"
#include "Player.h"

class Layer
{
public:
	vector<Enemies*> m_Enemies;
	sf::Texture m_Cloud_Texture1;
	sf::Sprite m_Cloud_Texture1_Sprite;
	sf::Texture m_Cloud_Texture2;
	sf::Sprite m_Cloud_Texture2_Sprite;
	sf::Texture m_Cloud_Texture3;
	sf::Sprite m_Cloud_Texture3_Sprite;
	sf::Texture m_Cloud_Texture4;
	sf::Sprite m_Cloud_Texture4_Sprite;
	sf::Texture m_Cloud_Texture5;
	sf::Sprite m_Cloud_Texture5_Sprite;
	sf::Texture m_Cloud_Texture6;
	sf::Sprite m_Cloud_Texture6_Sprite;

	Layer();
	void Layer_Manager(Player& player1, sf::RenderWindow& window, vector<Enemies*>& Enemies1);
};

