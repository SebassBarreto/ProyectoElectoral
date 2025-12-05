#ifndef INDICEAVL_H
#define INDICEAVL_H

#include <string>
#include "../../include/arboles/ArbolAVL.h"
#include "../../include/listas/Lista.h"
#include "../gestores/GestorArchivos.h"

struct IndiceEntry {
    std::string clave; // ej: "Candidato:100101" o "Ciudad:3"
    int referencia;    // por ejemplo posición en Lista<>, o id numérico
    IndiceEntry() : clave(""), referencia(-1) {}
    IndiceEntry(const std::string& k, int r) : clave(k), referencia(r) {}
    bool operator<(const IndiceEntry& o) const { return clave < o.clave; }
    bool operator>(const IndiceEntry& o) const { return clave > o.clave; }
    bool operator==(const IndiceEntry& o) const { return clave == o.clave; }
    std::string toFileLine() const { return clave + "|" + std::to_string(referencia); }
    static bool fromFileLine(const std::string& line, IndiceEntry& out) {
        size_t p = line.find('|');
        if (p == std::string::npos) return false;
        out.clave = line.substr(0, p);
        try { out.referencia = std::stoi(line.substr(p + 1)); }
        catch (...) { return false; }
        return true;
    }
};

class IndiceAVL {
private:
    ArbolAVL<IndiceEntry> arbol;
    Lista<IndiceEntry> registros; // auxiliar para recuperar referencia y persistir
public:
    IndiceAVL() {}
    ~IndiceAVL() { limpiar(); }

    bool insertar(const std::string& clave, int referencia) {
        IndiceEntry e(clave, referencia);
        if (registros.existe(e)) {
            // actualizar referencia en la lista (opcional)
            // buscar y actualizar
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

    bool buscar(const std::string& clave, int& referenciaOut) const {
        IndiceEntry key(clave, 0);
        if (!arbol.buscar(key)) return false;
        // Como ArbolAVL no expone el dato, buscamos en la lista auxiliar
        // búsqueda lineal; si quieres rendimiento aquí, usa un mapa adicional
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

    bool eliminar(const std::string& clave) {
        IndiceEntry key(clave, 0);
        if (!arbol.eliminar(key)) return false;
        // eliminar de registros
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

    bool guardarEnArchivo(const std::string& ruta) {
        int tam = registros.obtenerTamano();
        if (tam == 0) {
            return GestorArchivos::escribirArchivoCompleto(ruta, std::string(""));
        }
        std::string out[4096];
        int k = 0;
        IndiceEntry tmp;
        for (int i = 0; i < tam; ++i) {
            registros.obtenerElemento(i, tmp);
            out[k++] = tmp.toFileLine();
        }
        return GestorArchivos::escribirLineas(ruta, out, k);
    }

    bool cargarDesdeArchivo(const std::string& ruta) {
        registros.limpiar();
        arbol.limpiar();
        const int CAP = 8192;
        std::string lines[CAP];
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
