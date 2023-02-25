#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemies.h"
#include "Player.h"
#include "Enemies.h"
#include "Layer.h"

using namespace std;


void Spawn_Random_Enemy(vector<Enemies*>& Enemies1, sf::RenderWindow& window)
{
    Enemies* enemy1 = new Enemies;
    enemy1->m_Current_Level = rand() % 3 + 1;
    if (rand() % 4 == 0)
    {
        enemy1->m_Sprite.setPosition(sf::Vector2f(-50, static_cast<float>((rand() % window.getSize().y))));
    }
    else if (rand() % 4 == 1)
    {
        enemy1->m_Sprite.setPosition(sf::Vector2f(static_cast<float>((window.getSize().x + 50)), static_cast<float>((rand() % window.getSize().y))));
    }
    else if (rand() % 4 == 2)
    {
        enemy1->m_Sprite.setPosition(sf::Vector2f(static_cast<float>((rand() % window.getSize().x)), -50));
    }
    else if (rand() % 4 == 3)
    {
        enemy1->m_Sprite.setPosition(sf::Vector2f(static_cast<float>((rand() % window.getSize().x)), static_cast<float>((rand() % window.getSize().y+50))));
    }
    Enemies1.push_back(enemy1);


}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "PogSlayer? PogSlayer!");
    window.setFramerateLimit(60);
    Player player1;
    player1.m_Sprite.setPosition(sf::Vector2f(static_cast<float>((window.getSize().x / 2)), static_cast<float>((window.getSize().y / 2))));
    vector<Enemies*> Enemies1;
    sf::Clock spawn_Rate;
    bool isPaused = false;
    


    Layer layer1;
    layer1.m_Cloud_Texture1_Sprite.setPosition(200, 200);
    layer1.m_Cloud_Texture2_Sprite.setPosition(600, 200);
    layer1.m_Cloud_Texture3_Sprite.setPosition(200, 600);
    layer1.m_Cloud_Texture4_Sprite.setPosition(1000, 200);
    layer1.m_Cloud_Texture5_Sprite.setPosition(200, 1000);
    layer1.m_Cloud_Texture6_Sprite.setPosition(1000,1000);


    bool game_Over = false;
   
    sf::Font font;
    font.loadFromFile("times.ttf");
    sf::Text health_Text;
    health_Text.setFont(font);
    health_Text.setFillColor(sf::Color::White);
    health_Text.setCharacterSize(30);
    health_Text.setPosition(0, 0);


    sf::Text controls_Text;
    controls_Text.setFont(font);
    controls_Text.setFillColor(sf::Color::Red);
    controls_Text.setCharacterSize(30);
    controls_Text.setPosition(50, 500);
    controls_Text.setString("Move with W A S D, pressing Q and E moves you up or down a layer");

    sf::Text controls_Text2;
    controls_Text2.setFont(font);
    controls_Text2.setFillColor(sf::Color::Red);
    controls_Text2.setCharacterSize(30);
    controls_Text2.setPosition(50, 540);
    controls_Text2.setString(" Press Spacebar to resume game");


        while (window.isOpen())
        {

            if (isPaused)
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::KeyPressed)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        {
                            isPaused = false;
                        }
                    }
                }
                window.draw(controls_Text);
                window.draw(controls_Text2);
                window.display();
            }
            else if (game_Over == false)
            {
                health_Text.setString("Health : " + to_string(player1.m_Health));
                 sf::Event event;
                 while (window.pollEvent(event))
                 {
                     if (event.type == sf::Event::Closed)
                         window.close();
                     if (event.type == sf::Event::MouseButtonPressed)
                     {
                         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                         {
                             player1.Player_Shoot(window);

                         }
                     }

                     if (event.type == sf::Event::KeyPressed)
                     {
                         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && player1.m_Current_Level != 3)
                         {
                             player1.m_Current_Level += 1;
                         }
                         if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && player1.m_Current_Level != 1)
                         {
                             player1.m_Current_Level -= 1;
                         }
                         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                         {
                             isPaused = true;
                         }
                     }
                 }

                 if (spawn_Rate.getElapsedTime().asSeconds() >= 3)
                 {
                     Spawn_Random_Enemy(Enemies1, window);
                     spawn_Rate.restart();
                 }

                 player1.Move();
                 player1.look_At_Mouse(window);

                 window.clear();

                 layer1.Layer_Manager(player1, window, Enemies1);//also draws player and enemies

                 player1.Update(window, Enemies1, game_Over);

                 window.draw(health_Text);


                 window.display();
            }
            else
            {

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

            }
        }


    return 0;
}