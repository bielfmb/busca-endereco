#ifndef AUXI_PONTO_HPP
#define AUXI_PONTO_HPP

#include <cmath>


/**
 * @struct Ponto
 * 
 * @brief Representa uma coordenada em um plano (mapa)
 */
struct Ponto {
    double lat, longi; //!< Posição no plano

    /**
     * @brief Calcula a distância euclidiana entre dois pontos.
     * 
     * @param ponto Coordenada que se deseja calcular a distância.
     */
    double distancia(const Ponto& ponto) {
        return sqrt(pow(lat - ponto.lat, 2) + pow(longi - ponto.longi, 2));
    }
};

#endif