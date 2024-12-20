#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

typedef struct
{
    long long position;
    std::string id;
    bool is_empty;
} FileBlock;

void print_vector(std::vector<int> lista)
{
    for (int numero : lista)
    {
        std::cout << numero << " ";
    }
    std::cout << std::endl;
}

void print_file_block(std::vector<FileBlock> lista_blocos)
{
    for (FileBlock numero : lista_blocos)
    {
        std::cout << numero.id << "/";
    }
    std::cout << std::endl;
}

int main()
{
    std::ifstream arquivo("advcode9.txt"); // Abre o arquivo para leitura
    if (!arquivo.is_open())
    { // Verifica se o arquivo foi aberto com sucesso
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    std::vector<int> rules_file;
    std::string linha((std::istreambuf_iterator<char>(arquivo)),
                      std::istreambuf_iterator<char>());
    arquivo.close(); // Fecha o arquivo
    std::cout << linha << std::endl;
    // std::getline(std::cin, linha);
    for (char n : linha)
    {
        int numero = n - '0';

        // Lendo os números da linha
        rules_file.push_back(numero);
    }
    // print_vector(rules_file);

    std::vector<FileBlock> lista_blocos;
    long long id = 0;
    long long position = 0;
    for (int i = 0; i < rules_file.size(); i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < rules_file[i]; j++)
            {
                FileBlock file_block;
                file_block.position = position;
                file_block.id = std::to_string(id);
                file_block.is_empty = false;
                lista_blocos.push_back(file_block);
                position++;
            }
            id++;
        }
        else
        {
            for (int j = 0; j < rules_file[i]; j++)
            {
                FileBlock file_block;
                file_block.position = position;
                file_block.id = '.';
                file_block.is_empty = true;
                lista_blocos.push_back(file_block);
                position++;
            }
        }
    }
    // print_file_block(lista_blocos);

    int tamanho_lista_blocos = lista_blocos.size();
    for (int i = 0; i < tamanho_lista_blocos; i++)
    {
        if (lista_blocos[i].is_empty)
        {
            for (int j = tamanho_lista_blocos - 1; j >= 0; j--)
            {
                if (!lista_blocos[j].is_empty and i < j)
                {
                    // lista_blocos[i].position = j;
                    lista_blocos[i].is_empty = false;
                    lista_blocos[i].id = lista_blocos[j].id;
                    // lista_blocos[j].position = i;
                    lista_blocos[j].is_empty = true;
                    lista_blocos[j].id = '.';
                    break;
                }
            }
        }
    }

    int cont = 0;
    for (FileBlock block : lista_blocos)
    {
        // std::cout << block.id << "/";

        if (block.id != ".")
        {
            // std::cout << block.id << " x " << block.position << " = " << block.position * std::stoi(block.id) << std::endl;
            cont += block.position * std::stoll(block.id);
        }
    }

    std::cout << cont << std::endl;
}