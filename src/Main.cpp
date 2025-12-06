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


/**
 * @brief Cria, a partir da entrada, a ÁrvoreAVL de logradouros retirados
 * dos endereços, além da instância principal de Palavra
 * 
 * @param palavra Possui todas as palavras dos nomes de todos os logradouros
 * e os identificadores deles em que as strings aparecem
 * 
 * @returns Um ponteiro para o vetor dinâmico que contém a árvore de 
 * logradouros, passando para o chamador a responsabilidade de gerenciamento
 * de memória
 * 
 * @details O TAD de retorno e o passado como parâmetro são construídos 
 * enquanto os endereços são lidos, de forma que a localidade de referência é
 * aproveitada e o programa não precisa armazenar todos os endereços
 */
ArvoreAVL<int, Logradouro>* carregarLogradouros(Palavra& palavra) {
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

/**
 * @brief Cria, a partir da entrada, a lista de consultas solicitadas.
 * 
 * @returns Um ponteiro para o vetor dinâmico que contém as consultas por 
 * logradouros, passando para o chamador a responsabilidade de gerenciar a
 * memória
 */
Vetor<Consulta>* carregarConsultas() {
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

int main() {
    Palavra* palavra = new Palavra();
    ArvoreAVL<int, Logradouro>* logs = carregarLogradouros(*palavra);
    Vetor<Consulta>* consultas = carregarConsultas();

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

    return 0;
}