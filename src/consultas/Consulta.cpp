#include "consultas/Consulta.hpp"

Consulta::Consulta(int id, int numRespostas, std::string consulta, Ponto origem)
    : _id(id),
      _numRespostas(numRespostas),
      _consulta(consulta),
      _origem(origem) {}

Consulta::Consulta(std::string linha) {
    std::stringstream ss(linha);
    std::string segmento;

    try {
        std::getline(ss, segmento, ';');
        this->_id = std::stoi(segmento);

        std::getline(ss, segmento, ';');
        this->_consulta = segmento;

        std::getline(ss, segmento, ';');
        this->_origem.lat = std::stod(segmento);

        std::getline(ss, segmento, ';');
        this->_origem.longi = std::stod(segmento);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

Consulta::Consulta() : _id(-1), _numRespostas(-1) {}

void Consulta::encontrarLogradouros(ArvoreAVL<int, Logradouro> log) {
    Logradouro* l = nullptr;
    LogradouroDist ld;

    for (int i = 0; i < this->_candidatos.getTamanho(); i++) {
        l = log.buscar(*this->_candidatos.get(i));

        if (l != nullptr) {
            double distancia = l->getCentro().distancia(this->_origem);
            ld = {l->getId(), l->getNome(), distancia};

            this->_resultado.inserir(ld);
        }
    }
}

void Consulta::consultar(Palavra* palavra) {
    Vetor<std::string>* consultas = this->_quebrarConsulta();

    for (int i = 0; i < consultas->getTamanho(); i++) {
        if (this->_candidatos.getTamanho() <= 0) {
            this->_candidatos = *palavra->buscarPalavra(*consultas->get(i));
            continue;
        }
        
        Vetor<int>* aux = palavra->buscarPalavra(*consultas->get(i));
        this->_candidatos = *this->_candidatos.mesclarIguais(aux);
    }
    
    delete consultas;
}

void Consulta::imprimir() {
    std::cout << this->_id << this->_resultado.getTamanho() << std::endl;

    this->_resultado.ordenar();
    for (int i = 0; i < _numRespostas; i++) {
        std::cout << this->_resultado.get(i)->idLog << ";"
                  << this->_resultado.get(i)->nomeLog
                  << std::endl;
    }
}

Vetor<std::string>* Consulta::_quebrarConsulta() {
    Vetor<std::string>* palavras = new Vetor<std::string>();
    std::stringstream ss(this->_consulta);
    std::string segmento;

    while (ss >> segmento)
        palavras->inserir(segmento);
    
    return palavras;
}