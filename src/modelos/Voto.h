#ifndef VOTO_H
#define VOTO_H

#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

/**
 * Tipos de voto según el enunciado:
 * - Valido: voto para un candidato
 * - Blanco: opción 0 en tarjetón
 * - Nulo: voto inválido por marcaciones incorrectas
 * - Abstencion: no emitió voto (se contabiliza para simulación, no es un voto sobre tarjetón)
 */

enum class TipoVoto: uint8_t{
    Valido = 0, Blanco = 1, Nulo = 2, Abstencion = 3
};

struct VotoEvento{
    TipoVoto tipo;
    int idCiudad; //de donde se emite
    int idPartido; //para el candidato (si aplica)
    int idCandidato; //candidato elegido(si aplica -1 en blanco nulo o abstencion)

    VotoEvento(): tipo(TipoVoto::Nulo), idCiudad(-1), idPartido(-1), idCandidato(-1) {}
    VotoEvento(TipoVoto t, int ciudad, int partido);
};


#endif //VOTO_H