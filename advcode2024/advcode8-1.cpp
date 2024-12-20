#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

typedef struct
{
    char antena;
    std::vector<std::pair<int, int>> positions;
} LocAntena;

void print_vector(std::vector<std::string> lista)
{
    for (std::string numero : lista)
    {
        std::cout << numero << std::endl;
    }
    std::cout << std::endl;
}

void print_loc_antenas(const std::vector<LocAntena> loc_antenas)
{
    // std::cout << "print_loc_antenas" << std::endl;
    for (LocAntena loc_antena : loc_antenas)
    {
        std::cout << loc_antena.antena << ": ";
        for (int i = 0; i < loc_antena.positions.size(); i++)
        {
            std::cout << "(" << loc_antena.positions[i].first << "," << loc_antena.positions[i].second << ")" << std::endl;
        }
        std::cout << std::endl;
    }
}

bool dentro_grid(int x, int y, int linhas, int colunas)
{
    return x >= 0 and x < linhas and y >= 0 and y < colunas;
}

bool existe_antena(std::vector<LocAntena> loc_antenas, char antena)
{
    // std::cout << "existe_antena" << std::endl;
    for (LocAntena loc_antena : loc_antenas)
    {
        if (loc_antena.antena == antena)
            return true;
    }
    return false;
}

LocAntena get_antena(std::vector<LocAntena> &antenas, char antena)
{
    if (existe_antena(antenas, antena))
    {
        for (LocAntena loc_antena : antenas)
        {
            if (loc_antena.antena == antena)
                return loc_antena;
        }
    }
    LocAntena antena_vaiza;
    return antena_vaiza;
}

void update_antena(std::vector<LocAntena> &antenas, char antena, std::pair<int, int> localization)
{
    for (LocAntena &loc_antena : antenas)
    {
        if (loc_antena.antena == antena)
        {
            loc_antena.positions.push_back(localization);
            break;
        }
    }
}

std::vector<LocAntena> get_loc_antenas(const std::vector<std::string> grid)
{
    // std::cout << "get_loc_antenas" << std::endl;
    std::vector<LocAntena> loc_antenas;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            LocAntena loc_antena;
            if (grid[i][j] != '.')
            {
                if (existe_antena(loc_antenas, grid[i][j]))
                {
                    std::pair<int, int> position = {i, j};
                    update_antena(loc_antenas, grid[i][j], position);
                }
                else
                {
                    loc_antena.antena = grid[i][j];
                    std::pair<int, int> position = {i, j};
                    loc_antena.positions.push_back(position);
                    loc_antenas.push_back(loc_antena);
                }
            }
        }
    }
    return loc_antenas;
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

    int n_linhas = grid.size();
    int n_colunas = grid[0].size();

    print_vector(grid);
    std::vector<LocAntena> antenas = get_loc_antenas(grid);

    print_loc_antenas(antenas);

    int cont = 0;
    for (LocAntena antena : antenas)
    {
        int qt_antenas = antena.positions.size();
        for (int i = 0; i < qt_antenas; i++)
        {
            for (int j = i; j < qt_antenas; j++)
            {
                int di = antena.positions[i].first - antena.positions[j].first;
                int dj = antena.positions[i].second - antena.positions[j].second;
                if (dj == 0 and di == 0)
                    continue;

                std::vector<int> id_antenas = {i, j};
                for (int id_antena : id_antenas)
                {
                    int i_influencia_em_cima = antena.positions[id_antena].first + di;
                    int j_influencia_em_cima = antena.positions[id_antena].second + dj;
                    if (dentro_grid(i_influencia_em_cima, j_influencia_em_cima, n_linhas, n_colunas))
                    {
                        // std::cout << grid[i_influencia_em_cima][j_influencia_em_cima] << ": ";
                        if (grid[i_influencia_em_cima][j_influencia_em_cima] == '.')
                        {
                            cont++;
                            // std::cout << "entrou em cima!" << "// ";
                            grid[i_influencia_em_cima][j_influencia_em_cima] = '#';
                        }
                        else if (grid[i_influencia_em_cima][j_influencia_em_cima] == '#')
                            cont++;
                    }

                    int i_influencia_embaixo = antena.positions[id_antena].first - di;
                    int j_influencia_embaixo = antena.positions[id_antena].second - dj;
                    if (dentro_grid(i_influencia_embaixo, j_influencia_embaixo, n_linhas, n_colunas))
                    {
                        // std::cout << grid[i_influencia_embaixo][j_influencia_embaixo] << ": ";
                        if (grid[i_influencia_embaixo][j_influencia_embaixo] == '.')
                        {
                            cont++;
                            // std::cout << "entrou embaixo!" << "// ";
                            grid[i_influencia_embaixo][j_influencia_embaixo] = '#';
                        }
                        else if (grid[i_influencia_embaixo][j_influencia_embaixo] == '#')
                            cont++;
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
    print_vector(grid);
    std::cout << cont << std::endl;
}