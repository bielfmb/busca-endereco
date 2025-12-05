#include "consultas/Palavra.hpp"


Palavra::Palavra() {}

Palavra::~Palavra() {}

void Palavra::inserirPalavras(int idLog, std::string nomeLog) {
    Vetor<std::string>* logs = this->_quebrarTermo(nomeLog);

    for (int i = 0; i < logs->getTamanho(); i++) {
        Vetor<int>* busca = this->_palavras.buscar(*logs->get(i));

        if (busca != nullptr) busca->inserir(idLog);
        else {
            Vetor<int> novosIds;
            novosIds.inserir(idLog);
            this->_palavras.inserir(*logs->get(i), novosIds);
        };
    }

    delete logs;
}

void ordenarCallback(std::string& palavra, Vetor<int>& logs, void* contexto) {
    logs.ordenar();
}

void Palavra::ordenarLogradouros() {
    this->_palavras.paraCadaNo(ordenarCallback, nullptr);
}

Vetor<int>* Palavra::buscarPalavra(std::string palavra) {
    Vetor<int>* busca = this->_palavras.buscar(palavra);

    return busca;
}

Vetor<std::string>* Palavra::_quebrarTermo(std::string log) {
    Vetor<std::string>* logs = new Vetor<std::string>();
    std::stringstream ss(log);
    std::string segmento;

    while (ss >> segmento)
        logs->inserir(segmento);
    
    return logs;
}