#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Bullet;

using namespace std;

class Enemies
{

public:
	vector<Bullet*> bullets;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::RectangleShape m_Hitbox;
	bool m_Is_Dead = false;
	bool m_Seen_Player = false;
	sf::Vector2f m_Direction;
	float m_Magnitude;
	int m_Current_Level = 1;
	sf::Clock m_Shoot_CD;
	sf::Clock m_Level_Change_CD;
	sf::Clock m_Direction_CD;

	Enemies();
	void Update(vector<Enemies*>& m_Enemies,vector<Bullet*>& player_Bullets, Player& player1, sf::RenderWindow& window, int j);
	void Enemy_Shoot( Player& player1);
	void Enemy_Move(Player& player1);
	void Enemy_Move(sf::RenderWindow& window);
};

