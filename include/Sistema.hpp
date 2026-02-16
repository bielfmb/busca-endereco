#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include "auxi/ArvoreAVL.hpp"
#include "auxi/Vetor.hpp"
#include "auxi/Ponto.hpp"
#include "consultas/Consulta.hpp"
#include "consultas/Endereco.hpp"
#include "consultas/Logradouro.hpp"
#include "consultas/Palavra.hpp"


class Sistema {
    public:
        /**
         * @brief Orquestra a execução do buscador de endereços
         * 
         * @details Após realizar uma tokenização, esta função processa as
         * consultas e imprime os resultados a partir de métodos internos e
         * da classe Consulta.
         */
        void executar();
    
    private:
        /**
         * @brief Cria, a partir da entrada, a ÁrvoreAVL de logradouros retirados
         * dos endereços, além de atualizar a instância principal de Palavra
         * 
         * @param palavra Possui todas as palavras dos nomes de todos os 
         * logradouros e os identificadores deles em que as strings aparecem
         * 
         * @returns Um ponteiro para o vetor dinâmico que contém a árvore de 
         * logradouros, passando para o chamador a responsabilidade de 
         * gerenciamento de memória
         * 
         * @details O TAD de retorno e o passado como parâmetro são construídos 
         * enquanto os endereços são lidos, de forma que a localidade de referência
         * é aproveitada e o programa não precisa armazenar todos os endereços
         */
        ArvoreAVL<int, Logradouro>* _carregarLogradouros(Palavra& palavra);

        /**
         * @brief Cria, a partir da entrada, a lista de consultas solicitadas.
         * 
         * @returns Um ponteiro para o vetor dinâmico que contém as consultas por 
         * logradouros, passando para o chamador a responsabilidade de gerenciar a
         * memória
         */
        Vetor<Consulta>* _carregarConsultas();
};

#endif