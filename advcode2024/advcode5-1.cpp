#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

typedef struct
{
    int raiz;
    std::vector<int> antes;
} Pagina;

bool existe_raiz(const std::vector<Pagina> paginas, const int pagina)
{
    if (paginas.empty())
        return false;

    for (Pagina i : paginas)
    {
        if (i.raiz == pagina)
        {
            return true;
        }
    }
    return false;
}

Pagina get_pagina(std::vector<Pagina> paginas, int pagina)
{
    for (Pagina i : paginas)
    {
        if (i.raiz == pagina)
        {
            return i;
        }
    }
    Pagina pagina_vazia;
    return pagina_vazia;
}

int main()
{
    std::vector<std::pair<int, int>> regras_ordem;
    std::string linha;

    // Lendo as regras
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        std::string del = "|";

        auto pos = linha.find(del);

        while (pos != std::string::npos)
        {
            int first = stoi(linha.substr(0, pos));

            linha.erase(0, pos + del.length());

            pos = linha.find(del);
            int second = stoi(linha);

            std::pair<int, int> par = {first, second};
            regras_ordem.push_back(par);
        }
    }

    // Lendo as sequencias
    std::vector<std::vector<int>> sequencias;
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        std::string del = ",";

        auto pos = linha.find(del);

        std::vector<int> sequencia;
        int numero;

        while (pos != std::string::npos)
        {
            numero = stoi(linha.substr(0, pos));
            sequencia.push_back(numero);

            linha.erase(0, pos + del.length());

            pos = linha.find(del);
        }
        sequencia.push_back(stoi(linha));
        sequencias.push_back(sequencia);
    }

    // Inicio processamento
    std::vector<Pagina> paginas;
    std::vector<std::vector<int>> sequencias_validas;
    // Para cada sequencia...
    for (std::vector<int> &sequencia : sequencias)
    {
        bool sequencia_valida = true;
        // Para cada numero da sequencia... (pivo)
        for (int j = 0; j < sequencia.size(); j++)
        {
            int pivo = sequencia[j];
            // Se a pagina não foi processada ainda, uma Pagina é criada
            if (!existe_raiz(paginas, pivo))
            {
                Pagina pagina;
                pagina.raiz = pivo;
                for (std::pair<int, int> regra : regras_ordem)
                {
                    if (regra.second == pivo)
                    {
                        pagina.antes.push_back(regra.first);
                    }
                }
                paginas.push_back(pagina);
            }
            // Para cada numero da sequencia depois do pivo...
            for (int k = j + 1; k < sequencia.size(); k++)
            {
                Pagina pagina = get_pagina(paginas, pivo);
                auto it = find(pagina.antes.begin(), pagina.antes.end(), sequencia[k]);
                // Se o numero foi encontrado em pagina.antes do pivo, a sequencia está desordenada
                if (it != pagina.antes.end())
                {
                    sequencia_valida = false;
                    break;
                }
            }
            if (!sequencia_valida)
                break;
        }
        if (sequencia_valida)
        {
            sequencias_validas.push_back(sequencia);
        }
    }

    // Soma os valores do meio
    int cont = 0;
    for (std::vector<int> &sequencia : sequencias_validas)
    {
        int meio = (sequencia.size() - 1) / 2;
        cont += sequencia[meio];
    }

    std::cout << cont << std::endl;
    return 0;
}