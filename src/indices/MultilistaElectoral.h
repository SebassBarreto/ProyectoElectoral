#ifndef MULTILISTAELECTORAL_H
#define MULTILISTAELECTORAL_H

#include "../../include/listas/Multilista.h"
#include "../../include/listas/Lista.h"
#include "../gestores/GestorArchivos.h"
#include "../modelos/Ciudad.h"
#include <string>

/*
  Diseño sugerido de multilista electoral:
  - Nivel1: regionId (int)      -> T = int
  - Nivel2: ciudadId (int)      -> U = int
  - Nivel3: candidatoId (int)   -> V = int
  Con esto puedes hacer: region -> ciudades -> candidatos
*/

class MultilistaElectoral {
private:
    Multilista<int,int,int> m; // regionId -> ciudadId -> candidatoId

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

    // persistencia simple: guardar por linea region|ciudad1,ciudad2|candidato1,candidato2
    bool guardarEnArchivo(const std::string& ruta) {
        if (m.estaVacia()) return GestorArchivos::escribirArchivoCompleto(ruta, std::string(""));
        // implementación concreta depende de poder iterar la multilista
        // aquí puedes recorrer m.imprimir() o agregar una función para iterar
        // por simplicidad se deja como punto de extensión
        return false;
    }

    bool cargarDesdeArchivo(const std::string& ruta) {
        // parsear lineas y poblar multilista
        return false;
    }
};

#endif // MULTILISTAELECTORAL_H
