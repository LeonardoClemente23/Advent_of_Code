#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

void print_vector(std::vector<int> lista)
{
    for (int numero : lista)
    {
        std::cout << numero << " ";
    }
    std::cout << std::endl;
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
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int distances = 0;
    for (int i = 0; i < left.size(); i++)
    {
        int distance = std::abs(left[i] - right[i]);
        distances += distance;
    }
    std::cout << distances << std::endl;
}