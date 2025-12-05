#ifndef ESCRUTINIO_H
#define ESCRUTINIO_H

#include <iostream>
#include <string>
#include "../../include/listas/Lista.h"
#include "../sistema/SistemaElectoral.h"
#include "../modelos/ResultadoElectoral.h"
#include "../gestores/GestorArchivos.h"

using namespace std;

class Escrutinio {
public:
    static bool escribirResultadosAlcaldiaPorCiudad(const string& ruta, const string& nombreCiudad, const ResultadoElectoral& res) {
        string out[64];
        int k = 0;
        out[k++] = string("CIUDAD: ") + nombreCiudad;
        out[k++] = string("Censo: ") + to_string(res.getCensoElectoral());
        out[k++] = string("Emitidos: ") + to_string(res.getTotalVotosEmitidos());
        out[k++] = string("Abstencion: ") + to_string(res.getAbstencion());
        out[k++] = string("Votos nulos: ") + to_string(res.getVotosNulos());
        out[k++] = string("Votos en blanco: ") + to_string(res.getVotosEnBlanco());
        out[k++] = string("Ganador: ") + res.getGanador();
        return GestorArchivos::escribirLineas(ruta, out, k);
    }

    static bool escribirResultadosPresidenciaPais(const string& ruta, const ResultadoElectoral& res) {
        string out[64];
        int k = 0;
        out[k++] = string("PAIS");
        out[k++] = string("Censo: ") + to_string(res.getCensoElectoral());
        out[k++] = string("Emitidos: ") + to_string(res.getTotalVotosEmitidos());
        out[k++] = string("Abstencion: ") + to_string(res.getAbstencion());
        out[k++] = string("Votos nulos: ") + to_string(res.getVotosNulos());
        out[k++] = string("Votos en blanco: ") + to_string(res.getVotosEnBlanco());
        out[k++] = string("Ganador: ") + res.getGanador();
        out[k++] = string("Segunda vuelta: ") + string(res.getRequiereSegundaVuelta() ? "SI" : "NO");
        return GestorArchivos::escribirLineas(ruta, out, k);
    }
};

#endif // ESCRUTINIO_H