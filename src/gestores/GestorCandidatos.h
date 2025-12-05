#ifndef GESTORCANDIDATOS_H
#define GESTORCANDIDATOS_H

#include <iostream>
#include <string>
#include "../../include/listas/Lista.h"
#include "../modelos/Candidato.h"
#include "GestorArchivos.h"

using namespace std;

class GestorCandidatos {
private:
    static bool parseLinea(const string& s, Candidato& out) {
        int pos[12];
        int count = 0;
        for (int i = 0; i < (int)s.size() && count < 12; ++i) {
            if (s[i] == '|') pos[count++] = i;
        }
        if (count < 12) return false;

        string nombre      = s.substr(0, pos[0]);
        string apellido    = s.substr(pos[0] + 1, pos[1] - pos[0] - 1);
        string id          = s.substr(pos[1] + 1, pos[2] - pos[1] - 1);
        char sexo               = s[pos[2] + 1];
        string estadoCivil = s.substr(pos[3] + 1, pos[4] - pos[3] - 1);

        int dia = 0, mes = 0, anio = 0;
        try {
            dia  = stoi(s.substr(pos[4] + 1, pos[5] - pos[4] - 1));
            mes  = stoi(s.substr(pos[5] + 1, pos[6] - pos[5] - 1));
            anio = stoi(s.substr(pos[6] + 1, pos[7] - pos[6] - 1));
        } catch (...) { return false; }

        string ciudadNac   = s.substr(pos[7] + 1, pos[8] - pos[7] - 1);
        string ciudadRes   = s.substr(pos[8] + 1, pos[9] - pos[8] - 1);
        string partido     = s.substr(pos[9] + 1, pos[10] - pos[9] - 1);
        string tipo        = s.substr(pos[10] + 1, pos[11] - pos[10] - 1);
        string vice        = s.substr(pos[11] + 1);

        bool pres = (tipo == "P");
        out = Candidato(nombre, apellido, id, sexo, estadoCivil,
                        dia, mes, anio, ciudadNac, ciudadRes, partido, pres, vice);
        return true;
    }

public:
    static bool cargarAlcaldia(const string& ruta, Lista<Candidato>& lista) {
        lista.limpiar();
        const int CAP = 2048;
        string lineas[CAP];
        int n = 0;
        if (!GestorArchivos::leerLineas(ruta, lineas, CAP, n)) return false;

        for (int i = 0; i < n; ++i) {
            const string& s = lineas[i];
            Candidato c;
            if (!parseLinea(s, c)) continue;
            if (!c.getEsPresidencial()) {
                lista.insertarFinal(c);
            }
        }
        return true;
    }

    static bool cargarPresidencia(const string& ruta, Lista<Candidato>& lista) {
        lista.limpiar();
        const int CAP = 256;
        string lineas[CAP];
        int n = 0;
        if (!GestorArchivos::leerLineas(ruta, lineas, CAP, n)) return false;

        for (int i = 0; i < n; ++i) {
            const string& s = lineas[i];
            Candidato c;
            if (!parseLinea(s, c)) continue;
            if (c.getEsPresidencial()) {
                lista.insertarFinal(c);
            }
        }
        return true;
    }

    static bool guardar(const string& ruta, const Lista<Candidato>& lista) {
        int tam = lista.obtenerTamano();
        if (tam <= 0) {
            const string vacio = "";
            return GestorArchivos::escribirArchivoCompleto(ruta, vacio);
        }
        string out[4096];
        int k = 0;
        Candidato c;
        for (int i = 0; i < tam; ++i) {
            if (!lista.obtenerElemento(i, c)) continue;
            out[k++] = c.toFileFormat();
        }
        return GestorArchivos::escribirLineas(ruta, out, k);
    }
};

#endif // GESTORCANDIDATOS_H