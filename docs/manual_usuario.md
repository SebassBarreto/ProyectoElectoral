# Manual de Usuario  
## Sistema Electoral – Proyecto Final 2025-3  

---

## 1. Introducción  

El Sistema Electoral es una aplicación de consola diseñada para simular y gestionar el proceso electoral de las alcaldías de las capitales del país y las elecciones presidenciales. Permite realizar consultas, modificar datos, generar tarjetones, simular votaciones, obtener escrutinios y generar estadísticas nacionales y regionales.  

Este manual explica cómo usar el programa paso a paso.

---

## 2. Requerimientos  

- **Sistema operativo:** Windows, Linux o macOS.  
- **Compilador C++:** Compatible con C++17 (Dev-C++ o MinGW).  
- **Archivos de datos** dentro de la carpeta `data/`:
  - `regiones.txt`
  - `ciudades.txt`
  - `partidos.txt`
  - `candidatos.txt`
  - `resultados.txt`

**Importante:** No mover ni renombrar estos archivos.

---

## 3. Ejecución Inicial  

Para iniciar el sistema:  

1. Abra la carpeta del proyecto.  
2. Ejecute el archivo `ProyectoElectoral.exe` (si está compilado) o compile `main.cpp` en Dev-C++.  
3. Al iniciar, el sistema cargará automáticamente:
   - Ciudades
   - Regiones
   - Partidos
   - Candidatos
   - Censo electoral generado aleatoriamente
   - Datos previos de simulaciones anteriores

Una vez cargado, aparecerá el **Menú Principal**.

---

## 4. Menú Principal  
SISTEMA ELECTORAL
=================

Consultas

Modificación de datos

Simulación electoral

Escrutinio

Estadísticas

Salir

Seleccione una opción:

text

---

## 5. Consultas  

Este módulo permite consultar información sin modificar los datos.

**Opciones típicas:**  

1. Consultar regiones  
2. Consultar ciudades por región  
3. Consultar partidos  
4. Consultar candidatos por:
   - Ciudad
   - Región
   - Partido
5. Mostrar tarjetón de alcaldía por ciudad
6. Mostrar tarjetón presidencial
7. Consultar censo electoral
8. Volver

### Consultas solicitadas por el enunciado  

- Candidatos a alcaldías por partido y región.  
- Candidatos a alcaldías por partido en las capitales.  
- Candidatos a presidencia y vicepresidencia.  
- Candidato a alcaldía por ciudad y por partido.  
- Tarjetón de alcaldía (incluye voto en blanco).  
- Tarjetón presidencial (incluye voto en blanco).  
- Censo electoral total y por ciudad.

Los tarjetones incluyen voto en blanco.

---

## 6. Modificación de Datos  

Permite editar la información almacenada en memoria antes de simular.

**Se puede:**  

- Agregar candidato  
- Editar candidato  
- Eliminar candidato  
- Modificar ciudades o partidos  
- Actualizar regiones  
- Guardar cambios

**Nota importante:**  
**Una vez inicie la simulación de votaciones no podrá eliminar ni agregar candidatos hasta finalizar.**

---

## 7. Simulación Electoral  

La simulación genera votaciones aleatorias respetando el censo electoral.

**El sistema:**  

1. Genera para cada ciudad:
   - Votos por cada candidato de alcaldía
   - Votos en blanco
   - Votos nulos
   - Abstención

2. Genera para el país:
   - Votos por cada fórmula presidencial
   - Votos en blanco
   - Votos nulos
   - Abstención

**Reglas:**  

- El número total de votos no puede superar el censo electoral.  
- Los votos se distribuyen de forma aleatoria pero consistente.  
- Se genera un resultado por ciudad y para el país.

Al finalizar, los datos se envían al módulo de escrutinio.

---

## 8. Escrutinio  

Este módulo muestra los resultados electorales ciudad por ciudad y a nivel nacional.

**Para alcaldías por ciudad:**  

- Lista de candidatos  
- Votos obtenidos  
- Porcentajes  
- Votos en blanco  
- Votos nulos  
- Abstención  
- Ganador

**Para presidencia:**  

- Totales nacionales por candidato  
- Votos en blanco  
- Votos nulos  
- Abstención  
- Ganador  
- Verificación de segunda vuelta:
  - Si ningún candidato supera el 50%, se muestran los dos más votados

---

## 9. Estadísticas  

El sistema genera reportes avanzados solicitados en el documento oficial.

### Estadísticas para Alcaldías  

**Reporte general por región:**  
- Total votos  
- Votos en blanco  
- Votos nulos  
- Abstención  
- Porcentajes

**Reporte detallado por región:**  
- Alcaldes electos por partido  
- Totales por sexo (hombres/mujeres)

**Totales nacionales:**  
- Totales por partido  
- Totales por sexo

### Estadísticas para Presidente  

**Reporte general por región**  
**Reporte nacional consolidado**  
**Reporte detallado por departamento:**  
- Votos por partido  
- Votos por sexo  
- Porcentajes

**Reporte total nacional:**  
- Votos por partido  
- Votos por sexo

**Evaluación de segunda vuelta:**  
- Si aplica, muestra los dos candidatos con mayor votación

---

## 10. Archivos y Persistencia  

Al finalizar la simulación se actualizan los archivos en `data/`:  

- Nuevos candidatos (si fueron agregados antes de simular)  
- Censos actualizados  
- Datos de resultados recientes

Estos archivos permiten realizar múltiples simulaciones consecutivas sin perder información.

---

## 11. Mensajes Comunes  

- **"Dato inválido"**  
  La entrada no cumple el formato esperado.

- **"No existen registros para esta consulta"**  
  La ciudad, candidato o partido no tiene datos asociados.

- **"El archivo no pudo ser cargado"**  
  Verifique que la carpeta `data/` se encuentre junto al ejecutable.

- **"Acción no permitida durante la simulación"**  
  Intento de modificar candidatos después de iniciar la votación.

---

## 12. Finalizar el Programa  

En el menú principal elija:  
Salir

text

Se le consultará si desea guardar cambios antes de cerrar.

---

## 13. Soporte  

Revise la carpeta `docs/` para:  

- Diseño de la solución  
- Estructura de archivos  
- Diagramas  
- Manual del usuario  
- Documento del proyecto

Para soporte adicional, contacte al profesor o al equipo de desarrollo.

---

*Última actualización: Diciembre 2025*  
*Versión del sistema: 1.0*