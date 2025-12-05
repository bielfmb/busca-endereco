#ifndef CONSULTAS_ENDERECO_HPP
#define CONSULTAS_ENDERECO_HPP

#include <iostream>
#include <string>
#include <sstream>


enum Regiao {
    BARREIRO,
    CENTRO_SUL,
    LESTE,
    NORDESTE,
    NOROESTE,
    NORTE,
    OESTE,
    PAMPULHA, 
    VENDA_NOVA
};

struct Endereco {
    int idEnd, idLog;
    int num;
    int CEP;
    Ponto coordenada;
    std::string tipoLog, log;
    std::string bairro;
    Regiao regiao;

    void criar(const std::string& linha) {
        std::stringstream ss(linha);
        std::string segmento;

        try {
            std::getline(ss, segmento, ';'); 
            idEnd = std::stoi(segmento);

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
            regiao = getRegiao(segmento);

            std::getline(ss, segmento, ';');
            CEP = std::stoi(segmento); 

            std::getline(ss, segmento, ';');
            coordenada.lat = std::stod(segmento);
            
            std::getline(ss, segmento, ';'); 
            coordenada.longi = std::stod(segmento);
        } catch (const std::exception& e) {
            std::cerr << "Erro fatal ao criar Endereco: " << e.what() << ". Dados incompletos ou inválidos." << std::endl;
        }
    }

    Regiao getRegiao(std::string segmento) {
        if (segmento == "BARREIRO")
            return Regiao::BARREIRO;
        else if (segmento == "CENTRO-SUL")
            return Regiao::CENTRO_SUL;
        else if (segmento == "LESTE")
            return Regiao::LESTE;
        else if (segmento == "NORDESTE")
            return Regiao::NORDESTE;
        else if (segmento == "NOROESTE")
            return Regiao::NOROESTE;
        else if (segmento == "NORTE")
            return Regiao::NORTE;
        else if (segmento == "OESTE")
            return Regiao::OESTE;
        else if (segmento == "PAMPULHA")
            return Regiao::PAMPULHA;
        else if (segmento == "VENDA-NOVA")
            return Regiao::VENDA_NOVA;
    }
};

#endif