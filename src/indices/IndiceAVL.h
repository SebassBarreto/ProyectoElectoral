#ifndef INDICEAVL_H
#define INDICEAVL_H

#include <iostream>
#include <string>
#include "../../include/arboles/ArbolAVL.h"
#include "../../include/listas/Lista.h"
#include "../gestores/GestorArchivos.h"
using namespace std;

struct IndiceEntry {
    std::string clave;
    int referencia;    
    IndiceEntry() : clave(""), referencia(-1) {}
    IndiceEntry(const string& k, int r) : clave(k), referencia(r) {}
    bool operator<(const IndiceEntry& o) const { return clave < o.clave; }
    bool operator>(const IndiceEntry& o) const { return clave > o.clave; }
    bool operator==(const IndiceEntry& o) const { return clave == o.clave; }
    std::string toFileLine() const { return clave + "|" + to_string(referencia); }
    static bool fromFileLine(const std::string& line, IndiceEntry& out) {
        size_t p = line.find('|');
        if (p == string::npos) return false;
        out.clave = line.substr(0, p);
        try { out.referencia = std::stoi(line.substr(p + 1)); }
        catch (...) { return false; }
        return true;
    }
};

class IndiceAVL {
private:
    ArbolAVL<IndiceEntry> arbol;
    Lista<IndiceEntry> registros; 
public:
    IndiceAVL() {}
    ~IndiceAVL() { limpiar(); }

    bool insertar(const string& clave, int referencia) {
        IndiceEntry e(clave, referencia);
        if (registros.existe(e)) {
            
            int pos = registros.buscar(e);
            if (pos != -1) {
                IndiceEntry tmp;
                registros.obtenerElemento(pos, tmp);
                tmp.referencia = referencia;
                registros.eliminarEnPosicion(pos);
                registros.insertarEnPosicion(tmp, pos);
            }
            return true;
        }
        arbol.insertar(e);
        registros.insertarFinal(e);
        return true;
    }

    bool buscar(const string& clave, int& referenciaOut) const {
        IndiceEntry key(clave, 0);
        if (!arbol.buscar(key)) return false;
      
        Lista<IndiceEntry>* mutableReg = const_cast<Lista<IndiceEntry>*>(&registros);
        int tam = mutableReg->obtenerTamano();
        IndiceEntry tmp;
        for (int i = 0; i < tam; ++i) {
            mutableReg->obtenerElemento(i, tmp);
            if (tmp.clave == clave) {
                referenciaOut = tmp.referencia;
                return true;
            }
        }
        return false;
    }

    bool eliminar(const string& clave) {
        IndiceEntry key(clave, 0);
        if (!arbol.eliminar(key)) return false;
      
        IndiceEntry tmp;
        int tam = registros.obtenerTamano();
        for (int i = 0; i < tam; ++i) {
            if (!registros.obtenerElemento(i, tmp)) continue;
            if (tmp.clave == clave) {
                registros.eliminarEnPosicion(i);
                return true;
            }
        }
        return true;
    }

    bool guardarEnArchivo(const string& ruta) {
        int tam = registros.obtenerTamano();
        if (tam == 0) {
            return GestorArchivos::escribirArchivoCompleto(ruta, string(""));
        }
        string out[4096];
        int k = 0;
        IndiceEntry tmp;
        for (int i = 0; i < tam; ++i) {
            registros.obtenerElemento(i, tmp);
            out[k++] = tmp.toFileLine();
        }
        return GestorArchivos::escribirLineas(ruta, out, k);
    }

    bool cargarDesdeArchivo(const string& ruta) {
        registros.limpiar();
        arbol.limpiar();
        const int CAP = 8192;
        string lines[CAP];
        int n = 0;
        if (!GestorArchivos::leerLineas(ruta, lines, CAP, n)) return false;
        for (int i = 0; i < n; ++i) {
            IndiceEntry e;
            if (!IndiceEntry::fromFileLine(lines[i], e)) continue;
            arbol.insertar(e);
            registros.insertarFinal(e);
        }
        return true;
    }

    void limpiar() {
        registros.limpiar();
        arbol.limpiar();
    }
};

#endif // INDICEAVL_H

