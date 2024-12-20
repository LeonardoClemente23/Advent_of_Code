#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

std::vector<int> dx = {0, 0, 1, -1};
std::vector<int> dy = {1, -1, 0, 0};

void print_topografia(std::vector<std::vector<int>> topografia)
{
    for (auto &&linha : topografia)
    {
        for (int i = 0; i < linha.size(); i++)
        {
            std::cout << linha[i];
        }
        std::cout << std::endl;
    }
}

bool dentro_grid(int x, int y, int linhas, int colunas)
{
    return x >= 0 and x < linhas and y >= 0 and y < colunas;
}

int avalia_visitas(std::vector<std::vector<int>> &topografia, int x, int y, int linhas, int colunas)
{
    std::queue<std::pair<int, int>> fila_a_visitar;
    std::vector<std::pair<int, int>> visitados;
    std::pair<int, int> posicao_inicial = {x, y};
    int altura_atual = 0;

    bool visitavel = true;
    int pontos = 1;
    fila_a_visitar.push(posicao_inicial);
    while (visitavel)
    {
        std::pair<int, int> posicao = fila_a_visitar.front();
        int escolha_caminho = 0;
        bool final_caminho = false;
        for (int direction = 0; direction < 4; direction++)
        {
            int pos_x = posicao.first + dx[direction];
            int pos_y = posicao.second + dy[direction];
            if (dentro_grid(pos_x, pos_y, linhas, colunas))
            {
                if (topografia[posicao.first][posicao.second] == 9)
                {
                    final_caminho = true;
                    int cnt = std::count(visitados.begin(), visitados.end(), posicao);
                    if (cnt == 0)
                    {
                        break;
                    }
                }
                bool nao_visitado;
                if (topografia[pos_x][pos_y] == (topografia[posicao.first][posicao.second] + 1))
                {
                    escolha_caminho++;
                    std::pair<int, int> avaliado = {pos_x, pos_y};
                    int cnt = std::count(visitados.begin(), visitados.end(), avaliado);
                    if (cnt == 0)
                        fila_a_visitar.push(avaliado);
                }
            }
        }
        visitados.push_back(posicao);
        fila_a_visitar.pop();

        if (fila_a_visitar.empty())
            visitavel = false;

        if (final_caminho)
            continue;

        if (escolha_caminho == 0)
        {
            pontos--;
        }

        if (escolha_caminho > 0)
        {
            pontos += (escolha_caminho - 1);
        }
    }
    return pontos;
}

int main()
{
    std::vector<std::vector<int>> topografia;
    std::string linha;

    // Lendo as linhas da matriz
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        std::vector<int> linha_int;
        for (char number : linha)
        {
            int n = number - '0';
            linha_int.push_back(n);
        }

        topografia.push_back(linha_int);
    }

    int linhas = topografia.size();
    int colunas = topografia[0].size();

    std::queue<std::pair<int, int>> fila_a_visitar;
    std::vector<std::pair<int, int>> visitados;
    int soma_pontos = 0;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (topografia[i][j] == 0)
            {
                std::cout << std::endl;
                int pontos = avalia_visitas(topografia, i, j, linhas, colunas);
                soma_pontos += pontos;
            }
        }
    }
    std::cout << soma_pontos << std::endl;
    return 0;
}