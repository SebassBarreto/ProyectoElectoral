
#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <string>
#include <ctime>
using namespace std;

class Candidato {
private:
    string nombre;
    string apellido;
    string identificacion;
    char sexo; // 'M' o 'F'
    string estadoCivil; // Casado, Soltero, Unión libre, Divorciado
    int diaNacimiento, mesDNacimiento, birthYear;
    string ciudadNacimiento;
    string ciudadResidencia;
    string partido;
    bool esPresidencial;
    string vicepresidente; // Solo si es presidencial
    int numeroTarjeton; // Para identificar en el tarjetón

public:
    // Constructor
    Candidato()
    : nombre(""), apellido(""), identificacion(""), sexo('M'),
      estadoCivil(""), diaNacimiento(0), mesDacimiento(0), anoNacimiento(0),
      ciudadNacimiento(""), ciudadResidencia(""), partido(""),
      esPresidencial(false), vicepresidente(""), numeroTarjeton(0) {}

    Candidato(string n, string a, string id, char s, string ec,
                     int d, int m, int y, string cn, string cr, string p, bool pres, string vp)
    : nombre(n), apellido(a), identificacion(id), sexo(s), estadoCivil(ec),
      diaNacimiento(d), mesDacimiento(m), anoNacimiento(y),
      ciudadNacimiento(cn), ciudadResidencia(cr), partido(p),
      esPresidencial(pres), vicepresidente(vp), numeroTarjeton(0) {}

    // Getters
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getIdentificacion() const { return identificacion; }
    char getSexo() const { return sexo; }
    string getEstadoCivil() const { return estadoCivil; }
    string getCiudadNacimiento() const { return ciudadNacimiento; }
    string getCiudadResidencia() const { return ciudadResidencia; }
    string getPartido() const { return partido; }
    bool getEsPresidencial() const { return esPresidencial; }
    string getVicepresidente() const { return vicepresidente; }
    int getNumeroTarjeton() const { return numeroTarjeton; }

    // Setters
    void setPartido(string p) { partido = p; }
    void setNumeroTarjeton(int num) { numeroTarjeton = num; }
    void setVicepresidente(string vp) { vicepresidente = vp; }

    //Calcular edad

    int calcularEdad() const {
        time_t now = time(0);
        tm* localtm = localtime(&now);
        int actualYear = 1900 + localtm->tm_year;
        int edad = actualYear - birthYear;

        // Ajustar si aún no ha cumplido años
        int mesActual = 1 + localtm->tm_mon;
        int diaActual = localtm->tm_mday;

        if (mesActual < mesDNacimiento || (mesActual == mesDNacimiento && diaActual < diaNacimiento)) {
            edad--;
        }
        return edad;
    }
};
#endif //CANDIDATO_H

    

#endif //CANDIDATO_H
