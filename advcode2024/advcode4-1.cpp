#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<int> dx = {0, 0, 1, -1, 1, 1, -1, -1};
std::vector<int> dy = {1, -1, 0, 0, 1, -1, 1, -1};

bool dentro_grid(int x, int y, int linhas, int colunas)
{
    return x >= 0 and x < linhas and y >= 0 and y < colunas;
}

bool busca_mary(const std::vector<std::string> &grid, std::string mary, int x, int y, int dir)
{
    int linhas = grid.size();
    int colunas = grid[0].size();

    for (int i = 0; i < mary.size(); i++)
    {
        int posx = x + i * dx[dir];
        int posy = y + i * dy[dir];

        if (!dentro_grid(posx, posy, linhas, colunas) or grid[posx][posy] != mary[i])
            return false;
    }
    return true;
}

void print_vector(std::vector<std::string> lista)
{
    for (std::string numero : lista)
    {
        std::cout << numero << " ";
    }
    std::cout << std::endl;
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

    print_vector(grid);

    int linhas = grid.size();
    int colunas = grid[0].size();
    std::string mary = "XMAS";

    int cont = 0;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (grid[i][j] == mary[0])
            {
                // std::cout << "ACHOU " << i << "," << j << std::endl;
                for (int dir = 0; dir < dx.size(); dir++)
                {
                    if (busca_mary(grid, mary, i, j, dir))
                    {
                        cont++;
                    }
                }
            }
        }
    }
    std::cout << cont << std::endl;
    return 0;
}