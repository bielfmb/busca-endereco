#ifndef CONSULTAS_CONSULTA_HPP
#define CONSULTAS_CONSULTA_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "Palavra.hpp"
#include "Logradouro.hpp"
#include "auxi/ArvoreAVL.hpp"
#include "auxi/LogradouroDist.hpp"


/**
 * @class Consulta
 * 
 * @brief Utiliza informações de Logradouro e Palavra para buscar os locais
 * mais próximos do pedido do cliente.
 */
class Consulta {
    public:
        /**
         * @brief Construtor de consulta.
         * 
         * @param linha Todas as informações necessárias para a consulta, como 
         * id, nome e coordenada do pedido, separados por ponto e vírgula
         * @param numRespostas Quantidade máxima de endereços compatíveis com
         * o pedido
         */
        Consulta(std::string linha, int numRespostas);

        /**
         * @brief Construtor vazio.
         * 
         * @details Utilizado para construir um objeto "nulo", a fim de
         * poder criar vetores de consultas sem a necessidade de inicializar
         * todas as posições. Define o id e o máximo de respostas como -1, 
         * sinalizando que o pedido não é válido.
         */
        Consulta();

        /**
         * @brief Verifica se um ou mais logradouros correspondem à consulta, 
         * criando um vetor de LogradouroDist no processo.
         * 
         * @param palavra Objeto de que se retirará os ids dos logradouros 
         * que contêm todas as palavras a consulta.
         * @param log Árvore utilizada para encontrar os logradouros 
         * correspondentes encontrados através de palavra
         */
        void consultar(Palavra* palavra, ArvoreAVL<int, Logradouro>& log);

        /**
         * @brief Escreve no terminal o resultado da consulta
         */
        void imprimir();

    private:
        int _id; //!< Identificador da consulta
        int _numRespostas; //!< Quantidade máxima de respostas da consulta
        std::string _consulta; //!< Trecho do nome do logradouro que será buscado
        Ponto _origem; //!< Coordenada do pedido
        Vetor<LogradouroDist> _resultado; //!< Logradouros compatíveis

        /**
         * @brief Utilizado por consultar para encontrar logradouros
         * com todas as palavras do pedido do cliente
         * 
         * @param palavra Objeto de que se retirará os ids dos logradouros 
         * que contêm todas as palavras a consulta.
         * 
         * @returns Vetor criado dinamicamente com os ids dos logradouros 
         * candidatos, passando para o chamador a responsabilidade de 
         * gerenciamento de memória 
         */
        Vetor<int>* _buscarCandidatos(Palavra* palavra);

        /**
         * @brief Divide as palavras da consulta para uma busca eficiente
         * 
         * @returns Vetor com todas as palavras do pedido criado de forma 
         * dinâmica, passando para o chamador a responsabilidade de 
         * gerenciamento de memória
         */
        Vetor<std::string>* _quebrarConsulta();
};

#endif