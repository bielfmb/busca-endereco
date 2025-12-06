#ifndef AUXI_LORADOURODIST_HPP
#define AUXI_LORADOURODIST_HPP

#include <cmath>
#include <string>


/**
 * @struct LogradouroDist
 * 
 * @brief Representa a distância entre um logradouro e uma coordenada
 */
struct LogradouroDist {
    int idLog; //!< Id do logradouro que se busca a distãncia a um ponto
    std::string nomeLog; //!< Nome do logradouro
    double distancia; //!< Distância entre o logradouro e um ponto 

    /**
     * @brief Sobrecarrega o operador "menor que". Retorna se este
     * LogradouroDist é menor que o passado como parâmetro.
     */
    bool operator < (const LogradouroDist& outro) {
        return (this->distancia < outro.distancia);
    }

    /**
     * @brief Sobrecarrega o operador "maior que". Retorna se este
     * LogradouroDist é maior que o passado como parâmetro.
     */
    bool operator > (const LogradouroDist& outro) {
        return (this->distancia > outro.distancia);
    }
    
    /**
     * @brief Sobrecarrega o operador "menor ou igual a". Retorna se este
     * LogradouroDist é menor que o passado como parâmetro.
     */
    bool operator <= (const LogradouroDist& outro) {
        return (this->distancia <= outro.distancia);
    }
};

#endif