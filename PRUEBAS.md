# Casos de prueba manuales · TF01 Control de calificaciones

Autor: Braunier Isaias Vilorio Mariano · Matrícula 100816767

| # | Tipo | Pasos (entrada) | Resultado esperado | Resultado obtenido |
|---|------|-----------------|--------------------|--------------------|
| 1 | Válido | Opción 1: matrícula 123456789, nombre juan santana perez | Estudiante registrado y guardado | Registrado y guardado en estudiantes.csv |
| 2 | Límite | Opción 2 o 3 con el estudiante recién creado (sin notas) | Aviso de que no tiene calificaciones | El programa avisó que no tiene calificaciones |
| 3 | Válido | Opción 2: matrícula 123456789, asignatura programacion, nota 95 | Calificación registrada y guardada | Registrada; el CSV muestra la asignatura y la nota 95 |
| 4 | Válido | Registrar a 123456788 (jose perez rodriguez) con matematica y nota 60 | Estudiante y nota registrados | Registrados |
| 5 | Válido (búsqueda) | Opción 4: matrícula 123456788 | Datos, nota, promedio 60.00 y REPROBADO | Mostró nombre, matematica 60.00, promedio 60.00 -> REPROBADO |
| 6 | Válido (cálculo) | Opción 3: matrícula 123456788 | Promedio 60.00 | Promedio de jose perez rodriguez: 60.00 (1 asignatura(s)) |
| 7 | Válido | Opción 5 (aprobados y reprobados) | Juan aprobado (95.00), José reprobado (60.00) | 1 aprobado (juan, 95.00) y 1 reprobado (jose, 60.00) |
| 8 | Válido | Opción 6 (mayor y menor promedio) | Mayor 95.00 (Juan), menor 60.00 (José) | Mayor 95.00 (juan santana perez), menor 60.00 (jose perez rodriguez) |
| 9 | Inválido | Opción 2: matrícula 123456789, nota 150, luego abc | Rechaza ambas y vuelve a pedir la nota | Mostró "ingrese un numero entre 0.00 y 100.00" en ambos casos y siguió pidiendo la nota |
| 10 | Inválido | Opción 2: matrícula 999999999 (no existe) | Error: no existe un estudiante con esa matrícula | Mostró el error y no pidió asignatura ni nota |
| 11 | Inválido | Opción 1: matrícula 12345 | Error: debe tener 9 dígitos | Mostró "Error: la matricula debe tener exactamente 9 digitos numericos." y volvió a pedir la matrícula |
| 12 | Inválido | Opción 1: matrícula repetida 123456789 | Error: ya existe un estudiante con esa matrícula | Mostró "Error: ya existe un estudiante con esa matricula." y volvió al menú |
| 13 | Persistencia | Opción 0, abrir de nuevo el programa y usar la opción 7 | Se cargan los estudiantes y sus notas desde estudiantes.csv | Al reabrir mostró "Datos cargados: 2 estudiante(s), 2 fila(s) leida(s)" y la opción 7 listó a juan santana perez (95.00) y a jose perez rodriguez (60.00) con sus notas |