#include "Player.h"
#include "Bullet.h"


Player::Player()
{

	if (!m_Texture.loadFromFile("Poggers.jpg"))
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
		m_Sprite.scale(-.25, .25);
		m_Sprite.setOrigin(static_cast<float>(m_Texture.getSize().x / 2), static_cast<float>(m_Texture.getSize().y / 2));
		m_Hit_Box = sf::RectangleShape(sf::Vector2f(75, 75));
		m_Hit_Box.setOrigin(37.5, 37.5);
	}
}

void Player::Move()
{
    float speed = 4;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y - speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x, m_Sprite.getPosition().y + speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x - speed, m_Sprite.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_Sprite.setPosition(m_Sprite.getPosition().x + speed, m_Sprite.getPosition().y);
    }

}

void Player::look_At_Mouse(sf::RenderWindow& win) {
	sf::Vector2f curPos = m_Sprite.getPosition();
	sf::Vector2i position = sf::Mouse::getPosition(win);


	const float PI = 3.14159265f;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	m_Sprite.setRotation(rotation + 180);
}

void Player::Player_Shoot(sf::RenderWindow& window)
{
	Bullet* new_Proj = new Bullet(false);
	new_Proj->m_Sprite.setPosition(m_Sprite.getPosition());
	sf::Vector2f mousePositionFloat = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	new_Proj->m_Direction = mousePositionFloat - new_Proj->m_Sprite.getPosition();
	new_Proj->m_Magnitude = sqrt((new_Proj->m_Direction.x * new_Proj->m_Direction.x + new_Proj->m_Direction.y * new_Proj->m_Direction.y));
	new_Proj->m_Direction.x = new_Proj->m_Direction.x / new_Proj->m_Magnitude;
	new_Proj->m_Direction.y = new_Proj->m_Direction.y / new_Proj->m_Magnitude;
	new_Proj->m_Sprite.setRotation(m_Sprite.getRotation()+90);
	new_Proj->m_Hitbox.setRotation(m_Sprite.getRotation());
	new_Proj->m_Current_Level = m_Current_Level;
	bullets.push_back(new_Proj);
}

void Player::Update(sf::RenderWindow& window, vector<Enemies*> enemies1, bool& game_Over)
{
	sf::Font font;
	font.loadFromFile("times.ttf");
	sf::Text game_Over_Text;
	game_Over_Text.setFont(font);
	game_Over_Text.setString("GAME OVER");
	game_Over_Text.setFillColor(sf::Color::Red);
	game_Over_Text.setCharacterSize(120);
	game_Over_Text.setPosition(static_cast<float>(window.getSize().x / 6), static_cast<float>(window.getSize().y / 3));


	if (m_Current_Level == 1)
	{

		m_Hit_Box.setSize(sf::Vector2f(75, 75));
		m_Hit_Box.setPosition(m_Sprite.getPosition());
		m_Sprite.setScale(-.25, .25);
	}
	else if (m_Current_Level == 2)
	{
		m_Hit_Box.setSize(sf::Vector2f(37.5, 37.5));
		m_Hit_Box.setPosition(m_Sprite.getPosition().x + 18, m_Sprite.getPosition().y + 18);
		m_Sprite.setScale(-.125, .125);
	}
	else if (m_Current_Level == 3)
	{
		m_Hit_Box.setSize(sf::Vector2f(18.75, 18.75));
		m_Hit_Box.setPosition(m_Sprite.getPosition().x + 28, m_Sprite.getPosition().y + 28);
		m_Sprite.setScale(-.065f, .065f);
	}


	for (int i = static_cast<int>(enemies1.size() - 1); i >= 0; i--)
	{
		for (int j = static_cast<int>(enemies1[i]->bullets.size() - 1); j >= 0; j--)
		{
			if (enemies1[i]->bullets[j]->m_Hitbox.getGlobalBounds().intersects(m_Hit_Box.getGlobalBounds()) && enemies1[i]->bullets[j]->m_Current_Level == m_Current_Level)
			{
				m_Health -= 1;
				enemies1[i]->bullets[j]->m_Is_Dead = true;
			}
		}
	}
	if (m_Health <= 0)
	{
		window.draw(game_Over_Text);
		game_Over = true;
	}
}