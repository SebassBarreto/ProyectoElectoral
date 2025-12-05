#ifndef MENUESTADISTICAS_H
#define MENUESTADISTICAS_H

#include <iostream>
#include <string>
#include "../sistema/SistemaElectoral.h"
#include "../sistema/Estadisticas.h"

using namespace std;

class MenuEstadisticas {
private:
    SistemaElectoral& sys;
public:
    MenuEstadisticas(SistemaElectoral& s) : sys(s) {}

    void mostrar() {
        cout << "\n-- Menu Estadisticas --\n";
        cout << "1. Censo por region\n";
        cout << "Opcion: ";
        int op; if (!(cin >> op)) { cin.clear(); cin.ignore(10000, '\n'); return; }
        cin.ignore(10000, '\n');
        if (op == 1) {
            Estadisticas::estadisticaCensoPorRegion(sys, "data/resultados/estadisticas_presidencia_por_region.txt");
            cout << "Generado en data/resultados/estadisticas_presidencia_por_region.txt\n";
        }
    }
};

#endif // MENUESTADISTICAS_H