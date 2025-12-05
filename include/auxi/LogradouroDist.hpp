#ifndef AUXI_LORADOURODIST_HPP
#define AUXI_LORADOURODIST_HPP

#include <cmath>
#include <string>

struct LogradouroDist {
    int idLog;
    std::string nomeLog;
    double distancia;

    bool operator < (const LogradouroDist& other) {
        return (this->distancia < other.distancia);
    }

    bool operator > (const LogradouroDist& other) {
        return (this->distancia > other.distancia);
    }

    bool operator <= (const LogradouroDist& other) {
        return (this->distancia <= other.distancia);
    }
};

#endif