# Estructura del Proyecto Electoral

```text
ProyectoElectoral/
├── main.cpp
├── README.md
├── include/
│   ├── nodos/
│   │   ├── Nodo.h
│   │   ├── NodoDoble.h
│   │   └── NodoArbol.h
│   ├── listas/
│   │   ├── Lista.h
│   │   ├── ListaDoble.h
│   │   ├── ListaCircular.h
│   │   └── Multilista.h
│   ├── pilas_colas/
│   │   ├── Pila.h
│   │   ├── Cola.h
│   │   └── ColaPrioridad.h
│   ├── arboles/
│   │   ├── ArbolBinario.h
│   │   └── ArbolAVL.h
│   └── algoritmos/
│       ├── Ordenamiento.h
│       └── Busqueda.h
├── src/
│   ├── modelos/
│   │   ├── Fecha.h
│   │   ├── Region.h
│   │   ├── Ciudad.h
│   │   ├── Partido.h
│   │   ├── Candidato.h
│   │   ├── Voto.h
│   │   └── ResultadoElectoral.h
│   ├── gestores/
│   │   ├── GestorArchivos.h
│   │   ├── GestorRegiones.h
│   │   ├── GestorCiudades.h
│   │   ├── GestorPartidos.h
│   │   └── GestorCandidatos.h
│   ├── indices/
│   │   ├── IndiceAVL.h
│   │   └── MultilistaElectoral.h
│   ├── sistema/
│   │   ├── SistemaElectoral.h
│   │   ├── Consultas.h
│   │   ├── Simulador.h
│   │   ├── Escrutinio.h
│   │   ├── Tarjeton.h
│   │   └── Estadisticas.h
│   ├── menus/
│   │   ├── MenuPrincipal.h
│   │   ├── MenuConsultas.h
│   │   ├── MenuModificacion.h
│   │   ├── MenuSimulacion.h
│   │   └── MenuEstadisticas.h
│   └── utilidades/
│       ├── Utilidades.h
│       └── Validadores.h
├── data/
│   ├── regiones.txt
│   ├── ciudades.txt
│   ├── partidos.txt
│   ├── candidatos.txt
│   └── resultados.txt
└── docs/
    ├── proyecto_final_2025-3.pdf
    ├── diseño_solucion.md
    ├── estructura_archivos.md
    ├── manual_usuario.md
    └── diagramas/
        ├── diagrama_clases.png
        └── diagrama_estructuras.png
```


## Descripción de Carpetas

### include/
Librerías genéricas reutilizables

- **nodos/**: Estructuras básicas de nodos
- **listas/**: Implementaciones de listas enlazadas
- **pilas_colas/**: Estructuras LIFO y FIFO
- **arboles/**: Árboles binarios y AVL
- **algoritmos/**: Algoritmos de ordenamiento y búsqueda

### src/
Código específico del proyecto electoral

- **modelos/**: Clases de dominio del sistema
- **gestores/**: Manejo de archivos y operaciones CRUD
- **indices/**: Estructuras optimizadas para búsquedas
- **sistema/**: Lógica principal del sistema electoral
- **menus/**: Interfaces de consola
- **utilidades/**: Funciones auxiliares y validaciones

### data/
Archivos de texto plano con datos del sistema

### docs/
Documentación del proyecto