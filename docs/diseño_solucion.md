# Diseño de la Solución — Proyecto Electoral

## 1. Introducción

El Proyecto Electoral es un sistema modular desarrollado en C++ que permite administrar un proceso electoral completo: registro de regiones, ciudades, partidos y candidatos; gestión y conteo de votos; consultas; simulación del proceso y generación de estadísticas.

Este documento describe el diseño interno de la solución, cubriendo la arquitectura general, capas del sistema, estructuras de datos utilizadas, dependencias entre módulos y decisiones técnicas.

---

## 2. Arquitectura General

El proyecto está organizado siguiendo una arquitectura por capas, separando responsabilidades para facilitar mantenibilidad y escalabilidad:

1. **Capa de Datos (data/)**  
   Archivos planos que contienen la información inicial del sistema.

2. **Capa de Modelos (src/modelos/)**  
   Clases que representan las entidades del dominio electoral.

3. **Capa de Estructuras Genéricas (include/)**  
   Implementa estructuras de datos reutilizables: listas, pilas, colas, árboles, multilistas y algoritmos auxiliares.

4. **Capa de Gestión (src/gestores/)**  
   Controla el acceso a archivos y las operaciones CRUD de las entidades del sistema.

5. **Capa de Índices (src/indices/)**  
   Estructuras diseñadas para acelerar búsquedas y relaciones entre entidades mediante AVL y multilistas.

6. **Capa del Sistema Electoral (src/sistema/)**  
   Contiene la lógica central: consultas, escrutinio, simulación, votación y estadísticas.

7. **Capa de Interfaz por Consola (src/menus/)**  
   Presenta menús y opciones de interacción al usuario.

---

## 3. Diseño por Módulos

### 3.1. include/ — Estructuras de Datos Generales

#### 3.1.1. Nodos
- `Nodo.h`: nodo simple para listas enlazadas.
- `NodoDoble.h`: nodo doble para listas dobles.
- `NodoArbol.h`: nodo para árboles binarios y AVL.

#### 3.1.2. Listas
- `Lista.h`: lista simple.
- `ListaDoble.h`: lista doble.
- `ListaCircular.h`: lista circular enlazada.
- `Multilista.h`: estructura de multilista con múltiples punteros lógicos.

#### 3.1.3. Pilas y Colas
- `Pila.h`: implementación LIFO.
- `Cola.h`: implementación FIFO.
- `ColaPrioridad.h`: cola con prioridades internas, útil para ordenamientos.

#### 3.1.4. Árboles
- `ArbolBinario.h`: árbol binario general.
- `ArbolAVL.h`: árbol AVL con rotaciones.

#### 3.1.5. Algoritmos
- `Ordenamiento.h`: algoritmos genéricos (quick sort, merge sort, etc.).
- `Busqueda.h`: búsqueda binaria, secuencial y variantes.

---

### 3.2. src/modelos/ — Modelos del Dominio

Representan los elementos del sistema electoral:

- `Fecha.h`
- `Region.h`
- `Ciudad.h`
- `Partido.h`
- `Candidato.h`
- `Voto.h`
- `ResultadoElectoral.h`

Cada modelo se centra en almacenar datos y proveer métodos simples de acceso (getters/setters).

---

### 3.3. src/gestores/ — Gestión y Control CRUD

Encapsulan operaciones sobre archivos y manejo de entidades:

- `GestorArchivos.h`: lectura/escritura de archivos.
- `GestorRegiones.h`
- `GestorCiudades.h`
- `GestorPartidos.h`
- `GestorCandidatos.h`

Cada gestor:
- carga datos desde data/
- valida entradas
- aplica operaciones CRUD
- actualiza índices cuando corresponde

---

### 3.4. src/indices/ — Índices de Alto Rendimiento

#### 3.4.1. Árbol AVL
- `IndiceAVL.h`

Utilizado para:
- búsqueda rápida por códigos
- inserciones ordenadas
- eliminar duplicidad de datos

#### 3.4.2. Multilista
- `MultilistaElectoral.h`

Permite representar relaciones complejas:
- regiones → ciudades  
- partidos → candidatos  
- candidatos → votos  

Se usa cuando una entidad pertenece a múltiples categorías simultáneamente.

---

### 3.5. src/sistema/ — Lógica Principal

- `SistemaElectoral.h`: fachada del sistema.
- `Consultas.h`: consultas por región, partido, ciudad o candidato.
- `Simulador.h`: simulación del proceso de votación.
- `Escrutinio.h`: conteo y consolidación de votos.
- `Tarjeton.h`: representación de los candidatos por región.
- `Estadisticas.h`: cálculos agregados y análisis.

Esta capa define las reglas, flujos y operaciones de alto nivel del proyecto.

---

### 3.6. src/menus/ — Interfaz por Consola

Implementa los menús que ve el usuario:

- `MenuPrincipal.h`
- `MenuConsultas.h`
- `MenuModificacion.h`
- `MenuSimulacion.h`
- `MenuEstadisticas.h`

Cada menú se comunica únicamente con la capa del sistema, no directamente con datos.

---

### 3.7. src/utilidades/ — Herramientas Auxiliares

- `Utilidades.h`: conversiones, manejo de cadenas, utilidades varias.
- `Validadores.h`: validación de entradas numéricas, texto, fechas, etc.

---

## 4. Flujo General del Sistema

1. Cargar archivos desde `data/`.
2. Inicializar modelos y estructuras.
3. Construir índices AVL y multilistas.
4. Mostrar menú principal.
5. Según la acción del usuario:
   - ejecutar consultas,
   - registrar o modificar entidades,
   - simular votaciones,
   - realizar escrutinio,
   - generar estadísticas.
6. Actualizar archivos y estructuras cuando corresponda.

---

## 5. Decisiones de Diseño

- Se eligen estructuras propias en lugar de STL para fines académicos y control total.
- Los gestores actúan como capa intermedia evitando acoplamiento directo entre UI y modelos.
- Los archivos de texto permiten compatibilidad y facilidad de lectura.
- El uso de AVL garantiza tiempos de búsqueda eficientes.
- La multilista permite representar relaciones múltiples sin duplicar información.
- El sistema está dividido en capas para evitar dependencias circulares.

---

## 6. Conclusión

La solución propuesta está diseñada para ser modular, escalable y clara. Permite gestionar eficazmente un sistema electoral realista, integrando estructuras de datos avanzadas con una organización por capas que facilita el mantenimiento y expansión futura del proyecto.
