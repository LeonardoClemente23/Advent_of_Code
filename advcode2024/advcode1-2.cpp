#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

int frequencies_sum(std::vector<int> lista1, std::vector<int> lista2)
{
    int frequencies = 0;
    for (int i = 0; i < lista1.size(); i++)
    {
        frequencies += (std::count(lista2.begin(), lista2.end(), lista1[i]) * lista1[i]);
    }
    return frequencies;
}

int main()
{
    std::vector<int> left;
    std::vector<int> right;
    std::string linha;

    while (std::getline(std::cin, linha) && !linha.empty())
    {
        std::istringstream stream(linha);
        int numero;

        // Lendo os números da linha
        stream >> numero;
        left.push_back(numero);

        stream >> numero;
        right.push_back(numero);
    }

    std::cout << frequencies_sum(left, right) << std::endl;
}