#ifndef CONSULTAS_LOGRADOURO_HPP
#define CONSULTAS_LOGRADOURO_HPP

#include <string>
#include "auxi/Ponto.hpp"


/**
 * @class Logradouro 
 * 
 * @brief Representa uma via pública, como rua, avenida, praça, etc.
 */
class Logradouro {
    public:
        /**
         * @brief Construtor de logradouro
         * 
         * @param id Identificador do logradouro
         * @param nome Nome do logradouro
         * @param tipo Se é uma rua, avenida, praça, etc.
         * @param coordenada Centro do logradouro 
         */
        Logradouro(int id, std::string nome, std::string tipo, Ponto coordenada);

        /**
         * @brief Construtor vazio.
         * 
         * @details Utilizado para construir um objeto "nulo", a fim de
         * poder criar vetores de logradouro sem a necessidade de inicializar
         * todas as posições. Define o id como -1, sinalizando que o objeto
         * não é válido.
         */
        Logradouro();

        /**
         * @brief Adiciona uma nova cooredenada, utilizada para atualizar o 
         * centro do logradouro 
         * 
         * @param outro Ponto que será inserido.
         * 
         * @details Um mesmo logradouro possui vários endereços diferentes. 
         * Esta função soma as latitudes e longitudes atuais às passadas como
         * parâmtro e atualiza a quantidade de endereços do logradouro. Isso 
         * serve para que se possa obter um "ponto médio" (centro) do local
         */
        void inserirCoordenada(Ponto& outro);

        /**
         * @brief Retorna o identificador do logradouro
         */
        int getId();

        /**
         * @brief Retorna o nome do logradouro
         */
        std::string getNome();

        /**
         * @brief Retorna o ponto central do logradouro
         */
        Ponto getCentro();

    private:
        int _id; //!< Identificador do logradouro
        int _quant; //!< Quantidade de endereços neste logradouro
        std::string _nome; //!< Nome do logradouro
        std::string _tipo; //!< Se é uma rua, avenida, praça, etc.
        Ponto _coordenada; //!< Ponto central do logradouro

};

#endif