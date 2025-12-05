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
        Consulta(std::string linha, int numRespostas);
        Consulta();
        void consultar(Palavra* palavra, ArvoreAVL<int, Logradouro>& log);
        void imprimir();

    private:
        int _id, _numRespostas;
        std::string _consulta;
        Ponto _origem;
        Vetor<LogradouroDist> _resultado;

        Vetor<int>* _buscarCandidatos(Palavra* palavra);
        Vetor<std::string>* _quebrarConsulta();
};

#endif