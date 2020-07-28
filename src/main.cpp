#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include "Button.hpp"


int matrixPoseX = 0, matrixPoseY = 0;   
double cellSize = 30;
std::array<std::array<bool, 1000>, 1000> matrix;



void drawMatrix(sf::RenderTarget *target)
{
    sf::RectangleShape outline(sf::Vector2f(matrix.size() * cellSize+10, matrix[0].size() * cellSize+10));
    outline.setFillColor(sf::Color::Red);
    outline.setPosition(sf::Vector2f(matrixPoseX-5, matrixPoseY-5));
    target->draw(outline);
    for(int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix[i].size(); j++)
        {
            std::array<int, 2> cellPoses = {matrixPoseX+i*(int)cellSize, matrixPoseY+j*(int)cellSize};
            if((0 < cellPoses[0] || 0 < cellPoses[0]+(int)cellSize) && (cellPoses[0]+(int)cellSize < target->getSize().x || cellPoses[0] < target->getSize().x) && (0 < cellPoses[1] || 0 < cellPoses[1]+(int)cellSize) && (cellPoses[1]+(int)cellSize < target->getSize().y || cellPoses[1] < target->getSize().y))
            {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(sf::Vector2f(cellPoses[0], cellPoses[1]));
                cell.setFillColor(matrix[i][j] ? sf::Color::White : sf::Color::Black);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Red);
                target->draw(cell);
            }
        }
}
void repaint(sf::RenderWindow *target)
{
    target->clear(sf::Color::Black);
    drawMatrix(target);
    target->display();
}
bool inInter(int val, int min, int max)
{
    return min <= val && val <= max;
}
int main()
{
    int generation = 0;
    bool pause = 1;
    int delay = 300;
    int count = 0;
    int mousePrevX = -1, mousePrevY = -1;
    sf::RenderWindow win(sf::VideoMode(800, 600), "Game Of Lag", sf::Style::Close | sf::Style::Titlebar);
    bool mouseL = 0, mouseM = 0, mouseR = 0;
    while (win.isOpen())
    {
        sf::sleep(sf::milliseconds(1));
        sf::Event event;
        while(win.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    win.close();
                    break;
                case sf::Event::MouseWheelScrolled:
                    cellSize += event.mouseWheelScroll.delta*(cellSize/10);
                    if(cellSize < 5)cellSize = 5;
                    else if(cellSize > 100) cellSize = 100;
                    break;
                case sf::Event::MouseButtonReleased:
                    switch(event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            mouseL = 0;
                            break;
                        case sf::Mouse::Middle:
                            mouseM = 0;
                            mousePrevX = -1;
                            mousePrevY = -1;
                            break;
                        case sf::Mouse::Right:
                            mouseR = 0;
                            break;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    switch(event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            mouseL = 1;
                            break;
                        case sf::Mouse::Middle:
                            mouseM = 1;
                            break;
                        case sf::Mouse::Right:
                            mouseR = 1;
                            break;
                    }
                    repaint(&win);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Space:
                            pause += 1;
                            break;
                        case sf::Keyboard::A:
                            delay += 50;
                            break;
                        case sf::Keyboard::Q:
                            delay -= 50;
                            break;
                    }
                    break;
            }
        }

        if(mouseL)
        {
            if(inInter(sf::Mouse::getPosition(win).x, matrixPoseX, matrixPoseX+matrix.size()*(int)cellSize) && inInter(sf::Mouse::getPosition(win).y, matrixPoseY, matrixPoseY+matrix[0].size()*(int)cellSize))
            { 
                std::array<int, 2> cell = {(sf::Mouse::getPosition(win).x-matrixPoseX)/((int)cellSize), (sf::Mouse::getPosition(win).y-matrixPoseY)/((int)cellSize)};
                if(!matrix[cell[0]][cell[1]])matrix[cell[0]][cell[1]]=1;
            }
            
        }
        if(mouseM)
        {
            if(mousePrevX != -1 && mousePrevY != -1)
            {
                matrixPoseX += sf::Mouse::getPosition(win).x - mousePrevX;
                matrixPoseY += sf::Mouse::getPosition(win).y - mousePrevY;
            }
            mousePrevX = sf::Mouse::getPosition(win).x;
            mousePrevY = sf::Mouse::getPosition(win).y;
        }
        if(mouseR)
        {
            if(inInter(sf::Mouse::getPosition(win).x, matrixPoseX, matrixPoseX+matrix.size()*(int)cellSize) && inInter(sf::Mouse::getPosition(win).y, matrixPoseY, matrixPoseY+matrix[0].size()*(int)cellSize))
            { 
                std::array<int, 2> cell = {(sf::Mouse::getPosition(win).x-matrixPoseX)/((int)cellSize), (sf::Mouse::getPosition(win).y-matrixPoseY)/((int)cellSize)};
                if(matrix[cell[0]][cell[1]])matrix[cell[0]][cell[1]]=0;
            }
        }


        repaint(&win);
        count = count < delay ? count+1 : 0;
    }
    
}