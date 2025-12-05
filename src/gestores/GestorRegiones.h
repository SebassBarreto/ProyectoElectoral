#ifndef GESTORREGIONES_H
#define GESTORREGIONES_H

#include <iostream>
#include <string>
#include "../../include/listas/Lista.h"
#include "../modelos/Region.h"
#include "GestorArchivos.h"

using namespace std;

class GestorRegiones {
public:
    static bool cargar(const string& ruta, Lista<Region>& lista) {
        lista.limpiar();
        const int CAP = 512;
        string lineas[CAP];
        int n = 0;
        if (!GestorArchivos::leerLineas(ruta, lineas, CAP, n)) return false;

        for (int i = 0; i < n; ++i) {
            const string& s = lineas[i];
            int p1 = (int)s.find('|');
            int p2 = (p1 == -1 ? -1 : (int)s.find('|', p1 + 1));
            if (p1 == -1 || p2 == -1) continue;

            int id = 0;
            string nombre = s.substr(p1 + 1, p2 - p1 - 1);
            string desc = s.substr(p2 + 1);
            try { id = stoi(s.substr(0, p1)); } catch (...) { continue; }

            lista.insertarFinal(Region(id, nombre, desc));
        }
        return true;
    }

    static bool guardar(const string& ruta, const Lista<Region>& lista) {
        int tam = lista.obtenerTamano();
        if (tam <= 0) {
            const string vacio = "";
            return GestorArchivos::escribirArchivoCompleto(ruta, vacio);
        }
        string out[1024];
        int k = 0;
        Region r;
        for (int i = 0; i < tam; ++i) {
            if (!lista.obtenerElemento(i, r)) continue;
            out[k++] = r.toString();
        }
        return GestorArchivos::escribirLineas(ruta, out, k);
    }
};

#endif // GESTORREGIONES_H