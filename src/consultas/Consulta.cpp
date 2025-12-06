#include "consultas/Consulta.hpp"


Consulta::Consulta(std::string linha, int numRespostas) 
    : _numRespostas(numRespostas) 
{
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

void Consulta::consultar(Palavra* palavra, ArvoreAVL<int, Logradouro>& log) {
    Vetor<int>* candidatos = this->_buscarCandidatos(palavra);
    Logradouro* l = nullptr;
    LogradouroDist ld;

    if (candidatos == nullptr) return;

    for (int i = 0; i < candidatos->getTamanho(); i++) {
        l = log.buscar(*candidatos->get(i));

        // NOTA: Caso a busca tenha um retorno, é adicionado um novo 
        // LogradouroDist aos candidatos
        if (l != nullptr) {
            double distancia = l->getCentro().distancia(this->_origem);
            ld = {l->getId(), l->getNome(), distancia};

            this->_resultado.inserir(ld);
        }
    }

    delete candidatos;
}

void Consulta::imprimir() {
    int quantImpressoes = (this->_resultado.getTamanho() < this->_numRespostas)
                           ? this->_resultado.getTamanho()
                           : this->_numRespostas;

    std::cout << this->_id << ";" << quantImpressoes << std::endl;

    this->_resultado.ordenar();
    for (int i = 0; i < quantImpressoes; i++) {
        std::cout << this->_resultado.get(i)->idLog << ";"
                  << this->_resultado.get(i)->nomeLog
                  << std::endl;
    }
}

Vetor<int>* Consulta::_buscarCandidatos(Palavra* palavra) {
    Vetor<int>* candidatos = new Vetor<int>();
    Vetor<std::string>* consultas = this->_quebrarConsulta();

    if (consultas == nullptr) {
        delete candidatos;
        return nullptr;
    }

    for (int i = 0; i < consultas->getTamanho(); i++) {
        Vetor<int>* aux = palavra->buscarPalavra(*consultas->get(i));

        // NOTA: Caso uma das buscas não obtenha resultados, não existem 
        // logradouros com todas as palavras esperadas pela consulta.
        if (aux == nullptr) {
            candidatos->limpar();
            break;
        }

        if (candidatos->getTamanho() <= 0) {
            *candidatos = *aux;
            continue;
        }

        Vetor<int>* intersecao = candidatos->mesclarIguais(aux);
        delete candidatos;
        candidatos = intersecao;
    }
    
    delete consultas;
    if (candidatos->getTamanho() <= 0) {
        delete candidatos;
        return nullptr;
    }

    return candidatos;
}

Vetor<std::string>* Consulta::_quebrarConsulta() {
    Vetor<std::string>* palavras = new Vetor<std::string>();
    std::stringstream ss(this->_consulta);
    std::string segmento;

    while (ss >> segmento)
        palavras->inserir(segmento);
    
    if (palavras->getTamanho() <= 0) return nullptr;
    return palavras;
}