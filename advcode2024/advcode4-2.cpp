#include <iostream>
#include <vector>
#include <string>
#include <sstream>

typedef std::vector<std::string> Padrao;

Padrao padrao1 = {"M.M", ".A.", "S.S"};
Padrao padrao2 = {"M.S", ".A.", "M.S"};
Padrao padrao3 = {"S.M", ".A.", "S.M"};
Padrao padrao4 = {"S.S", ".A.", "M.M"};

std::vector<Padrao> marys = {padrao1, padrao2, padrao3, padrao4};

void print_vector(std::vector<std::string> lista)
{
    for (std::string numero : lista)
    {
        std::cout << numero << std::endl;
    }
    std::cout << std::endl;
}

bool dentro_grid(int x, int y, int linhas, int colunas)
{
    return x >= 0 and x < linhas and y >= 0 and y < colunas;
}

bool identifica_mary(const std::vector<std::string> &grid, const Padrao mary, int x, int y)
{
    int linhas = grid.size();
    int colunas = grid[0].size();
    int posx;
    int posy;

    for (int i = 0; i < mary.size(); i++)
    {
        for (int j = 0; j < mary[0].size(); j++)
        {
            posx = x + i;
            posy = y + j;
            if (!dentro_grid(posx, posy, linhas, colunas))
                return false;

            if (grid[posx][posy] != mary[i][j] and mary[i][j] != '.')
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::vector<std::string> grid;
    std::string linha;

    // Lendo as linhas da matriz
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        grid.push_back(linha);
    }

    int linhas = grid.size();
    int colunas = grid[0].size();
    std::vector<std::vector<bool>> letra_valida(linhas, std::vector<bool>(colunas, false));
    // conta os padroes válidas
    int cont = 0;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (grid[i][j] == 'S' or grid[i][j] == 'M')
            {
                for (int k = 0; k < marys.size(); k++)
                {
                    if (identifica_mary(grid, marys[k], i, j))
                        cont++;
                }
            }
        }
    }

    std::cout << cont << std::endl;
    return 0;
}