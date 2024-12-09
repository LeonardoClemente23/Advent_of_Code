#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <bitset>

const std::vector<std::string> operacoes = {"+", "*", "||"};

typedef std::pair<long long, std::vector<int>> Equacao;

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
            if (resultado == equacoes[i].first)
            {
                cont += resultado;
                break;
            }
        }
    }
    std::cout << cont << std::endl;
}
