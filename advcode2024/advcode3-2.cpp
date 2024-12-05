#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>

void do_or_dont(std::string do_dont, bool &actual_state)
{
    /* altera o estado da multiplicacao*/
    if (do_dont == "do()")
    {
        actual_state = true;
    }
    if (do_dont == "don't()")
    {
        actual_state = false;
    }
}

int mul_string(const std::string &input)
{
    int number1;
    int number2;
    std::regex pattern(R"(\((\d{1,3}),(\d{1,3})\))");
    std::smatch match;

    if (std::regex_search(input, match, pattern))
    {
        number1 = std::stoi(match[1]); // Primeiro número
        number2 = std::stoi(match[2]); // Segundo número
    }

    return number1 * number2;
}

int main()
{
    std::vector<std::string> strings_mul;
    std::ifstream arquivo("advcode3_mul.txt"); // Abre o arquivo para leitura
    if (!arquivo.is_open())
    { // Verifica se o arquivo foi aberto com sucesso
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    // Lê o conteúdo inteiro do arquivo e armazena em uma string
    std::string big_string((std::istreambuf_iterator<char>(arquivo)),
                           std::istreambuf_iterator<char>());

    arquivo.close(); // Fecha o arquivo

    // extrai o padrão do regex.
    std::smatch match;
    std::regex r(R"(mul[(]\d{1,3}[,]\d{1,3}[)]|(do[(][)])|(don't[(][)]))");
    bool state = true;
    int sum_mul = 0;
    while (regex_search(big_string, match, r))
    {
        if (match.str(0) == "do()" or match.str(0) == "don't()")
        {
            do_or_dont(match.str(0), state);
            big_string = match.suffix().str();
            continue;
        }
        if (state)
            sum_mul += mul_string(match.str(0));
        // Seta para procurar no resto da string.
        big_string = match.suffix().str();
    }

    std::cout << sum_mul << std::endl;

    return 0;
}
