#ifndef CONSULTAS_ENDERECO_HPP
#define CONSULTAS_ENDERECO_HPP

#include <iostream>
#include <string>
#include <sstream>


/**
 * @struct Endereco
 * 
 * @brief Possui todos os dados de um enedereço físico.
 * Utilizado para compor as instâncias de Palavra e Logradouro
 */
struct Endereco {
    std::string idEnd; //!< Identificador do endereço
    int idLog; //!< Identificador do logradouro
    int num; //!< Número da residência
    int CEP; //!< Código de Endereçamento Postal do endereço 
    Ponto coordenada; //!< Latitude e logitude do endereço
    std::string tipoLog; //!< Se o logradouro é uma rua, avenida, praça, etc.
    std::string log; //!< Nome do logradouro
    std::string bairro, regiao; //!< Bairro do endereço (não log) e sua região

    /**
     * @brief Popula os dados do endereço a partir de uma string, separando os
     * dados por ponto e vírgula
     * 
     * @param linha Endereço bruto passado pela entrada 
     */
    void criar(std::string& linha) {
        std::stringstream ss(linha);
        std::string segmento;

        try {
            std::getline(ss, segmento, ';'); 
            idEnd = segmento;

            std::getline(ss, segmento, ';');
            idLog = std::stoi(segmento);
            
            std::getline(ss, segmento, ';');
            tipoLog = segmento;
            
            std::getline(ss, segmento, ';');
            log = segmento;
            
            std::getline(ss, segmento, ';');
            num = std::stoi(segmento);
            
            std::getline(ss, segmento, ';');
            bairro = segmento;
            
            std::getline(ss, segmento, ';');
            regiao = segmento;

            std::getline(ss, segmento, ';');
            CEP = std::stoi(segmento); 

            std::getline(ss, segmento, ';');
            coordenada.lat = std::stod(segmento);
            
            std::getline(ss, segmento, ';'); 
            coordenada.longi = std::stod(segmento);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

#endif