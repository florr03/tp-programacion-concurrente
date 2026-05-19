# tp-programacion-concurrente

### Persona 1 → Producción + sincronización inicial

Hace:

* Clase `Job`
* Generación de jobs
* Threads productores
* Inserción en cola
* Retardo 100 ms
* Estados:

  * CREADO
  * EN_COLA
* Parte del informe:

  * Gestión de carga inmediata
  * Por qué usar concurrencia desde producción

Carga: **media-alta**

---

### Persona 2 → Cola + prioridades + anti-starvation

Hace:

* Message Queue
* Prioridad Premium/Free
* Scheduler
* Anti-starvation (5000 ms)
* Condition variables
* Espera pasiva (sin busy waiting)
* Parte informe:

  * Livelock
  * Starvation

Carga: **alta**

---

### Persona 3 → Pool VRAM + consumidores 

Hace:

* Worker threads
* Pool VRAM
* Máx 5 slots
* Exclusión mutua
* Retardos:

450 ms asignación
250 ms liberación
600 ms procesamiento

* Parte informe:
  * Deadlock
  * Exclusión mutua

Carga: **alta**

---

### Persona 4 → Logs + contador + pruebas + integración

Hace:

* Logger sincronizado
* `sistema.log`
* Contador global
* Race conditions
* Escenarios:

1500 jobs
0 jobs
8 premium
Anti-starvation

Configuraciones:
1P-2C
3P-1C
3P-3C

* Video
* Github
* Parte informe:

  * Selección de primitivas

Carga: **alta**

---



## Reparto final equilibrado (mi propuesta)

| Persona | Código              | Testing            | Informe              | Integración  |
| ------- | ------------------- | ------------------ | -------------------- | ------------ |
| 1       | Productores         | pruebas generación | concurrencia inicial | ayuda        |
| 2       | Queue + prioridades | starvation         | scheduler            | ayuda        |
| 3       | VRAM + workers      | deadlocks          | exclusión mutua      | ayuda        |
| 4       | logs + contador     | stress tests       | primitivas           | Github/video |

