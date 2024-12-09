#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <complex>

const char soldier = '^';
const char free_path = '.';
const char obstacle = '#';
const char ja_passou = 'X';
const char novo_obstaculo = 'O';
const std::complex<int> initial_direction = {-1, 0};
const std::complex<int> turn = {0, -1};

void print_vector(std::vector<std::string> lista)
{
    for (std::string numero : lista)
    {
        std::cout << numero << std::endl;
    }
    std::cout << std::endl;
}

bool valida_move(const std::complex<int> position, const std::complex<int> direction, const std::pair<int, int> mapa_dims)
{
    std::complex<int> new_pos = position + direction;
    return new_pos.real() < mapa_dims.first and
           new_pos.real() >= 0 and
           new_pos.imag() < mapa_dims.second and
           new_pos.imag() >= 0;
}

void move(std::vector<std::string> &mapa, std::complex<int> &position, std::complex<int> direction)
{
    mapa[position.real()][position.imag()] = ja_passou;
    position += direction;
    mapa[position.real()][position.imag()] = soldier;
}

int conta_lugares(const std::vector<std::string> &mapa, const char lugar)
{
    int cont = 0;
    for (int i = 0; i < mapa.size(); i++)
    {
        for (int j = 0; j < mapa[i].size(); j++)
        {
            if (mapa[i][j] == lugar)
                cont++;
        }
    }
    return cont;
}

int main()
{
    std::vector<std::string> initial_mapa;
    std::pair<int, int> mapa_dims;
    std::string linha;

    // Lendo as linhas do mapa
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        initial_mapa.push_back(linha);
    }
    mapa_dims.first = initial_mapa[0].size();
    mapa_dims.second = initial_mapa.size();

    std::complex<int> initial_position;
    for (int i = 0; i < initial_mapa.size(); i++)
    {
        int pos = initial_mapa[i].find(soldier);
        if (pos == std::string::npos)
            continue;
        initial_position = {i, pos};
        break;
    }

    int cont_free_path = conta_lugares(initial_mapa, free_path);
    int cont_loop = 0;
    for (int i = 0; i < initial_mapa.size(); i++)
    {
        for (int j = 0; j < initial_mapa[i].size(); j++)
        {
            if (initial_mapa[i][j] == obstacle or
                initial_mapa[i][j] == soldier)
                continue;

            std::vector<std::string> mapa = initial_mapa;
            std::complex<int> position = initial_position;
            std::complex<int> direction = initial_direction;
            mapa[i][j] = novo_obstaculo;

            int cont_passos = 0;
            while (cont_passos <= cont_free_path)
            {
                if (!valida_move(position, direction, mapa_dims))
                {
                    break;
                }
                std::complex<int> a_frente = position + direction;
                if (mapa[a_frente.real()][a_frente.imag()] == obstacle or
                    mapa[a_frente.real()][a_frente.imag()] == novo_obstaculo)
                {
                    direction *= turn;
                }
                move(mapa, position, direction);
                cont_passos++;
            }
            mapa[position.real()][position.imag()] = 'X';
            if (cont_passos > cont_free_path)
            {
                // print_vector(mapa);
                cont_loop++;
                std::cout << i << "," << j << " ";
                // std::cout << cont_loop << "," << cont_passos << ":" << cont_free_path << std::endl;
            }
            // if (i == 3 and j == 1)
            //     print_vector(mapa);
        }
    }
    std::cout << cont_loop << std::endl;
}
