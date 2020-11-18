#include <SFML/Graphics.hpp>
#include <array>

template<unsigned int X, unsigned int Y> std::array<std::array<bool, Y>, X> drawMatrix(sf::RenderTarget *target, bool redraw, int x, int y, int cellSize, std::array<std::array<bool, Y>, X> matrix);
template<unsigned int X, unsigned int Y> void repaint(sf::RenderWindow *target, int x, int y, int cellSize, std::array<std::array<bool, Y>, X> matrix);
template<unsigned int X, unsigned int Y> void draw(sf::RenderWindow *target);