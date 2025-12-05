#ifndef GESTORCIUDADES_H
#define GESTORCIUDADES_H

#include <iostream>
#include <string>
#include "../../include/listas/Lista.h"
#include "../modelos/Ciudad.h"
#include "GestorArchivos.h"

using namespace std;

class GestorCiudades {
public:
    static bool cargar(const string& ruta, Lista<Ciudad>& lista) {
        lista.limpiar();
        const int CAP = 1024;
        string lineas[CAP];
        int n = 0;
        if (!GestorArchivos::leerLineas(ruta, lineas, CAP, n)) return false;

        for (int i = 0; i < n; ++i) {
            const string& s = lineas[i];
            int p1 = (int)s.find('|');
            int p2 = (p1 == -1 ? -1 : (int)s.find('|', p1 + 1));
            int p3 = (p2 == -1 ? -1 : (int)s.find('|', p2 + 1));
            if (p1 == -1 || p2 == -1 || p3 == -1) continue;

            int id = 0, idRegion = 0, poblacion = 0;
            string nombre = s.substr(p1 + 1, p2 - p1 - 1);
            try {
                id        = stoi(s.substr(0, p1));
                idRegion  = stoi(s.substr(p2 + 1, p3 - p2 - 1));
                poblacion = stoi(s.substr(p3 + 1));
            } catch (...) { continue; }

            lista.insertarFinal(Ciudad(id, nombre, idRegion, poblacion));
        }
        return true;
    }

    static bool guardar(const string& ruta, const Lista<Ciudad>& lista) {
        int tam = lista.obtenerTamano();
        if (tam <= 0) {
            const string vacio = "";
            return GestorArchivos::escribirArchivoCompleto(ruta, vacio);
        }
        string out[2048];
        int k = 0;
        Ciudad c;
        for (int i = 0; i < tam; ++i) {
            if (!lista.obtenerElemento(i, c)) continue;
            out[k++] = c.toString();
        }
        return GestorArchivos::escribirLineas(ruta, out, k);
    }
};

#endif // GESTORCIUDADES_H