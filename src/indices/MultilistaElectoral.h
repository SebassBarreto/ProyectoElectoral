#ifndef MULTILISTAELECTORAL_H
#define MULTILISTAELECTORAL_H

#include <iostream>
#include "../../include/listas/Multilista.h"
#include "../../include/listas/Lista.h"
#include "../gestores/GestorArchivos.h"
#include "../modelos/Ciudad.h"
#include <string>
using namespace std;

class MultilistaElectoral {
private:
    Multilista<int,int,int> m; 

public:
    MultilistaElectoral() {}
    ~MultilistaElectoral() { m.limpiar(); }

    void insertarRegion(int idRegion) {
        m.insertarNivel1(idRegion);
    }

    bool existeRegion(int idRegion) const {
        return m.existeNivel1(idRegion);
    }

    bool insertarCiudadEnRegion(int idRegion, int idCiudad) {
        return m.insertarNivel2(idRegion, idCiudad);
    }

    bool insertarCandidatoEnCiudadDeRegion(int idRegion, int idCandidato) {
        return m.insertarNivel3(idRegion, idCandidato);
    }

    Lista<int>* obtenerCiudadesDeRegion(int idRegion) {
        return m.obtenerListaNivel2(idRegion);
    }

    Lista<int>* obtenerCandidatosDeRegion(int idRegion) {
        return m.obtenerListaNivel3(idRegion);
    }

    int contarCiudades(int idRegion) const {
        return m.contarNivel2(idRegion);
    }

    int contarCandidatos(int idRegion) const {
        return m.contarNivel3(idRegion);
    }

    void limpiar() {
        m.limpiar();
    }

    // persistencia
    bool guardarEnArchivo(const string& ruta) {
        if (m.estaVacia()) return GestorArchivos::escribirArchivoCompleto(ruta, string(""));
        return false;
    }

    bool cargarDesdeArchivo(const string& ruta) {
        return false;
    }
};

#endif // MULTILISTAELECTORAL_H


