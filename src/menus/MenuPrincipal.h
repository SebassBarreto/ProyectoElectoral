#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <iostream>
#include <string>
#include "../sistema/SistemaElectoral.h"
#include "../sistema/Tarjeton.h"
#include "../sistema/Consultas.h"
#include "../sistema/Simulador.h"
#include "../sistema/Escrutinio.h"
#include "../sistema/Estadisticas.h"

using namespace std;

class MenuPrincipal {
private:
    SistemaElectoral& sys;

    void pausar() {
        cout << "Presione ENTER para continuar...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    MenuPrincipal(SistemaElectoral& s) : sys(s) {}

    void mostrar() {
        bool salir = false;
        while (!salir) {
            cout << "\n=== SISTEMA ELECTORAL ===\n";
            cout << "1. Consultas\n";
            cout << "2. Tarjetones\n";
            cout << "3. Simulacion\n";
            cout << "4. Escrutinio (demo)\n";
            cout << "5. Estadisticas (demo)\n";
            cout << "6. Salir\n";
            cout << "Opcion: ";
            int op;
            if (!(cin >> op)) { cin.clear(); cin.ignore(10000, '\n'); continue; }
            cin.ignore(10000, '\n');

            if (op == 1) consultas();
            else if (op == 2) tarjetones();
            else if (op == 3) simulacion();
            else if (op == 4) escrutinioDemo();
            else if (op == 5) estadisticasDemo();
            else if (op == 6) salir = true;
            else cout << "Opcion invalida\n";
        }
    }

    void consultas() {
        cout << "\n-- Consultas --\n";
        Lista<string> out;
        Consultas::listarPresidencia(sys, out);
        for (int i = 0; i < out.obtenerTamano(); ++i) {
            string s; out.obtenerElemento(i, s);
            cout << s << "\n";
        }
        pausar();
    }

    void tarjetones() {
        cout << "\n-- Tarjetones --\n";
        int idBogota = -1;
        if (sys.obtenerIdCiudadPorNombre("Bogota", idBogota)) {
            Lista<string> out;
            Tarjeton::generarTarjetonAlcaldia(sys, idBogota, out);
            cout << "Tarjeton alcaldia (Bogota):\n";
            for (int i = 0; i < out.obtenerTamano(); ++i) { string s; out.obtenerElemento(i, s); cout << s << "\n"; }
        }
        Lista<string> out2;
        Tarjeton::generarTarjetonPresidencia(sys, out2);
        cout << "Tarjeton presidencia:\n";
        for (int i = 0; i < out2.obtenerTamano(); ++i) { string s; out2.obtenerElemento(i, s); cout << s << "\n"; }
        pausar();
    }

    void simulacion() {
        cout << "\n-- Simulacion --\n";
        sys.comenzarSimulacion();
        Simulador::seed(12345);

        int idBogota = -1;
        if (sys.obtenerIdCiudadPorNombre("Bogota", idBogota)) {
            ResultadoElectoral resBog;
            if (Simulador::simularAlcaldiaCiudad(sys, idBogota, resBog)) {
                Escrutinio::escribirResultadosAlcaldiaPorCiudad("data/resultados/resultados_ciudad_alcaldia.txt", "Bogota", resBog);
                cout << resBog.toString() << "\n";
            }
        }

        ResultadoElectoral resPais(0);
        if (Simulador::simularPresidenciaPais(sys, resPais)) {
            Escrutinio::escribirResultadosPresidenciaPais("data/resultados/resultados_pais_presidencia.txt", resPais);
            cout << resPais.toString() << "\n";
        }
        sys.finalizarSimulacion();
        pausar();
    }

    void escrutinioDemo() {
        cout << "Ver archivos en data/resultados/ para los escrutinios generados.\n";
        pausar();
    }

    void estadisticasDemo() {
        Estadisticas::estadisticaCensoPorRegion(sys, "data/resultados/estadisticas_presidencia_por_region.txt");
        cout << "Estadistica censo por region generada en data/resultados/estadisticas_presidencia_por_region.txt\n";
        pausar();
    }
};

#endif // MENUPRINCIPAL_H