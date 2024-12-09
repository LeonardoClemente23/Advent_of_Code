#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <bitset>

const std::vector<std::string> operacoes = {"+", "*", "||"};

typedef std::pair<long long, std::vector<int>> Equacao;

void print_vector(std::vector<Equacao> lista)
{
    for (Equacao equacao : lista)
    {
        std::cout << equacao.first << ": " << " ";
        for (long long numero : equacao.second)
        {
            std::cout << numero << "," << " ";
        }
        std::cout << std::endl;
    }
}

void print_vector_str(std::vector<std::string> lista)
{
    for (std::string numero : lista)
    {
        std::cout << numero << " ";
    }
    std::cout << std::endl;
}

void print_vector_int(std::vector<int> lista)
{
    for (int numero : lista)
    {
        std::cout << numero << " ";
    }
    std::cout << std::endl;
}

std::vector<std::vector<std::string>> gera_combinacoes(int espacos)
{
    std::vector<std::vector<std::string>> combinacoes;
    if (espacos == 0)
        return combinacoes;

    int base = operacoes.size();
    int total_comb = std::pow(base, espacos);

    for (int i = 0; i < total_comb; ++i)
    {
        std::vector<std::string> combinacao;
        int num = i;
        for (int j = 0; j < espacos; ++j)
        {
            combinacao.push_back(operacoes[num % base]);
            num /= base;
        }
        // print_vector_str(combinacao);
        combinacoes.push_back(combinacao);
    }
    return combinacoes;
}

int main()
{
    std::vector<Equacao> equacoes;
    std::string linha;
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        long long resultado;
        std::vector<int> numeros_equacao;
        int pos = linha.find(":");
        if (pos != std::string::npos)
        {
            resultado = stoll(linha.substr(0, pos));
        }

        std::istringstream stream(linha.substr(pos + 1));
        int numero;

        while (stream >> numero)
            numeros_equacao.push_back(numero);

        Equacao equacao = {resultado, numeros_equacao};
        equacoes.push_back(equacao);
    }

    long long cont = 0;
    for (int i = 0; i < equacoes.size(); i++)
    {
        int espacos = equacoes[i].second.size() - 1;
        std::vector<std::vector<std::string>> combinacoes_operacoes = gera_combinacoes(espacos);

        for (long long j = 0; j < combinacoes_operacoes.size(); j++)
        {
            std::vector<std::string> combinacao = combinacoes_operacoes[j];
            // std::cout << "A COMBINACAO: " << j << std::endl;
            // std::cout << combinacoes_operacoes.size() << std::endl;
            // print_vector_str(combinacao);
            //  print_vector_int(nova_lista);
            long long resultado = equacoes[i].second[0];
            if (!combinacao.empty())
            {
                for (int k = 0; k < combinacao.size(); k++)
                {
                    {
                        if (combinacao[k] == "+")
                            resultado += equacoes[i].second[k + 1];
                        if (combinacao[k] == "*")
                            resultado *= equacoes[i].second[k + 1];
                        if (combinacao[k] == "||")
                            resultado = stoll(std::to_string(resultado) + std::to_string(equacoes[i].second[k + 1]));
                    }
                }
            }
            // std::cout << resultado << std::endl;
            if (resultado == equacoes[i].first)
            {
                // std::cout << "DEU BOM" << std::endl;
                cont += resultado;
                break;
            }
        }
        // std::cout << "_______________________________________" << std::endl;
    }
    std::cout << cont << std::endl;
}