// ESTAH ERRADO
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

typedef struct no
{
    bool visitado;
    long long numero_no;
    no *esquerdo;
    no *direito;
} No;

No *cria_no(long long conteudo)
{
    No *no = new No();
    no->numero_no = conteudo;
    no->direito = nullptr;
    no->esquerdo = nullptr;

    return no;
}

void inserir_no(No *pai)
{
    std::string pai_str = std::to_string(pai->numero_no);
    if (pai->numero_no == 0)
    {
        pai->esquerdo = cria_no(1);
        std::cout << "inserir no 1: " << pai->direito << "/" << pai->esquerdo << std::endl;
        return;
    }

    if (pai_str.size() % 2 == 0)
    {
        long long n_esquerdo = stoll(pai_str.substr(0, (pai_str.size() / 2)));
        long long n_direito = stoll(pai_str.substr((pai_str.size() / 2)));

        pai->direito = cria_no(n_direito);
        pai->esquerdo = cria_no(n_esquerdo);
        // std::cout << "inserir no 2: " << pai->direito << "/" << pai->esquerdo << std::endl;
        return;
    }
    if (pai_str.size() % 2 == 1)
    {
        long long numero = stoll(pai_str) * 2024;

        pai->esquerdo = cria_no(numero);
        // std::cout << "inserir no 3: " << pai->direito << "/" << pai->esquerdo << std::endl;
    }
}

int altura_arvore(No *raiz)
{
    if (raiz == nullptr)
    {
        return 0;
    }
    // std::cout << raiz->numero_no << " -> ";

    int alt_esq = altura_arvore(raiz->esquerdo);
    int alt_dir = altura_arvore(raiz->direito);
    return std::max(alt_esq, alt_dir) + 1;
}

void libera_no(No *no_ponteiro)
{
    if (no_ponteiro != nullptr)
    {
        libera_no(no_ponteiro->esquerdo);
        libera_no(no_ponteiro->direito);
        no_ponteiro = nullptr;
        // delete no_ponteiro;
    }
}

int main()
{
    std::vector<int> numeros_iniciais;
    std::string linha;
    std::getline(std::cin, linha);

    std::istringstream stream(linha);
    int numero;
    while (stream >> numero)
        numeros_iniciais.push_back(numero);

    // std::cout << numeros_iniciais[0] << "";
    // No *raiz = cria_no(123456);
    // inserir_no(raiz);
    // inserir_no(raiz->esquerdo);
    // inserir_no(raiz->direito);

    // std::cout << "Altura antes da remoção: " << altura_arvore(raiz) << std::endl;

    // Remova um nó específico (ajuste conforme necessário)
    // std::cout << "Removendo nó esquerdo da raiz" << std::endl;
    // libera_no(raiz->esquerdo);
    // raiz->esquerdo = nullptr;

    // std::cout << "Altura após a remoção: " << altura_arvore(raiz) << std::endl;

    // std::cout << "Liberando a árvore inteira" << std::endl;
    // libera_no(raiz); // Libere a memória da árvore
    // raiz = nullptr;
    // std::cout << "Altura após a remoção: " << altura_arvore(raiz) << std::endl;

    // return 0;
    long long cont = 0;
    for (int numero : numeros_iniciais)
    {
        No *raiz = cria_no(numero);
        std::deque<No *> grey;
        // std::vector<No *> black; black, abstração de free, basta ver se o nó é NULL
        grey.push_back(raiz);

        int altura = altura_arvore(raiz);
        while (!grey.empty())
        {
            No *no_atual = grey.back();

            if (!no_atual->visitado)
            {
                inserir_no(no_atual);
                no_atual->visitado = true;
            }

            if (altura_arvore(raiz) < 25)
            {
                std::cout << "7" << std::endl;
                if (no_atual->esquerdo != nullptr)
                {
                    std::cout << "8: " << no_atual->numero_no << std::endl;
                    grey.push_back(no_atual->esquerdo);
                }
                else if (no_atual->direito != nullptr)
                {
                    std::cout << "9" << std::endl;
                    grey.push_back(no_atual->direito);
                }
                else
                {
                    std::cout << "10" << std::endl;
                    libera_no(grey.back());
                    grey.pop_back();
                }
            }
            else
            {
                std::cout << "11" << std::endl;
                libera_no(no_atual);
                // std::cout << "altura: " << altura_arvore(raiz) << std::endl;
                // std::cout << "no_atual:" << no_atual->numero_no << std::endl;
                // std::cout << "grey_back:" << grey.back()->numero_no << std::endl;
                no_atual = nullptr;
                grey.pop_back();
            }
            if (altura_arvore(raiz) == 25)
                cont++;
        }
        std::cout << cont << std::endl;
    }

    return 0;
}
