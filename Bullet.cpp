#include "Bullet.h"


Bullet::Bullet(bool is_Enemy)
{
	if (!is_Enemy)
	{
		if (!m_Texture.loadFromFile("bullet.jpg"))
		{
			sf::Sprite error_Sprite;
			error_Sprite.setColor(sf::Color::Magenta);
			m_Sprite = error_Sprite;
		}
		else
		{
			m_Texture.setSmooth(true);
			m_Sprite.setTexture(m_Texture);
			m_Sprite.scale(.05f, .05f);
			m_Sprite.setOrigin(static_cast<float>(m_Texture.getSize().x / 2), static_cast<float>(m_Texture.getSize().y / 2.f));
			m_Sprite.setRotation(90);
			m_Hitbox.setFillColor(sf::Color::Red);
			m_Hitbox.setRadius(14);
			m_Hitbox.setOrigin(7, 7);
			m_Hitbox.setScale(3, 1);
		}
	}
	else
	{
		if (!m_Texture.loadFromFile("Fireball.jpg"))
		{
			sf::Sprite error_Sprite;
			error_Sprite.setColor(sf::Color::Magenta);
			m_Sprite = error_Sprite;
		}
		else
		{
			m_Texture.setSmooth(true);
			m_Sprite.setTexture(m_Texture);
			m_Sprite.scale(.2f, .2f);
			m_Sprite.setOrigin(static_cast<float>(m_Texture.getSize().x / 2), static_cast<float>(m_Texture.getSize().y / 2.f));
			m_Sprite.setRotation(90);
			m_Hitbox.setFillColor(sf::Color::Red);
			m_Hitbox.setOrigin(7, 7);
			m_Hitbox.setRadius(14);
			m_Is_Enemy_Proj = true;
		}
	}
}

void Bullet::Move_Bullet()
{
	m_Sprite.move(m_Direction.x * 16, m_Direction.y * 16);
}

void Bullet::Update_Bullets(vector<Bullet*>& bullet_Position, sf::RenderWindow& window, int i)
{
	if (bullet_Position[i]->m_Current_Level == 1 && !m_Is_Enemy_Proj)
	{
		m_Sprite.setScale(.05f, .05f);
		m_Hitbox.setRadius(14);
	}

	if (bullet_Position[i]->m_Current_Level == 2 && !m_Is_Enemy_Proj)
	{
		m_Sprite.setScale(.025f, .025f);
		m_Hitbox.setRadius(7);
	}

	if (bullet_Position[i]->m_Current_Level == 3 && !m_Is_Enemy_Proj)
	{
		m_Sprite.setScale(.0125f, .0125f);
		m_Hitbox.setRadius(3.5);
	}

	if (bullet_Position[i]->m_Current_Level == 1 && m_Is_Enemy_Proj)
	{
		m_Sprite.setScale(.2f, .2f);
		m_Hitbox.setRadius(14);
	}

	if (bullet_Position[i]->m_Current_Level == 2 && m_Is_Enemy_Proj)
	{
		m_Sprite.setScale(.2f / 2, .2f / 2);
		m_Hitbox.setRadius(7);
	}

	if (bullet_Position[i]->m_Current_Level == 3 && m_Is_Enemy_Proj)
	{
		m_Sprite.setScale(.2f / 4, .2f / 4);
		m_Hitbox.setRadius(3.5);
		m_Current_Level = 3;
	}

		
	if (bullet_Position[i]->m_Sprite.getPosition().x < 0 || bullet_Position[i]->m_Sprite.getPosition().x > window.getSize().x || bullet_Position[i]->m_Sprite.getPosition().y < 0 || bullet_Position[i]->m_Sprite.getPosition().y > window.getSize().y || bullet_Position[i]->m_Is_Dead)
	{
		bullet_Position[i] = nullptr;
		delete bullet_Position[i];
		bullet_Position.erase(bullet_Position.begin() + i);

	}
	else
	{
		bullet_Position[i]->Move_Bullet();

		bullet_Position[i]->m_Hitbox.setPosition(bullet_Position[i]->m_Sprite.getPosition().x, bullet_Position[i]->m_Sprite.getPosition().y);

		window.draw(bullet_Position[i]->m_Sprite);
		//window.draw(bullet_Position[i]->m_Hitbox);
	}

}