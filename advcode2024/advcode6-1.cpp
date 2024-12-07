#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <complex>

char soldier = '^';
char free_path = '.';
char obstacle = '#';
char ja_passou = 'X';
std::complex<int> initial_direction = {-1, 0};
std::complex<int> turn = {0, -1};

void print_vector(std::vector<std::string> lista)
{
    for (std::string numero : lista)
    {
        std::cout << numero << std::endl;
    }
    std::cout << std::endl;
}

std::complex<int> transformCoords(int x, int y, int rows)
{
    return {rows - 1 - y, x};
}

// Função para destransformar índices da matriz em coordenadas cartesianas (x, y)
std::complex<int> destransformCoords(int row, int col, int rows)
{
    return {col, rows - 1 - row};
}

bool valida_move(std::complex<int> position, std::pair<int, int> mapa_dims)
{
    std::complex<int> new_pos = position + initial_direction;
    return new_pos.real() < mapa_dims.first and
           new_pos.real() >= 0 and
           new_pos.imag() < mapa_dims.second and
           new_pos.imag() >= 0;
}

void move(std::vector<std::string> &mapa, std::complex<int> &position)
{
    mapa[position.real()][position.imag()] = ja_passou;
    position += initial_direction;
    mapa[position.real()][position.imag()] = soldier;
}

int conta_lugares_passados(const std::vector<std::string> &mapa)
{
    int cont = 0;
    for (int i = 0; i < mapa.size(); i++)
    {
        for (int j = 0; j < mapa[i].size(); j++)
        {
            if (mapa[i][j] == ja_passou)
                cont++;
        }
    }
    return cont;
}

int main()
{
    std::vector<std::string> mapa;
    std::pair<int, int> mapa_dims;
    std::string linha;

    // Lendo as linhas da matriz
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        mapa.push_back(linha);
    }
    mapa_dims.first = mapa[0].size();
    mapa_dims.second = mapa.size();

    std::complex<int> position;
    for (int i = 0; i < mapa.size(); i++)
    {
        int pos = mapa[i].find(soldier);
        if (pos == std::string::npos)
            continue;
        position = {i, pos};
        break;
    }

    bool dentro_mapa = true;
    while (dentro_mapa)
    {
        if (!valida_move(position, mapa_dims))
        {
            dentro_mapa = false;
            break;
        }
        std::complex<int> a_frente = position + initial_direction;
        if (mapa[a_frente.real()][a_frente.imag()] == '#')
        {
            initial_direction *= turn;
        }
        move(mapa, position);
    }
    mapa[position.real()][position.imag()] = 'X';

    std::cout << conta_lugares_passados(mapa) << std::endl;
}