#ifndef CONSULTAS_PALAVRA_HPP
#define CONSULTAS_PALAVRA_HPP

#include <string>
#include <sstream>
#include "auxi/ArvoreAVL.hpp"
#include "auxi/Vetor.hpp"

class Palavra {
    public:
        Palavra();
        ~Palavra();

        void inserirPalavras(int idLog, std::string nomeLog);
        void ordenarLogradouros();    
        Vetor<int>* buscarPalavra(std::string palavra);
    private:
        ArvoreAVL<std::string, Vetor<int>> _palavras;

        Vetor<std::string>* _quebrarTermo(std::string log);

};

#endif