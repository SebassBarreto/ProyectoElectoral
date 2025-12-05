#ifndef SISTEMA_ELECTORAL_H
#define SISTEMA_ELECTORAL_H

#include <iostream>
#include <string>

// modelos
#include "../modelos/Region.h"
#include "../modelos/Ciudad.h"
#include "../modelos/Partido.h"
#include "../modelos/Candidato.h"
#include "../modelos/Voto.h"
#include "../modelos/ResultadoElectoral.h"

// gestores
#include "../gestores/GestorArchivos.h"
#include "../gestores/GestorRegiones.h"
#include "../gestores/GestorCiudades.h"
#include "../gestores/GestorPartidos.h"
#include "../gestores/GestorCandidatos.h"

// indices
#include "../indices/IndiceAVL.h"
#include "../indices/MultilistaElectoral.h"

// listas genericas
#include "../../include/listas/Lista.h"

using namespace std;

class SistemaElectoral {
private:
    // datos cargados
    Lista<Region> regiones;
    Lista<Ciudad> ciudades;
    Lista<Partido> partidos;
    Lista<Candidato> candidatosAlcaldia;
    Lista<Candidato> candidatosPresidencia;

    // indices
    IndiceAVL idxCiudadPorNombre;       // "Ciudad:<nombre>" -> idCiudad
    IndiceAVL idxPartidoPorNombre;      // "Partido:<nombre>" -> idPartido
    IndiceAVL idxCandidatoPorIdent;     // "Cand:<ident>" -> posicion (alcaldia 0..n-1, presidencia offset 100000+j)
    IndiceAVL idxPresidentePorPartido;  // "Presidente:<idPartido>" -> id candidato presidencial (int)

    // multilistas
    MultilistaElectoral mElectoral;

    // control
    bool simulando;

    // helpers de clave
    static string kCiudadNombre(const string& nombre) { return string("Ciudad:") + nombre; }
    static string kPartidoNombre(const string& nombre) { return string("Partido:") + nombre; }
    static string kCandId(const string& id) { return string("Cand:") + id; }
    static string kPresPorPartido(int idPartido) { return string("Presidente:") + to_string(idPartido); }

public:
    SistemaElectoral() : simulando(false) {}

    bool inicializar(const string& rutaRegiones,
                     const string& rutaCiudades,
                     const string& rutaPartidos,
                     const string& rutaCandidatosAlcaldia,
                     const string& rutaCandidatosPresidencia) {
        if (!GestorRegiones::cargar(rutaRegiones, regiones)) return false;
        if (!GestorCiudades::cargar(rutaCiudades, ciudades)) return false;
        if (!GestorPartidos::cargar(rutaPartidos, partidos)) return false;
        if (!GestorCandidatos::cargarAlcaldia(rutaCandidatosAlcaldia, candidatosAlcaldia)) return false;
        if (!GestorCandidatos::cargarPresidencia(rutaCandidatosPresidencia, candidatosPresidencia)) return false;

        construirIndicesBasicos();
        mElectoral.construirRegionesCiudades(ciudades);
        poblarCiudadPartidoCandidatoAlcaldia();
        return true;
    }

    bool guardar(const string& rutaRegiones,
                 const string& rutaCiudades,
                 const string& rutaPartidos,
                 const string& rutaCandidatosAlcaldia,
                 const string& rutaCandidatosPresidencia,
                 const string& rutaRegionesCiudades,
                 const string& rutaCiudadPartidos,
                 const string& rutaCiudadPartidoCandidato) {

        bool ok = true;
        ok = ok && GestorRegiones::guardar(rutaRegiones, regiones);
        ok = ok && GestorCiudades::guardar(rutaCiudades, ciudades);
        ok = ok && GestorPartidos::guardar(rutaPartidos, partidos);
        ok = ok && GestorCandidatos::guardar(rutaCandidatosAlcaldia, candidatosAlcaldia);
        ok = ok && GestorCandidatos::guardar(rutaCandidatosPresidencia, candidatosPresidencia);
        ok = ok && mElectoral.guardarEnArchivos(rutaRegionesCiudades, rutaCiudadPartidos, rutaCiudadPartidoCandidato);
        return ok;
    }

    // control simulacion
    bool estaSimulando() const { return simulando; }
    void comenzarSimulacion() { simulando = true; }
    void finalizarSimulacion() { simulando = false; }

    // getters datos
    const Lista<Region>& getRegiones() const { return regiones; }
    const Lista<Ciudad>& getCiudades() const { return ciudades; }
    const Lista<Partido>& getPartidos() const { return partidos; }
    const Lista<Candidato>& getCandidatosAlcaldia() const { return candidatosAlcaldia; }
    const Lista<Candidato>& getCandidatosPresidencia() const { return candidatosPresidencia; }

    // indices y multilistas
    MultilistaElectoral& getMultilistaElectoral() { return mElectoral; }
    const MultilistaElectoral& getMultilistaElectoral() const { return mElectoral; }

    bool obtenerIdCiudadPorNombre(const string& nombreCiudad, int& idOut) const {
        return idxCiudadPorNombre.buscar(kCiudadNombre(nombreCiudad), idOut);
    }
    bool obtenerIdPartidoPorNombre(const string& nombrePartido, int& idOut) const {
        return idxPartidoPorNombre.buscar(kPartidoNombre(nombrePartido), idOut);
    }
    bool obtenerPosCandidatoPorIdentificacion(const string& ident, int& posOut) const {
        return idxCandidatoPorIdent.buscar(kCandId(ident), posOut);
    }
    bool obtenerPresidentePorPartido(int idPartido, int& idCandidatoOut) const {
        return idxPresidentePorPartido.buscar(kPresPorPartido(idPartido), idCandidatoOut);
    }

    void reconstruirIndices() {
        idxCiudadPorNombre.limpiar();
        idxPartidoPorNombre.limpiar();
        idxCandidatoPorIdent.limpiar();
        idxPresidentePorPartido.limpiar();
        construirIndicesBasicos();
    }

    void limpiar() {
        regiones.limpiar();
        ciudades.limpiar();
        partidos.limpiar();
        candidatosAlcaldia.limpiar();
        candidatosPresidencia.limpiar();
        idxCiudadPorNombre.limpiar();
        idxPartidoPorNombre.limpiar();
        idxCandidatoPorIdent.limpiar();
        idxPresidentePorPartido.limpiar();
        mElectoral.limpiar();
        simulando = false;
    }

private:
    void construirIndicesBasicos() {
        // ciudades por nombre
        for (int i = 0; i < ciudades.obtenerTamano(); ++i) {
            Ciudad c;
            if (ciudades.obtenerElemento(i, c)) {
                idxCiudadPorNombre.insertar(kCiudadNombre(c.getNombre()), c.getId());
            }
        }
        // partidos por nombre
        for (int i = 0; i < partidos.obtenerTamano(); ++i) {
            Partido p;
            if (partidos.obtenerElemento(i, p)) {
                idxPartidoPorNombre.insertar(kPartidoNombre(p.getNombre()), p.getId());
            }
        }
        // candidatos por identificacion
        for (int i = 0; i < candidatosAlcaldia.obtenerTamano(); ++i) {
            Candidato c;
            if (candidatosAlcaldia.obtenerElemento(i, c)) {
                idxCandidatoPorIdent.insertar(kCandId(c.getIdentificacion()), i);
            }
        }
        for (int j = 0; j < candidatosPresidencia.obtenerTamano(); ++j) {
            Candidato c;
            if (candidatosPresidencia.obtenerElemento(j, c)) {
                idxCandidatoPorIdent.insertar(kCandId(c.getIdentificacion()), 100000 + j);
            }
        }
        // presidente por partido
        for (int i = 0; i < candidatosPresidencia.obtenerTamano(); ++i) {
            Candidato c;
            if (!candidatosPresidencia.obtenerElemento(i, c)) continue;
            int idPartido = -1;
            if (!idxPartidoPorNombre.buscar(kPartidoNombre(c.getPartido()), idPartido)) continue;
            int idCandidatoNum = 0;
            try { idCandidatoNum = stoi(c.getIdentificacion()); } catch (...) { continue; }
            idxPresidentePorPartido.insertar(kPresPorPartido(idPartido), idCandidatoNum);
        }
    }

    void poblarCiudadPartidoCandidatoAlcaldia() {
        for (int i = 0; i < candidatosAlcaldia.obtenerTamano(); ++i) {
            Candidato c;
            if (!candidatosAlcaldia.obtenerElemento(i, c)) continue;

            int idCiudad = -1;
            if (!idxCiudadPorNombre.buscar(kCiudadNombre(c.getCiudadResidencia()), idCiudad)) {
                if (!idxCiudadPorNombre.buscar(kCiudadNombre(c.getCiudadNacimiento()), idCiudad)) {
                    continue;
                }
            }
            int idPartido = -1;
            if (!idxPartidoPorNombre.buscar(kPartidoNombre(c.getPartido()), idPartido)) continue;

            int idCandidatoNum = 0;
            try { idCandidatoNum = stoi(c.getIdentificacion()); } catch (...) { continue; }

            mElectoral.insertarPartidoEnCiudad(idCiudad, idPartido);
            mElectoral.registrarCandidatoAlcaldia(idCiudad, idPartido, idCandidatoNum);
        }
    }
};

#endif // SISTEMA_ELECTORAL_H