#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include "matrix.hpp"

#define GAME_WIDTH 1000
#define GAME_HEIGHT 1000


// void drawText(std::string, int posX, int posY, int charSize)
// {
//     sf::Text output()
// }
template <int size_x, int size_y>
void drawMatrix(sf::RenderTarget *target, Matrix<size_x, size_y> matrix)
{
    for(int i = 0; i < matrix.getSizeX(); i++)
        for(int j = 0; j < matrix.getSizeY(); j++)if(matrix.get(i, j))
        {
            std::array<int, 2> cellPoses = {matrix.getPosX()+i*(int)matrix.getCellSize(), matrix.getPosY()+j*(int)matrix.getCellSize()};
            if((0 < cellPoses[0] || 0 < cellPoses[0]+(int)matrix.getCellSize()) && (cellPoses[0]+(int)matrix.getCellSize() < target->getSize().x || cellPoses[0] < target->getSize().x) && (0 < cellPoses[1] || 0 < cellPoses[1]+(int)matrix.getCellSize()) && (cellPoses[1]+(int)matrix.getCellSize() < target->getSize().y || cellPoses[1] < target->getSize().y))
            {
                sf::RectangleShape cell(sf::Vector2f((int)matrix.getCellSize()-2, (int)matrix.getCellSize()-2));
                cell.setPosition(sf::Vector2f(cellPoses[0]+1, cellPoses[1]+1));
                cell.setFillColor(sf::Color::White);
                target->draw(cell);
            }
        }
    
    for(int i = 0; i < matrix.getSizeX()+1; i++)if((0 < matrix.getPosX()+i*(int)matrix.getCellSize() || 0 < matrix.getPosX()+i*(int)matrix.getCellSize()+2) && (matrix.getPosX()+i*(int)matrix.getCellSize() < target->getSize().x || matrix.getPosX()+i*(int)matrix.getCellSize()+2 < target->getSize().x))
    {
        sf::RectangleShape line(sf::Vector2f(2, matrix.getSizeY()*(int)matrix.getCellSize()));
        line.setPosition(sf::Vector2f(matrix.getPosX()+i*(int)matrix.getCellSize()-1, matrix.getPosY()));
        line.setFillColor(sf::Color(255, 255, 255, 64));
        target->draw(line);
    }
    for(int i = 0; i < matrix.getSizeY()+1; i++)if((0 < matrix.getPosY()+i*(int)matrix.getCellSize() || 0 < matrix.getPosY()+i*(int)matrix.getCellSize()+2) && (matrix.getPosY()+i*(int)matrix.getCellSize() < target->getSize().y || matrix.getPosY()+i*(int)matrix.getCellSize()+2 < target->getSize().y))
    {
        sf::RectangleShape line(sf::Vector2f(matrix.getSizeX()*(int)matrix.getCellSize(), 2));
        line.setPosition(sf::Vector2f(matrix.getPosX(), matrix.getPosY()+i*(int)matrix.getCellSize()-1));
        line.setFillColor(sf::Color(255, 255, 255, 64));
        target->draw(line);
    }
}
template <int size_x, int size_y>
void repaint(sf::RenderWindow *target, Matrix<size_x, size_y> matrix)
{
    target->clear(sf::Color::Black);
    drawMatrix<size_x, size_y>(target, matrix);
    target->display();
}
bool inInter(int val, int min, int max)
{
    return min <= val && val <= max;
}
int main()
{
    sf::RenderWindow win(sf::VideoMode(800, 600), "Game Of Lag", sf::Style::Default);
    Matrix<GAME_WIDTH, GAME_HEIGHT> matrix;
    bool pause = 1;
    int delay = 10;
    int count = 0;
    int mousePrevX = -1, mousePrevY = -1;
    bool mouseL = 0, mouseM = 0, mouseR = 0;

    while (win.isOpen())
    {
        sf::Event event;
        while(win.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    win.close();
                    break;
                case sf::Event::MouseWheelScrolled:
                    matrix.resize(matrix.getCellSize() + event.mouseWheelScroll.delta*(matrix.getCellSize()/10));
                    if(matrix.getCellSize() < 5) matrix.resize(5);
                    else if(matrix.getCellSize() > 100) matrix.resize(100);
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
                    repaint<GAME_WIDTH, GAME_HEIGHT>(&win, matrix);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Space://pause!!
                            pause = !pause;
                            break;
                        case sf::Keyboard::A://slow down the game
                            if(delay < 50)delay += 1;
                            break;
                        case sf::Keyboard::Q://speed up the game
                            if(delay > 0)delay -= 1;
                            break;
                        case sf::Keyboard::C://remove every cells
                            matrix.clear();
                            break;
                    }
                    break;
                case sf::Event::Resized:
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    win.setView(sf::View(visibleArea));
                    break;
            }
        }

        if(mouseL)
        {
            if(inInter(sf::Mouse::getPosition(win).x, matrix.getPosX(), matrix.getPosX()+matrix.getSizeX()*(int)matrix.getCellSize()) && inInter(sf::Mouse::getPosition(win).y, matrix.getPosY(), matrix.getPosY()+matrix.getSizeY()*(int)matrix.getCellSize()))
            { 
                std::array<int, 2> cell = {(sf::Mouse::getPosition(win).x-matrix.getPosX())/((int)matrix.getCellSize()), (sf::Mouse::getPosition(win).y-matrix.getPosY())/((int)matrix.getCellSize())};
                if(!matrix.get(cell[0], cell[1]))matrix.set(cell[0], cell[1], 1);
            }
            
        }
        if(mouseM)
        {
            if(mousePrevX != -1 && mousePrevY != -1)
                matrix.move(matrix.getPosX() + sf::Mouse::getPosition(win).x - mousePrevX, matrix.getPosY() + sf::Mouse::getPosition(win).y - mousePrevY);

            mousePrevX = sf::Mouse::getPosition(win).x;
            mousePrevY = sf::Mouse::getPosition(win).y;
        }
        if(mouseR)
        {
            if(inInter(sf::Mouse::getPosition(win).x, matrix.getPosX(), matrix.getPosX()+matrix.getSizeX()*(int)matrix.getCellSize()) && inInter(sf::Mouse::getPosition(win).y, matrix.getPosY(), matrix.getPosY()+matrix.getSizeY()*(int)matrix.getCellSize()))
            { 
                std::array<int, 2> cell = {(sf::Mouse::getPosition(win).x-matrix.getPosX())/((int)matrix.getCellSize()), (sf::Mouse::getPosition(win).y-matrix.getPosY())/((int)matrix.getCellSize())};
                if(matrix.get(cell[0], cell[1]))matrix.set(cell[0], cell[1], 0);
            }
        }

        if(!pause && count == 0)matrix.nextGen();
        repaint<GAME_WIDTH, GAME_HEIGHT>(&win, matrix);
        count = (count < delay) ? count+1 : 0;
    }
    
}