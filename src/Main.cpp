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

ArvoreAVL<int, Logradouro>* carregarLogradouros(Palavra& palavra) {
    ArvoreAVL<int, Logradouro>* logs = new ArvoreAVL<int, Logradouro>();
    Endereco end;
    std::string endBruto;

    int numEnderecos;
    if (!(std::cin >> numEnderecos)) return nullptr;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < numEnderecos; i++) {
        if (std::getline(std::cin, endBruto)) {
            end.criar(endBruto);
            Logradouro* l = logs->buscar(end.idLog);

            if (l == nullptr) {
                l = new Logradouro(end.idLog, end.log, end.tipoLog, end.coordenada);
                logs->inserir(end.idLog, *l);
                palavra.inserirPalavras(end.idLog, end.log);
                
                delete l;
            } 
            else l->inserirCoordenada(end.coordenada);
        }
    }
    return logs;
}

Vetor<Consulta>* carregarConsultas() {
    int numConsultas, maxRespostas;    
    if (!(std::cin >> numConsultas >> maxRespostas)) return nullptr;

    Vetor<Consulta>* consultas = new Vetor<Consulta>();
    std::string consultaBruta;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < numConsultas; i++) {
        if (std::getline(std::cin, consultaBruta)) {
            Consulta c(consultaBruta, maxRespostas);
            consultas->inserir(c);
        }
    }
    
    return consultas;
}

int main() {
    Palavra* palavra = new Palavra();
    ArvoreAVL<int, Logradouro>* logs = carregarLogradouros(*palavra);
    Vetor<Consulta>* consultas = carregarConsultas();

    palavra->ordenarLogradouros();

    std::cout << consultas->getTamanho() << std::endl;

    for (int i = 0; i < consultas->getTamanho(); i++) {
        consultas->get(i)->consultar(palavra, *logs);

        consultas->get(i)->imprimir();
    }

    delete palavra;
    delete logs;
    delete consultas;

    return 0;
}