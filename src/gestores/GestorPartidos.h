#ifndef GESTORPARTIDOS_H
#define GESTORPARTIDOS_H

#include <string>
#include <iostream>
#include "../../include/listas/Lista.h"
#include "../modelos/Partido.h"
#include "GestorArchivos.h"

using namespace std;

class GestorPartidos {
public:
    static bool cargar(const string& ruta, Lista<Partido>& lista) {
        lista.limpiar();
        const int CAP = 256;
        string lineas[CAP];
        int n = 0;
        if (!GestorArchivos::leerLineas(ruta, lineas, CAP, n)) return false;

        for (int i = 0; i < n; ++i) {
            const string& s = lineas[i];
            int p1 = (int)s.find('|');
            int p2 = (p1 == -1 ? -1 : (int)s.find('|', p1 + 1));
            if (p1 == -1 || p2 == -1) continue;

            string nombre = s.substr(0, p1);
            string rep    = s.substr(p1 + 1, p2 - p1 - 1);
            int id = 0;
            try { id = stoi(s.substr(p2 + 1)); } catch (...) { continue; }

            lista.insertarFinal(Partido(nombre, rep, id));
        }
        return true;
    }

    static bool guardar(const string& ruta, const Lista<Partido>& lista) {
        int tam = lista.obtenerTamano();
        if (tam <= 0) {
            const string vacio = "";
            return GestorArchivos::escribirArchivoCompleto(ruta, vacio);
        }
        string out[512];
        int k = 0;
        Partido p;
        for (int i = 0; i < tam; ++i) {
            if (!lista.obtenerElemento(i, p)) continue;
            out[k++] = p.toFileFormat();
        }
        return GestorArchivos::escribirLineas(ruta, out, k);
    }
};

#endif // GESTORPARTIDOS_H