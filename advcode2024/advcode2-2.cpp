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

bool is_safe_by_remove(std::vector<int> lista)
{
    for (size_t i = 0; i < lista.size(); ++i)
    {
        // Remover o elemento i
        int elemento = lista[i];
        lista.erase(lista.begin() + i);

        // Verifica a lista sem o possível elemento problema
        if (is_safe(lista))
            return true;

        // Recoloca o elemento no vetor na posição original
        lista.insert(lista.begin() + i, elemento);
    }
    return false;
}

void print_vector(std::vector<int> lista)
{
    for (int numero : lista)
        std::cout << numero << " ";

    std::cout << std::endl;
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
        else if (is_safe_by_remove(linha))
            cont_safe++;
    }
    std::cout << cont_safe << std::endl;
    return 0;
}