#include "graphic.hpp"


template<unsigned int X, unsigned int Y>
std::array<std::array<bool, Y>, X> drawMatrix(sf::RenderTarget *target, bool redraw, int x, int y, int cellSize, std::array<std::array<bool, Y>, X> matrix)
{
    for(int i = 0; i < matrixSizeX; i++)
        for(int j = 0; j < matrixSizeY; j++)
        {
            if(matrix[i][j] != oldGen[i][j] || force)
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
    return matrix;
}

template<unsigned int X, unsigned int Y>
void repaint(sf::RenderWindow *target, int x, int y, int cellSize, std::array<std::array<bool, Y>, X> matrix)
{
    target->clear(sf::Color::Black);
    sf::RectangleShape outline(sf::Vector2f(matrix.size() * cellSize+10, matrix[0].size() * cellSize+10));
    outline.setFillColor(sf::Color::Red);
    outline.setPosition(sf::Vector2f(x-5, y-5));
    target->draw(outline);
    drawMatrix<X, Y>(target, 1, x, y, cellSize, matrix);
    target->display();
}

template<unsigned int X, unsigned int Y>
void draw(sf::RenderWindow *target, int x, int y, int cellSize, std::array<std::array<bool, Y>, X> matrix)
{
    drawMatrix<X, Y>(target, 0, x, y, cellSize, matrix);
    target->display();
}

// void drawText(std::string, int posX, int posY, int charSize)
// {
//     sf::Text output()
// }