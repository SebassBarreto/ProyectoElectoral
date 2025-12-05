#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <iostream>
#include <string>
#include "../../include/listas/Lista.h"
#include "../sistema/SistemaElectoral.h"
#include "../indices/MultilistaElectoral.h"
#include "../gestores/GestorArchivos.h"

using namespace std;

class Estadisticas {
public:
    // total censo por region
    static void estadisticaCensoPorRegion(SistemaElectoral& sys, const string& rutaOut) {
        Lista<int> regiones;
        sys.getMultilistaElectoral().listarRegiones(regiones);
        string lines[512];
        int k = 0;
        for (int i = 0; i < regiones.obtenerTamano(); ++i) {
            int idRegion;
            if (!regiones.obtenerElemento(i, idRegion)) continue;
            Lista<int>* ciudades = sys.getMultilistaElectoral().obtenerCiudadesDeRegion(idRegion);
            int censoRegion = 0;
            if (ciudades != NULL) {
                for (int j = 0; j < ciudades->obtenerTamano(); ++j) {
                    int idCiudad;
                    if (!ciudades->obtenerElemento(j, idCiudad)) continue;
                    Ciudad c;
                    if (!obtenerCiudadPorId(sys, idCiudad, c)) continue;
                    censoRegion += c.getPoblacion();
                }
            }
            lines[k++] = string("Region ") + to_string(idRegion) + "|Censo|" + to_string(censoRegion);
        }
        GestorArchivos::escribirLineas(rutaOut, lines, k);
    }

private:
    static bool obtenerCiudadPorId(SistemaElectoral& sys, int idCiudad, Ciudad& out) {
        int n = sys.getCiudades().obtenerTamano();
        for (int i = 0; i < n; ++i) {
            Ciudad c;
            if (!sys.getCiudades().obtenerElemento(i, c)) continue;
            if (c.getId() == idCiudad) { out = c; return true; }
        }
        return false;
    }
};

#endif // ESTADISTICAS_H