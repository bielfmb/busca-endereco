#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "auxi/doctest.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Sistema.hpp"

/**
 * @brief Compara se, a partir do arquivo de entrada, o programa gera uma saída
 * idêntica à esperada.
 * 
 * @param arqEntrada Nome do arquivo com os dados de entrada
 * @param arqSaida Nome do arquivo com a saída esperada
 */
bool compararSaidas(std::string arqEntrada, std::string arqSaida) {
    Sistema s;
    std::ifstream entrada(arqEntrada);

    if (!entrada.is_open()) { return false; }

    std::streambuf* cinBackup = std::cin.rdbuf(entrada.rdbuf());

    std::stringstream saidaSimulada;
    std::streambuf* coutBackup = std::cout.rdbuf(saidaSimulada.rdbuf());

    s.executarSistema();

    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    std::ifstream saidaEsperada(arqSaida);
    if (!saidaEsperada.is_open()) { return false; }

    std::stringstream bufferEsperado;
    bufferEsperado << saidaEsperada.rdbuf();

    return saidaSimulada.str() == bufferEsperado.str();
}

TEST_CASE("Exemplos correspondem a saida do programa.") {
    SUBCASE("Entrada 1") 
        CHECK(compararSaidas("tests/exemplos/entrada_1.txt", 
                             "tests/exemplos/saida_1.txt")
                              == true);

    SUBCASE("Entrada 2")
        CHECK(compararSaidas("tests/exemplos/entrada_2.txt", 
                             "tests/exemplos/saida_2.txt")
                              == true);

    SUBCASE("Entrada 3")
        CHECK(compararSaidas("tests/exemplos/entrada_3.txt", 
                             "tests/exemplos/saida_3.txt")
                              == true);
}