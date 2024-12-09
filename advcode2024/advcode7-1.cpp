#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <bitset>

typedef std::pair<long long, std::vector<int>> Equacao;

std::string bit_para_string(int n, int bitcount)
{
    std::string bits = "";
    for (int bit = bitcount - 1; bit >= 0; --bit)
    {
        bits += ((n >> bit) & 1) ? '1' : '0';
    }
    return bits;
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
        const size_t range_numbers = equacoes[i].second.size() - 1;
        std::string bits;
        for (int j = 0; j < (1 << (range_numbers)); ++j)
        {
            bits = bit_para_string(j, range_numbers);
            long long calculado = equacoes[i].second[0];
            for (int k = 0; k < bits.size(); k++)
            {
                if (bits[k] == '1')
                    calculado += equacoes[i].second[k + 1];
                else
                    calculado *= equacoes[i].second[k + 1];
            }
            if (calculado == equacoes[i].first)
            {
                cont += calculado;
                break;
            }
        }
    }
    std::cout << cont << std::endl;
}