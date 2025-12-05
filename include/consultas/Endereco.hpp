#ifndef CONSULTAS_ENDERECO_HPP
#define CONSULTAS_ENDERECO_HPP

#include <iostream>
#include <string>
#include <sstream>


struct Endereco {
    std::string idEnd;
    int idLog;
    int num;
    int CEP;
    Ponto coordenada;
    std::string tipoLog, log;
    std::string bairro, regiao;

    void criar(const std::string& linha) {
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
            std::cerr << "Erro fatal ao criar Endereco: " << e.what() << ". Dados incompletos ou inválidos." << std::endl;
        }
    }
};

#endif