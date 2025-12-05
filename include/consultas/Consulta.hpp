#ifndef CONSULTAS_CONSULTA_HPP
#define CONSULTAS_CONSULTA_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "Palavra.hpp"
#include "Logradouro.hpp"
#include "auxi/ArvoreAVL.hpp"
#include "auxi/LogradouroDist.hpp"


class Consulta {
    public:
        Consulta(int id, int numRespostas, std::string consulta, Ponto origem);
        Consulta(std::string linha);
        Consulta();
        void consultar(Palavra* palavra);
        void encontrarLogradouros(ArvoreAVL<int, Logradouro> log);
        void imprimir();

    private:
        int _id, _numRespostas;
        std::string _consulta;
        Ponto _origem;
        Vetor<int> _candidatos;
        Vetor<LogradouroDist> _resultado;

        Vetor<std::string>* _quebrarConsulta();
};

#endif