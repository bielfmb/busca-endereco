#include "consultas/Logradouro.hpp"


Logradouro::Logradouro(int id, 
                       std::string nome, std::string tipo, 
                       Ponto coordenada)
    : _id(id),
      _quant(1),
      _nome(nome),
      _tipo(tipo),
      _coordenada(coordenada) {}

Logradouro::Logradouro() : _id(-1) {}

void Logradouro::inserirCoordenada(Ponto& outro) {
    this->_coordenada.lat += outro.lat;
    this->_coordenada.longi += outro.longi;
    this->_quant++;
}

int Logradouro::getId() { return this->_id; }

std::string Logradouro::getNome() { return this->_nome; }

Ponto Logradouro::getCentro() {
    Ponto centro = {this->_coordenada.lat / this->_quant,
                    this->_coordenada.longi / this->_quant};
    return centro;
}