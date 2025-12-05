#ifndef CONSULTAS_LOGRADOURO_HPP
#define CONSULTAS_LOGRADOURO_HPP

#include <string>
#include "auxi/Ponto.hpp"


class Logradouro {
    public:
        Logradouro(int id, std::string nome, std::string tipo, Ponto coordenada);
        Logradouro();

        void inserirCoordenada(Ponto& outro);
        int getId();
        std::string getNome();
        Ponto getCentro();

    private:
        int _id;
        int _quant;
        std::string _nome, _tipo;
        Ponto _coordenada;

};

#endif