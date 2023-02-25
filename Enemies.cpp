#include "Enemies.h"
#include "Bullet.h"
#include "Player.h"


Enemies::Enemies()
{
	if (!m_Texture.loadFromFile("Kitava.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Sprite = error_Sprite;
	}
	else
	{
		m_Texture.setSmooth(true);
		m_Sprite.setTexture(m_Texture);
		m_Sprite = sf::Sprite(m_Texture);
		m_Sprite.scale(.75, .75);
		m_Sprite.setOrigin(m_Texture.getSize().x / static_cast<float>(2), m_Texture.getSize().y / 2.f);
		m_Hitbox = sf::RectangleShape(sf::Vector2f(100, 100));
		m_Hitbox.setOrigin(m_Hitbox.getSize().x / 2, m_Hitbox.getSize().y / 2);
		m_Hitbox.setFillColor(sf::Color::Cyan);

	}
}
void Enemies::Enemy_Shoot( Player& player1)
{
	if (player1.m_Current_Level == m_Current_Level)
	{
		Bullet* new_Proj = new Bullet(true);
		new_Proj->m_Sprite.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y - 20);
		sf::Vector2f mousePositionFloat = sf::Vector2f(player1.m_Hit_Box.getPosition().x, player1.m_Hit_Box.getPosition().y);
		new_Proj->m_Direction = mousePositionFloat - new_Proj->m_Sprite.getPosition();
		new_Proj->m_Magnitude = sqrt((new_Proj->m_Direction.x * new_Proj->m_Direction.x + new_Proj->m_Direction.y * new_Proj->m_Direction.y));
		new_Proj->m_Direction.x = new_Proj->m_Direction.x / new_Proj->m_Magnitude;
		new_Proj->m_Direction.y = new_Proj->m_Direction.y / new_Proj->m_Magnitude;
		new_Proj->m_Sprite.setRotation(m_Sprite.getRotation() + 90);
		new_Proj->m_Hitbox.setRotation(m_Sprite.getRotation());
		new_Proj->m_Current_Level = m_Current_Level;
		bullets.push_back(new_Proj);
	}
}




void Enemies::Enemy_Move(Player& player1)
{
	int speed = 4;
	m_Direction = player1.m_Sprite.getPosition() - m_Sprite.getPosition();
	m_Magnitude = sqrt((m_Direction.x * m_Direction.x + m_Direction.y * m_Direction.y));
	m_Direction.x = m_Direction.x / m_Magnitude;
	m_Direction.y = m_Direction.y / m_Magnitude;

	m_Sprite.move(m_Direction.x * speed, m_Direction.y * speed);
}
void Enemies::Enemy_Move(sf::RenderWindow& window)
{

	int speed = 4;
	if (m_Direction_CD.getElapsedTime().asSeconds() >= 2)
	{
		m_Direction = sf::Vector2f(static_cast<float>(rand() % window.getSize().x), static_cast<float>(rand() % window.getSize().y)) - m_Sprite.getPosition();
		m_Direction_CD.restart();
	}
	if (m_Sprite.getPosition().x < 0 || m_Sprite.getPosition().x > window.getSize().x || m_Sprite.getPosition().y<0 || m_Sprite.getPosition().y > window.getSize().y)
	{
		m_Direction = sf::Vector2f(600,600) - m_Sprite.getPosition();
	}
	
	m_Magnitude = sqrt((m_Direction.x * m_Direction.x + m_Direction.y * m_Direction.y));
	m_Direction.x = m_Direction.x / m_Magnitude;
	m_Direction.y = m_Direction.y / m_Magnitude;

	m_Sprite.move(m_Direction.x * speed, m_Direction.y * speed);
}

void Enemies::Update(vector<Enemies*>& m_Enemies,vector<Bullet*>& player_Bullets, Player& player1, sf::RenderWindow& window, int j)
{
	//m_Hitbox.setPosition(m_Sprite.getPosition());
	if (player_Bullets.size() != 0 && m_Enemies.size() != 0)
	{
			for (int k = static_cast<int>(player_Bullets.size() - 1); k >= 0; k--)
			{
				if (player_Bullets[k]->m_Hitbox.getGlobalBounds().intersects(m_Hitbox.getGlobalBounds()) && player_Bullets[k]->m_Current_Level == m_Current_Level)
				{
					m_Is_Dead = true;
					player_Bullets[k]->m_Is_Dead = true;
				}
			}
			
	}
	for (int i = static_cast<int>(m_Enemies.size() - 1); i >= 0; i--)
	{
		if (m_Enemies[i]->m_Is_Dead == true)
		{

			m_Enemies[i] = nullptr;
			delete m_Enemies[i];
			m_Enemies.erase(m_Enemies.begin() + i);
		}	
	}
	if (j < m_Enemies.size())
	{
		if (m_Enemies[j]->m_Sprite.getPosition() != player1.m_Sprite.getPosition() && player1.m_Current_Level == m_Current_Level || m_Seen_Player == true)
		{
			m_Enemies[j]->Enemy_Move(player1);
			m_Enemies[j]->m_Seen_Player = true;
		}
		else
		{
			m_Enemies[j]->Enemy_Move(window);
		}
		window.draw(m_Enemies[j]->m_Sprite);
	}

	//window.draw(m_Enemies[i]->m_Hitbox);

	for (int i = static_cast<int>(bullets.size() - 1); i >= 0; i--)
	{
		bullets[i]->Update_Bullets(bullets, window, i);
		//window.draw(bullets[i]->m_Sprite);

	}

	if (m_Current_Level == 1)
	{
		m_Hitbox.setSize(sf::Vector2f(100, 100));
		m_Hitbox.setPosition(m_Sprite.getPosition());
		m_Sprite.setScale(.75, .75);
	}
	else if (m_Current_Level == 2)
	{
		m_Hitbox.setSize(sf::Vector2f(sf::Vector2f(100/2, 100/2)));
		m_Hitbox.setPosition(m_Sprite.getPosition().x + 28, m_Sprite.getPosition().y + 28);
		m_Sprite.setScale(.75/2, .75/2);
	}
	else if (m_Current_Level == 3)
	{
		m_Hitbox.setSize(sf::Vector2f(sf::Vector2f(100/4, 100/4)));
		m_Hitbox.setPosition(m_Sprite.getPosition().x + 28, m_Sprite.getPosition().y + 28);
		m_Sprite.setScale(-.065f, .065f);
	}

	if (m_Shoot_CD.getElapsedTime().asSeconds() >= 1)
	{
		Enemy_Shoot(player1);
		m_Shoot_CD.restart();
	}

	if (m_Current_Level < player1.m_Current_Level && m_Level_Change_CD.getElapsedTime().asSeconds() >= 4)
	{
		m_Current_Level += 1;
		m_Level_Change_CD.restart();
	}
	if (m_Current_Level > player1.m_Current_Level && m_Level_Change_CD.getElapsedTime().asSeconds() >= 3)
	{
		m_Current_Level -= 1;
		m_Level_Change_CD.restart();
	}
	
}