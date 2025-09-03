# Sistema de Gestión de Reservas de Vuelos en C++

##  Descripción

Sistema desarrollado en **C++** que permite gestionar vuelos, pasajeros y reservas desde la consola con persistencia en archivos binarios. Está pensado como prototipo funcional para aerolíneas pequeñas o proyectos académicos robustos.

## ⭐ Características destacadas

- Registro de vuelos con datos esenciales: fecha, hora, destino, aerolínea y precio.
- Gestión de pasajeros con asignación automática de asientos.
- Reserva y cancelación de vuelos con actualización visual de disponibilidad.
- Manejo de datos mediante archivos binarios (`Info_vuelos.txt`, `Pasajeros.txt`).
- Interfaz intuitiva mediante menús en consola (con `system("cls")` y `system("pause")`).

##  Estructura del proyecto

| Componente            | Funcionalidad principal                                 |
|-----------------------|---------------------------------------------------------|
| `Informacion`         | Almacena datos del vuelo                                |
| `Aviones`             | Representa disponibilidad de asientos (`O` / `X`)       |
| `Pasajeros`           | Guarda datos personales y posición del asiento          |
| Menús principales     | Navegación: archivo, horarios, reservas y vuelos        |
| Operaciones clave     | Leer/grabar archivos, reservar, cancelar, mostrar datos |

##  Tecnologías utilizadas

- **Lenguaje:** C++ (estructurado y modular)  
- **Persistencia:** Archivos binarios  
- **Interfaz:** Consola (Windows)  
- **IDE sugerido:** Code::Blocks, Visual Studio Code o NetBeans

##  Posibles mejoras futuras

- Interfaz gráfica (con Qt, Java Swing, etc.)  
- Output en pantalla más amigable (colores, tablas visuales)  
- Uso de base de datos relacional (SQLite o MySQL)  
- Migración a aplicación web o API REST  
- Estadísticas de ocupación y ventas

##  Ejecución del proyecto

1. Clona el repositorio:
   ```bash
   git clone https://github.com/Paulinaczz/flightManagementSystem.git
