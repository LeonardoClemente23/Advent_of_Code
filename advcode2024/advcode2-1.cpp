#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

bool estah_ordenado(std::vector<int> lista)
{
    if (std::is_sorted(lista.begin(), lista.end()) or std::is_sorted(lista.begin(), lista.end(), std::greater<int>()))
        return true;

    return false;
}

bool is_safe(std::vector<int> lista)
{
    if (!estah_ordenado(lista))
        return false;

    for (int i = 0; i < (lista.size() - 1); i++)
    {
        if (std::abs(lista[i] - lista[i + 1]) > 3 or std::abs(lista[i] - lista[i + 1]) == 0)
            return false;
    }
    return true;
}

int main()
{
    std::vector<std::vector<int>> matriz;
    std::string linha;

    // Lendo as linhas da matriz
    while (std::getline(std::cin, linha) && !linha.empty())
    {
        std::vector<int> linha_matriz;
        std::istringstream stream(linha);
        int numero;

        // Lendo os números da linha
        while (stream >> numero)
            linha_matriz.push_back(numero);

        matriz.push_back(linha_matriz);
    }
    int cont_safe = 0;
    for (const auto &linha : matriz)
    {
        if (is_safe(linha))
            cont_safe++;
    }
    std::cout << cont_safe << std::endl;
    return 0;
}