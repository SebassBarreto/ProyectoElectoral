#ifndef VOTO_H
#define VOTO_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>

using namespace std;

/**
 * Tipos de voto según el enunciado:
 * - Valido: voto para un candidato
 * - Blanco: opción 0 en tarjetón
 * - Nulo: voto inválido por marcaciones incorrectas
 * - Abstencion: no emitió voto (se contabiliza para simulación, no es un voto sobre tarjetón)
 */

enum class TipoVoto : uint8_t {
    Valido = 0,
    Blanco = 1,
    Nulo   = 2,
    Abstencion = 3
};

class Voto{
private:
    int idCiudad; // ciudad donde se emite (censo y agregacion por region)
    int idPartido;
    int idCandidato;
    TipoVoto tipo;
    char sexo; //M o F segun solicitado para estadisticas por genero

public: 
    Voto(): idCiudad(-1), idPartido(0), idCandidato(-1), tipo(TipoVoto::Nulo), sexo('M'){}

    //voto valido (candidato elegido)
    Voto(int ciudad, int partido, int candidato, char sexoV): idCiudad(ciudad), idPartido(partido), idCandidato(candidato),
    tipo(TipoVoto::Valido), sexo(sexoV){}

    //voto blanco/nulo/abstencion (sin candidato - partido)
    Voto(TipoVoto t, int ciudad, char sexoV): idCiudad(ciudad), idPartido(0), idCandidato(-1), tipo(t), sexo(sexoV) {}

    //getters
    int getIdCiudad() const{ 
        return idCiudad;
    }

    int getIdPartido() const{
        return idPartido;
    }

    int getIdCandidato() const{
        return idCandidato;
    }

    TipoVoto getTipo() const{
        return tipo;
    }

    char getSexo() const{
        return sexo;
    }

    //setters
    void setIdCiudad(int c){
        idCiudad = c;
    }
    void setIdPartido(int p){
        idPartido = p;
    }
    void setIdCandidato(int c){
        idCandidato = c;
    }
    void setTipo(TipoVoto t){
        tipo = t;
    }
    void setSexo(char s){
        sexo = s;
    }

    //utilidades
    static const char* tipoStr(TipoVoto t){
        switch(t){
            case TipoVoto::Valido:  return "VALIDO";
            case TipoVoto::Blanco:  return "BLANCO";
            case TipoVoto::Nulo:  return "NULO";
            case TipoVoto::Abstencion:  return "ABSTENCION";
        }
        return "DESCONOCIDO";
    }

    static char tipoChar(TipoVoto t) {
        switch (t) {
            case TipoVoto::Valido:     return 'V';
            case TipoVoto::Blanco:     return 'B';
            case TipoVoto::Nulo:       return 'N';
            case TipoVoto::Abstencion: return 'X';
        }
        return '?';
    }

};


#endif //VOTO_H