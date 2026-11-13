\# TF01 · Control de calificaciones



\*\*Universidad:\*\* Universidad Autónoma de Santo Domingo (UASD)

\*\*Asignatura:\*\* INF-5110 · Laboratorio de Introducción a la Programación

\*\*Autor:\*\* Braunier Isaias Vilorio Mariano · Matrícula 100816767



\## Descripción

Aplicación de consola en C++ para llevar el control de calificaciones de estudiantes. Permite registrar estudiantes y sus notas por asignatura, calcular promedios, buscar por matrícula, clasificar aprobados y reprobados y mostrar el mayor y el menor promedio. Los datos se guardan automáticamente en un archivo CSV y se cargan al iniciar el programa.



\## Funcionalidades

1\. Registrar estudiante (matrícula de 9 dígitos y nombre).

2\. Registrar calificación (asignatura y nota de 0 a 100).

3\. Calcular el promedio de un estudiante.

4\. Buscar estudiante por matrícula.

5\. Listar aprobados y reprobados (aprueba con promedio mayor o igual a 70).

6\. Mostrar el mayor y el menor promedio.

7\. Listar todos los estudiantes.

0\. Salir (guarda los datos).



\## Compilación y ejecución

Requiere un compilador C++11 o superior (g++).



&#x20;   g++ -std=c++11 -Wall -Wextra main.cpp -o control

&#x20;   .\\control.exe



El archivo estudiantes.csv se crea o se lee en la carpeta desde donde se ejecuta el programa.



\## Estructura de los datos

&#x20;   struct Calificacion { string asignatura; double nota; };

&#x20;   struct Estudiante   { string matricula; string nombre; vector<Calificacion> calificaciones; };

&#x20;   vector<Estudiante> estudiantes;



Formato del CSV (una fila por calificación; un estudiante sin notas se guarda con asignatura y nota vacías):



&#x20;   matricula,nombre,asignatura,nota

&#x20;   123456789,juan santana perez,programacion,95



\## Validaciones

\- Matrícula de exactamente 9 dígitos numéricos y no repetida.

\- Nombre y asignatura obligatorios y sin comas.

\- Nota numérica entre 0 y 100.

\- No repetir la misma asignatura para un estudiante.

\- Opción de menú válida y estudiante existente al registrar notas.



\## Resumen de pruebas

El detalle está en PRUEBAS.md. Se probaron casos válidos (registro, notas, búsqueda, promedio, aprobados y reprobados, mayor y menor) e inválidos (nota fuera de rango, texto en lugar de número, matrícula inexistente), además de la persistencia en el archivo CSV.

