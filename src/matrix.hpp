#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>

template <int size_x, int size_y>
class Matrix
{
    public:
        Matrix();
        Matrix(int posX, int posY, double cellSize);

        void set(int x, int y, bool val);
        bool get(int x, int y);

        void move(int x, int y);
        void resize(double cellsize);
        void clear();

        void nextGen();       

        int getPosX();
        int getPosY();
        int getSizeX();
        int getSizeY();
        double getCellSize();

    private:
        std::array<std::array<bool, size_y>, size_x> m_CurrentGen;
        std::array<std::array<bool, size_y>, size_x> m_PrevGen;

        int m_PosX, m_PosY, m_SizeX, m_SizeY;
        double m_CellSize;
        int m_Generation;
};

template <int size_x, int size_y>
Matrix<size_x, size_y>::Matrix()
{
    m_PosX = m_PosY = 0;
    m_SizeX = size_x;
    m_SizeY = size_y;
    m_CellSize = 30;
    m_Generation = 0;
}
template <int size_x, int size_y>
Matrix<size_x, size_y>::Matrix(int posX, int posY, double cellSize)
{
    m_PosX = posX;
    m_PosY = posY;
    m_SizeX = size_x;
    m_SizeY = size_y;
    m_CellSize = cellSize;
    m_Generation = 0;
}



template <int size_x, int size_y>
void Matrix<size_x, size_y>::set(int x, int y, bool val)
{
    m_CurrentGen[x][y] = val;
}

template <int size_x, int size_y>
bool Matrix<size_x, size_y>::get(int x, int y)
{
    return m_CurrentGen[x][y];
}

template <int size_x, int size_y>
void Matrix<size_x, size_y>::move(int x, int y)
{
    m_PosX = x;
    m_PosY = y;
}

template <int size_x, int size_y>
void Matrix<size_x, size_y>::resize(double cellsize)
{
    m_CellSize = cellsize;
}

template <int size_x, int size_y>
void Matrix<size_x, size_y>::clear()
{
    m_CurrentGen = std::array<std::array<bool, size_y>, size_x>();
}

template <int size_x, int size_y>
void Matrix<size_x, size_y>::nextGen()
{
    m_PrevGen = m_CurrentGen;
    m_CurrentGen = std::array<std::array<bool, size_y>, size_x>();
    for(int i = 0; i < size_x; i++)
        for(int j = 0; j < size_y; j++)
        {
            int adjCells = 0;
            for(int k = -1; k < 2; k++)
                for(int l = -1; l < 2; l++)
                    if(!(k == 0 && l == 0) && i+k > -1 && j+l > -1 && i+k < size_x-1 && j+l < size_y-1)
                        if(m_PrevGen[i+k][j+l])adjCells++;
            if(adjCells == 3)m_CurrentGen[i][j] = 1;
            else if(adjCells == 2)m_CurrentGen[i][j] = m_PrevGen[i][j];
            else m_CurrentGen[i][j] = 0;
        }
    m_Generation++;
}

template <int size_x, int size_y>
int Matrix<size_x, size_y>::getPosX()
{
    return m_PosX;
}

template <int size_x, int size_y>
int Matrix<size_x, size_y>::getPosY()
{
    return m_PosY;
}

template <int size_x, int size_y>
int Matrix<size_x, size_y>::getSizeX()
{
    return m_SizeX;
}

template <int size_x, int size_y>
int Matrix<size_x, size_y>::getSizeY()
{
    return m_SizeY;
}

template <int size_x, int size_y>
double Matrix<size_x, size_y>::getCellSize()
{
    return m_CellSize;
}

#endif