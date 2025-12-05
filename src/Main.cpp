#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "auxi/ArvoreAVL.hpp"
#include "auxi/Vetor.hpp"
#include "auxi/Ponto.hpp"
#include "consultas/Consulta.hpp"
#include "consultas/Endereco.hpp"
#include "consultas/Logradouro.hpp"
#include "consultas/Palavra.hpp"

ArvoreAVL<int, Logradouro>* carregarLogradouros(std::ifstream& entrada, Palavra& palavra) {
    ArvoreAVL<int, Logradouro>* logs = new ArvoreAVL<int, Logradouro>();
    Endereco end;
    std::string endBruto;

    int numEnderecos;
    if (!(entrada >> numEnderecos)) return nullptr;

    for (int i = 0; i < numEnderecos; i++) {
        if (std::getline(entrada, endBruto)) {
            end.criar(endBruto);
            Logradouro* l = logs->buscar(end.idLog);

            if (l == nullptr) {
                l = new Logradouro(end.idLog, end.log, end.tipoLog, end.coordenada);
                logs->inserir(end.idLog, *l);
                palavra.inserirPalavras(end.idLog, end.log);
            } 
            else 
                l->inserirCoordenada(end.coordenada);
        }
    }
    return logs;
}

Vetor<Consulta>* carregarConsultas(std::ifstream& entrada) {
    int numConsultas, maxRespostas;    
    if (!(entrada >> numConsultas >> maxRespostas)) return nullptr;

    Vetor<Consulta>* consultas = new Vetor<Consulta>();
    std::string consultaBruta;

    for (int i = 0; i < numConsultas; i++) {
        if (std::getline(entrada, consultaBruta)) {
            Consulta c(consultaBruta);
            consultas->inserir(c);
        }
    }
    
    return consultas;
}

int main(int argc, char* argv[]) {
    const char* nomeArquivo = argv[1];

    std::ifstream entrada;
    entrada.open(nomeArquivo);

    if (!entrada.is_open()) return 1;

    Palavra* palavra = new Palavra();
    ArvoreAVL<int, Logradouro>* logs = carregarLogradouros(entrada, *palavra);
    Vetor<Consulta>* consultas = carregarConsultas(entrada);

    palavra->ordenarLogradouros();

    for (int i = 0; i < consultas->getTamanho(); i++) {
        consultas->get(i)->consultar(palavra);
        consultas->get(i)->encontrarLogradouros(*logs);

        consultas->get(i)->imprimir();
    }

    delete palavra;
    delete logs;
    delete consultas;

    entrada.close();
    return 0;
}