#include "Layer.h"



Layer::Layer()
{
	if (!m_Cloud_Texture1.loadFromFile("Cloud.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Cloud_Texture1_Sprite = error_Sprite;
	}
	else
	{
		m_Cloud_Texture1.setSmooth(true);
		m_Cloud_Texture1_Sprite.setTexture(m_Cloud_Texture1);
		m_Cloud_Texture1_Sprite.setOrigin(static_cast<float>(m_Cloud_Texture1.getSize().x / 2), static_cast<float>(m_Cloud_Texture1.getSize().y / 2));

	}
	if (!m_Cloud_Texture2.loadFromFile("Cloud.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Cloud_Texture2_Sprite = error_Sprite;
	}
	else
	{
		m_Cloud_Texture2.setSmooth(true);
		m_Cloud_Texture2_Sprite.setTexture(m_Cloud_Texture2);
		m_Cloud_Texture2_Sprite.setOrigin(static_cast<float>(m_Cloud_Texture2.getSize().x / 2), static_cast<float>(m_Cloud_Texture2.getSize().y / 2));
		m_Cloud_Texture2_Sprite.setScale(.75, .75);
	}
	if (!m_Cloud_Texture3.loadFromFile("Cloud.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Cloud_Texture3_Sprite = error_Sprite;
	}
	else
	{
		m_Cloud_Texture3.setSmooth(true);
		m_Cloud_Texture3_Sprite.setTexture(m_Cloud_Texture3);
		m_Cloud_Texture3_Sprite.setOrigin(static_cast<float>(m_Cloud_Texture3.getSize().x / 2), static_cast<float>(m_Cloud_Texture3.getSize().y / 2));
		m_Cloud_Texture3_Sprite.setScale(.4f, .4f);
	}

	if (!m_Cloud_Texture4.loadFromFile("Cloud.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Cloud_Texture4_Sprite = error_Sprite;
	}
	else
	{
		m_Cloud_Texture4.setSmooth(true);
		m_Cloud_Texture4_Sprite.setTexture(m_Cloud_Texture4);
		m_Cloud_Texture4_Sprite.setOrigin(static_cast<float>(m_Cloud_Texture4.getSize().x / 2), static_cast<float>(m_Cloud_Texture4.getSize().y / 2));
		m_Cloud_Texture4_Sprite.setScale(.25, .25);
	}
	if (!m_Cloud_Texture5.loadFromFile("Cloud.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Cloud_Texture5_Sprite = error_Sprite;
	}
	else
	{
		m_Cloud_Texture5.setSmooth(true);
		m_Cloud_Texture5_Sprite.setTexture(m_Cloud_Texture5);
		m_Cloud_Texture5_Sprite.setOrigin(static_cast<float>(m_Cloud_Texture5.getSize().x / 2), static_cast<float>(m_Cloud_Texture5.getSize().y / 2));
		m_Cloud_Texture5_Sprite.setScale(.5, .5);
	}
	if (!m_Cloud_Texture6.loadFromFile("Cloud.jpg"))
	{
		sf::Sprite error_Sprite;
		error_Sprite.setColor(sf::Color::Magenta);
		m_Cloud_Texture6_Sprite = error_Sprite;
	}
	else
	{
		m_Cloud_Texture6.setSmooth(true);
		m_Cloud_Texture6_Sprite.setTexture(m_Cloud_Texture6);
		m_Cloud_Texture6_Sprite.setOrigin(static_cast<float>(m_Cloud_Texture6.getSize().x / 2), static_cast<float>(m_Cloud_Texture6.getSize().y / 2));

	}

}

void Layer::Layer_Manager(Player& player1, sf::RenderWindow& window, vector<Enemies*>& Enemies1)
{
    for (int i = 0; i < player1.bullets.size(); i++)
    {
		if (player1.bullets[i]->m_Current_Level == 3)
		{
			player1.bullets[i]->Update_Bullets(player1.bullets, window, i);
		}
    }

    if (player1.m_Current_Level == 3)
    {
        window.draw(player1.m_Sprite);
        //window.draw(player1.m_Hit_Box);
    }

    for ( int i = static_cast<int>(Enemies1.size() - 1); i >= 0; i--)
    {
        if (Enemies1[i]->m_Current_Level == 3)
        {
            Enemies1[i]->Update(Enemies1, player1.bullets, player1, window,i);
        }
    }
	window.draw(m_Cloud_Texture3_Sprite);
	window.draw(m_Cloud_Texture4_Sprite);
    if (player1.m_Current_Level == 2)
    {
        window.draw(player1.m_Sprite);
        //window.draw(player1.m_Hit_Box);
    }
	for (int i = 0; i < player1.bullets.size(); i++)
	{
		if (player1.bullets[i]->m_Current_Level == 2)
		{
			player1.bullets[i]->Update_Bullets(player1.bullets, window, i);
		}
	}
    for ( int i = static_cast<int>(Enemies1.size() - 1); i >= 0; i--)
    {
        if (Enemies1[i]->m_Current_Level == 2)
        {
            Enemies1[i]->Update(Enemies1, player1.bullets, player1, window, i);
        }
    }
    window.draw(m_Cloud_Texture2_Sprite);
	window.draw(m_Cloud_Texture5_Sprite);
    if (player1.m_Current_Level == 1)
    {
        window.draw(player1.m_Sprite);
        //window.draw(player1.m_Hit_Box);
    }
	for (int i = 0; i < player1.bullets.size(); i++)
	{
		if (player1.bullets[i]->m_Current_Level == 1)
		{
			player1.bullets[i]->Update_Bullets(player1.bullets, window, i);
		}
	}
    for (int i = static_cast<int>(Enemies1.size() - 1); i >= 0; i--)
    {
        if (Enemies1[i]->m_Current_Level == 1)
        {
            Enemies1[i]->Update(Enemies1, player1.bullets, player1, window, i);
        }
    }

	window.draw(m_Cloud_Texture1_Sprite);
	window.draw(m_Cloud_Texture6_Sprite);

}