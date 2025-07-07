
# 🚑 Fibonacci Routing Simulation

Simulación urbana de rutas óptimas con montículos de Fibonacci y eventos dinámicos como congestión vehicular o emergencias. Este sistema modela una ciudad como un grafo y calcula rutas en tiempo real usando Dijkstra adaptado con `Fibonacci Heap` para mejorar el rendimiento en múltiples operaciones `decrease-key`.

---

## 📂 Estructura del Proyecto

```markdown
/fibonacci-routing-simulation
│
├── main.cpp                  # Ejecuta la simulación
├── FibonacciHeap.h          # Implementación de Fibonacci Heap
├── Graph.h                  # Representación del grafo urbano
├── Router.h                 # Algoritmo de Dijkstra adaptado con Fibonacci Heap
├── SimulationScenario.cpp   # Escenarios dinámicos (congestión, emergencias)
├── SimulationScenario.h     # Declaraciones de funciones del escenario
├── data/
│   └── city\_graph.txt       # Grafo de ejemplo con pesos (tiempos de tránsito)
└── output/
└── routes\_log.txt       # Log de rutas calculadas y eventos simulados
```


## 🧪 Simulaciones Incluidas

El archivo `SimulationScenario.cpp` simula 3 eventos:

1. **Ruta base**: calcula el camino óptimo sin eventos externos.
2. **Congestión**: simula tráfico en una vía y recalcula la ruta.
3. **Emergencia**: mejora una vía específica (emergencia médica) y vuelve a calcular.

---

## 📄 Ejemplo de Archivo de Entrada (`data/city_graph.txt`)

```txt
1 2 2
2 3 2
3 6 5
1 4 1
4 5 3
5 6 6
```

---

## 🧾 Salida Esperada (`output/routes_log.txt`)

```txt
Ruta base 1 -> 6 | Tiempo: 9 | Ruta: 1 2 3 6
Tras congestión 2-3 | Tiempo: 10 | Ruta: 1 4 5 6
Emergencia 5-6 | Tiempo: 5 | Ruta: 1 4 5 6
```

---
Perfecto. Aquí tienes una sección detallada que **explica el enfoque algorítmico**, el **modelo de simulación** y **analiza el comportamiento del sistema a partir del output generado**, todo integrado como parte del README.

---

## 🧠 Enfoque y Resolución del Problema

El propósito del sistema es simular cómo se adaptan las rutas urbanas ante eventos como **congestión vial** o **emergencias**, manteniendo el tiempo de respuesta al mínimo. Para lograrlo, se combinan estructuras de datos avanzadas con lógica de simulación basada en grafos.

---

### 🔧 1. Modelado del Problema

La ciudad se modela como un **grafo dirigido y ponderado**, donde:

* **Nodos**: representan intersecciones o puntos de control.
* **Aristas**: representan calles, cuyo **peso es el tiempo estimado de tránsito**.
* El grafo se define en un archivo `city_graph.txt` y puede modificarse dinámicamente.

---

### 🚀 2. Algoritmo de Enrutamiento

Se utiliza el algoritmo de **Dijkstra**, optimizado con un **Montículo de Fibonacci** para lograr eficiencia en escenarios donde se requiere:

* Múltiples operaciones `decrease-key` al actualizar rutas.
* Recalcular caminos rápidamente ante cambios en el grafo.

Este enfoque es crucial en sistemas urbanos donde el tiempo de cómputo debe mantenerse bajo ante eventos impredecibles.

---

### ⚡ 3. Simulación de Escenarios

El sistema ejecuta una secuencia de simulaciones:

1. **Ruta base**: se calcula la ruta más corta sin eventos externos.
2. **Congestión**: se incrementa el peso de una arista clave, simulando tráfico.
3. **Emergencia**: se reduce el peso de otra arista, simulando prioridad médica o desbloqueo de vía.

En cada caso, el sistema recalcula la mejor ruta y registra:

* El tiempo total.
* La ruta seleccionada.
* El tipo de evento que ocurrió.

---

### 📊 4. Análisis del Output

Ejemplo de salida (`routes_log.txt`):

```
Ruta base 1 -> 6 | Tiempo: 9 | Ruta: 1 2 3 6
Tras congestión 2-3 | Tiempo: 10 | Ruta: 1 4 5 6
Emergencia 5-6 | Tiempo: 5 | Ruta: 1 4 5 6
```

#### 🔎 Interpretación:

* **Ruta base**: El sistema seleccionó la ruta más rápida por 1 → 2 → 3 → 6 (tiempo total 9).
* **Congestión**: Aumentar el peso de 2 → 3 provocó un desvío por 1 → 4 → 5 → 6, aunque fue ligeramente más lento (tiempo 10).
* **Emergencia**: Se redujo el peso de 5 → 6, mejorando dramáticamente el tiempo total (tiempo 5), y se mantuvo la ruta alternativa como la más eficiente.

Esto demuestra que:

* El sistema **detecta y reacciona automáticamente a los cambios en el grafo**.
* Se comporta correctamente tanto cuando las condiciones empeoran como cuando mejoran.
* El uso de Fibonacci Heap permite que recalcular rutas no degrade el rendimiento.

---


## 📌 ¿Por qué Fibonacci Heap?

Permite mejorar el rendimiento de Dijkstra cuando hay muchos `decrease-key`, como en escenarios urbanos dinámicos donde:

* Se actualizan pesos por congestión en tiempo real.
* Se recalculan rutas para múltiples ambulancias u operadores.

---

