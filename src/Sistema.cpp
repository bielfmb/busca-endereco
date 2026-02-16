#include "Sistema.hpp"


void Sistema::executar() {
    Palavra* palavra = new Palavra();
    ArvoreAVL<int, Logradouro>* logs = this->_carregarLogradouros(*palavra);
    if (!logs) {
        delete palavra;
        delete logs;
        return;
    }

    Vetor<Consulta>* consultas = this->_carregarConsultas();
    if (!consultas) {
        delete palavra;
        delete logs;
        delete consultas;
        return;
    }

    // NOTA: Para maior eficiência na busca de logradouros compatíveis com
    // as consultas, os vetores de ids de logradouros devem estar ordenados.
    palavra->ordenarLogradouros();

    std::cout << consultas->getTamanho() << std::endl;

    for (int i = 0; i < consultas->getTamanho(); i++) {
        consultas->get(i)->consultar(palavra, *logs);

        consultas->get(i)->imprimir();
    }

    delete palavra;
    delete logs;
    delete consultas;
}

ArvoreAVL<int, Logradouro>* Sistema::_carregarLogradouros(Palavra& palavra) {
    ArvoreAVL<int, Logradouro>* logs = new ArvoreAVL<int, Logradouro>();
    Endereco end;
    std::string endBruto;

    int numEnderecos;
    if (!(std::cin >> numEnderecos)) return nullptr;

    // NOTA: Função usada para limpar a quebra de linha deixada pelo operador 
    // ">>" da última leitura de dados
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numEnderecos; i++) {
        if (std::getline(std::cin, endBruto)) {
            end.criar(endBruto);
            Logradouro* l = logs->buscar(end.idLog);

            // NOTA: Caso não exista um logradouro com o id passado no endereço,
            // um novo é criado e seu nome é inserido em palavras. Senão, apenas
            // as coordendas do logradouro são atualizadas
            if (l == nullptr) {
                l = new Logradouro(end.idLog, 
                                   end.log, 
                                   end.tipoLog, 
                                   end.coordenada);

                logs->inserir(end.idLog, *l);
                palavra.inserirPalavras(end.idLog, end.log);
                
                delete l;
            } 
            else l->inserirCoordenada(end.coordenada);
        }
    }
    return logs;
}

Vetor<Consulta>* Sistema::_carregarConsultas() {
    int numConsultas, maxRespostas;    
    if (!(std::cin >> numConsultas >> maxRespostas)) return nullptr;

    Vetor<Consulta>* consultas = new Vetor<Consulta>();
    std::string consultaBruta;

    // NOTA: Função usada para limpar a quebra de linha deixada pelo operador 
    // ">>" da última leitura de dados
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numConsultas; i++) {
        if (std::getline(std::cin, consultaBruta)) {
            Consulta c(consultaBruta, maxRespostas);
            consultas->inserir(c);
        }
    }
    
    return consultas;
}
