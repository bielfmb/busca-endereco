#ifndef CONSULTAS_PALAVRA_HPP
#define CONSULTAS_PALAVRA_HPP

#include <string>
#include <sstream>
#include "auxi/ArvoreAVL.hpp"
#include "auxi/Vetor.hpp"


/**
 * @class Palavra
 * 
 * @brief Utiliza uma Árvore AVL para armazenar uma lista dos logradouros
 * em que uma palavra aparece
 */
class Palavra {
    public:
        /**
         * @brief Construtor de Palavra
         */
        Palavra();

        /**
         * @brief Adiciona uma nova palavra à árvore interna. Caso a string
         * já exista, acresenta o id do logradouro ao dado associado à palavra
         * 
         * @param idLog Id do logradouro relacionado à string
         * @param nome Nome do logradouro (será dividido em palavras individuais)
         */
        void inserirPalavras(int idLog, std::string nomeLog);

        /**
         * @brief Função de callback utilizada para ordenar todos os vetores de 
         * ids dos logradouros na árvore
         */
        void ordenarLogradouros();    

        /**
         * @brief Utiliza o mecanismo de busca da árvore AVL para encontrar
         * os ids dos logradouros que contêm determinada palavra
         * 
         * @param palavra String que se deseja encontrar correspodência 
         */
        Vetor<int>* buscarPalavra(std::string palavra);

    private:
        ArvoreAVL<std::string, Vetor<int>> _palavras; //!< Árvore de busca de 
                                                      // palavras

        /**
         * @brief Utilizado por inserirPalavra para dividir o nome do logradouro
         * em palavras individuais
         * 
         * @param log nome do logradouro que será partido
         * 
         * @returns Um vetor de string com todas as palavras no logradouro
         */
        Vetor<std::string>* _quebrarTermo(std::string log);
};

#endif