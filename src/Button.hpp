#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
    public:
        Button(int x, int y, int sizeX, int sizeY, std::string text, sf::Color color)
        {
            m_PosX = x;
            m_PosY = y;
            m_SizeX = sizeX;
            m_SizeY = sizeY;
            m_Text = text;
            m_Color = color;
        }
        bool pointing(int mousePosX, int mousePosY)
        {
            return((mousePosX >= m_PosX && mousePosX <= m_PosX+m_SizeX) && (mousePosY >= m_PosY && mousePosY <= m_PosY+m_SizeY));
        }
        void draw(sf::RenderTarget *target)
        {
            sf::RectangleShape base = sf::RectangleShape(sf::Vector2f(m_SizeX, m_SizeY));
            base.setFillColor(sf::Color::Black);
            base.setOutlineThickness(3);
            base.setOutlineColor(m_Color);
            sf::Text
        }
        void setColor(sf::Color newColor)
        {
            m_Color = newColor
        }
    private:
        int m_PosX, m_PosY, m_SizeX, m_SizeY;
        std::string m_Text;
        sf::Color m_Color;

};

#endif