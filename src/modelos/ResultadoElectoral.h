#ifndef RESULTADOELECTORAL_H
#define RESULTADOELECTORAL_H

#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>

class ResultadoElectoral {
private:
    std::map<std::string, int> votosPorCandidato; // candidato -> votos
    int votosEnBlanco;
    int votosNulos;
    int abstencion;
    int censoElectoral;
    std::string ganador;
    bool requiereSegundaVuelta;

    // Validar que no haya sobrepaso del censo
    bool validarVoto() const {
        return getTotalVotosValidos() + votosNulos + votosEnBlanco + abstencion <= censoElectoral;
    }

public:
    // Constructor
    ResultadoElectoral(int censo)
        : votosEnBlanco(0), votosNulos(0), abstencion(0),
          censoElectoral(censo), ganador(""), requiereSegundaVuelta(false) {
        if (censo <= 0) {
            censoElectoral = 0;
        }
    }

    // Setters
    bool agregarVoto(const std::string& candidato) {
        if (!validarVoto()) return false;
        votosPorCandidato[candidato]++;
        return true;
    }

    bool agregarVotoEnBlanco() {
        if (!validarVoto()) return false;
        votosEnBlanco++;
        return true;
    }

    bool agregarVotoNulo() {
        if (!validarVoto()) return false;
        votosNulos++;
        return true;
    }

    bool agregarAbstencion() {
        if (abstencion < censoElectoral) {
            abstencion++;
            return true;
        }
        return false;
    }

    void calcularResultados() {
        if (votosPorCandidato.empty()) {
            ganador = "Sin candidatos";
            requiereSegundaVuelta = false;
            return;
        }



        ganador = maxCandidato->first;
        int votosGanador = maxCandidato->second;
        int totalValidos = getTotalVotosValidos();

        // Calcular si requiere segunda vuelta
        if (totalValidos > 0) {
            double porcentajeGanador = (static_cast<double>(votosGanador) / totalValidos) * 100.0;
            requiereSegundaVuelta = (porcentajeGanador < 50.0);
        } else {
            requiereSegundaVuelta = false;
        }
    }

    void setGanador(const std::string& g) {
        ganador = g;
    }

    void setRequiereSegundaVuelta(bool requiere) {
        requiereSegundaVuelta = requiere;
    }

    // Getters
    int getVotos(const std::string& candidato) const {
        auto it = votosPorCandidato.find(candidato);
        if (it != votosPorCandidato.end()) {
            return it->second;
        }
        return 0;
    }

    int getVotosEnBlanco() const { return votosEnBlanco; }
    int getVotosNulos() const { return votosNulos; }
    int getAbstencion() const { return abstencion; }
    std::string getGanador() const { return ganador; }
    bool getRequiereSegundaVuelta() const { return requiereSegundaVuelta; }
    int getCensoElectoral() const { return censoElectoral; }

    // Obtener copia del mapa
    const std::map<std::string, int>& getVotosPorCandidato() const {
        return votosPorCandidato;
    }

    // Cálculos CORREGIDOS
    int getTotalVotosValidos() const {
        int total = votosEnBlanco; // Votos en blanco son válidos
        for (const auto& par : votosPorCandidato) {
            total += par.second;
        }
        return total;
    }

    int getTotalVotosEmitidos() const {
        return getTotalVotosValidos() + votosNulos;
    }

    int getParticipacion() const {
        return getTotalVotosEmitidos() + abstencion;
    }

    // Porcentajes sobre censo electoral
    float getPorcentajeSobreCenso(int votos) const {
        if (censoElectoral == 0) return 0.0f;
        return (static_cast<float>(votos) / censoElectoral) * 100.0f;
    }

    // Porcentajes sobre votos válidos
    float getPorcentajeSobreValidos(int votos) const {
        int totalValidos = getTotalVotosValidos();
        if (totalValidos == 0) return 0.0f;
        return (static_cast<float>(votos) / totalValidos) * 100.0f;
    }

    // toString mejorado
    std::string toString() const {
        std::stringstream ss;
        ss << "RESULTADOS ELECTORALES"<<endl;

        ss << "Censo electoral: " << censoElectoral <<endl;
        ss << "Votos emitidos: " << getTotalVotosEmitidos()
           << " (" << std::fixed << std::setprecision(2)
           << getPorcentajeSobreCenso(getTotalVotosEmitidos()) << "%)" << endl;
        ss << "Abstención: " << abstencion
           << " (" << getPorcentajeSobreCenso(abstencion) << "%)" << endl;

        ss << "VOTOS VÁLIDOS: " << endl;
        for (const auto& par : votosPorCandidato) {
            ss << "  " << std::left << std::setw(20) << par.first
               << ": " << std::right << std::setw(6) << par.second << " votos"
               << " (" << getPorcentajeSobreValidos(par.second) << "% válidos)"
               << " (" << getPorcentajeSobreCenso(par.second) << "% censo)" << endl;
        }

        ss << "Votos en blanco: " << votosEnBlanco
           << " (" << getPorcentajeSobreValidos(votosEnBlanco) << "% válidos)" << endl;
        ss << "Votos nulos: " << votosNulos << endl;
        ss << "Total validos: " << getTotalVotosValidos() << endl;

        ss << "GANADOR: " << ganador << endl;
        if (requiereSegundaVuelta) {
            ss << "SE REQUIERE SEGUNDA VUELTA" << endl;
        }
        return ss.str();
    }
};

#endif // RESULTADOELECTORAL_H
