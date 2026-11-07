#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <cmath>

using namespace std;

const double NOTA_MINIMA = 0.0;
const double NOTA_MAXIMA = 100.0;
const double NOTA_APROBACION = 70.0;      
const size_t LONGITUD_MATRICULA = 9;      
const string ARCHIVO_DATOS = "estudiantes.csv";

struct Calificacion {
    string asignatura;
    double nota;
};

struct Estudiante {
    string matricula;
    string nombre;
    vector<Calificacion> calificaciones;
};

string recortar(const string& texto) {
    size_t inicio = 0;
    size_t fin = texto.size();
    while (inicio < fin && isspace(static_cast<unsigned char>(texto[inicio]))) {
        inicio++;
    }
    while (fin > inicio && isspace(static_cast<unsigned char>(texto[fin - 1]))) {
        fin--;
    }
    return texto.substr(inicio, fin - inicio);
}

string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = static_cast<char>(tolower(static_cast<unsigned char>(texto[i])));
    }
    return texto;
}

vector<string> dividirLinea(const string& linea) {
    vector<string> campos;
    size_t inicio = 0;
    size_t coma = linea.find(',');
    while (coma != string::npos) {
        campos.push_back(linea.substr(inicio, coma - inicio));
        inicio = coma + 1;
        coma = linea.find(',', inicio);
    }
    campos.push_back(linea.substr(inicio));
    return campos;
}

string leerLinea(const string& mensaje) {
    string linea;
    cout << mensaje;
    if (!getline(cin, linea)) {
        cout << "\nEntrada finalizada. Programa terminado.\n";
        exit(0);
    }
    return recortar(linea);
}

bool matriculaValida(const string& matricula) {
    if (matricula.size() != LONGITUD_MATRICULA) {
        return false;
    }
    for (size_t i = 0; i < matricula.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(matricula[i]))) {
            return false;
        }
    }
    return true;
}

bool convertirNota(const string& texto, double& nota) {
    if (texto.empty()) {
        return false;
    }
    try {
        size_t procesados = 0;
        double valor = stod(texto, &procesados);
        if (procesados != texto.size()) {
            return false;            
        }
        if (!(valor >= NOTA_MINIMA && valor <= NOTA_MAXIMA)) {
            return false;             
        }
        nota = valor;
        return true;
    } catch (...) {
        return false;                 
    }
}

string leerTextoObligatorio(const string& mensaje) {
    while (true) {
        string texto = leerLinea(mensaje);
        if (texto.empty()) {
            cout << "  Error: el campo no puede estar vacio.\n";
        } else if (texto.find(',') != string::npos) {
            cout << "  Error: no se permiten comas en el texto.\n";
        } else {
            return texto;
        }
    }
}

string leerMatricula(const string& mensaje) {
    while (true) {
        string matricula = leerLinea(mensaje);
        if (matriculaValida(matricula)) {
            return matricula;
        }
        cout << "  Error: la matricula debe tener exactamente "
             << LONGITUD_MATRICULA << " digitos numericos.\n";
    }
}


double leerNota(const string& mensaje) {
    while (true) {
        double nota = 0.0;
        if (convertirNota(leerLinea(mensaje), nota)) {
            return nota;
        }
        cout << "  Error: ingrese un numero entre " << NOTA_MINIMA
             << " y " << NOTA_MAXIMA << ".\n";
    }
}

int leerOpcion() {
    string texto = leerLinea("Seleccione una opcion: ");
    if (texto.empty()) {
        return -1;
    }
    for (size_t i = 0; i < texto.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(texto[i]))) {
            return -1;
        }
    }
    return atoi(texto.c_str());
}

int buscarIndice(const vector<Estudiante>& estudiantes, const string& matricula) {
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].matricula == matricula) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

double calcularPromedio(const Estudiante& estudiante) {
    double suma = 0.0;
    for (size_t i = 0; i < estudiante.calificaciones.size(); i++) {
        suma += estudiante.calificaciones[i].nota;
    }
    return suma / estudiante.calificaciones.size();
}

bool estaAprobado(const Estudiante& estudiante) {
    return calcularPromedio(estudiante) >= NOTA_APROBACION;
}


bool guardarCSV(const vector<Estudiante>& estudiantes) {
    ofstream archivo(ARCHIVO_DATOS.c_str());
    if (!archivo.is_open()) {
        cout << "  Error: no se pudo escribir el archivo " << ARCHIVO_DATOS << ".\n";
        return false;
    }
    archivo << "matricula,nombre,asignatura,nota\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        const Estudiante& e = estudiantes[i];
        if (e.calificaciones.empty()) {
            archivo << e.matricula << "," << e.nombre << ",,\n";
        } else {
            for (size_t j = 0; j < e.calificaciones.size(); j++) {
                archivo << e.matricula << "," << e.nombre << ","
                        << e.calificaciones[j].asignatura << ","
                        << e.calificaciones[j].nota << "\n";
            }
        }
    }
    return true;
}

void cargarCSV(vector<Estudiante>& estudiantes) {
    ifstream archivo(ARCHIVO_DATOS.c_str());
    if (!archivo.is_open()) {
        cout << "No existe " << ARCHIVO_DATOS << ". Se inicia sin datos.\n";
        return;
    }

    string linea;
    int filasLeidas = 0;
    int filasOmitidas = 0;
    getline(archivo, linea);                       

    while (getline(archivo, linea)) {
        linea = recortar(linea);
        if (linea.empty()) {
            continue;
        }
        vector<string> campos = dividirLinea(linea);
        string matricula = recortar(campos.size() > 0 ? campos[0] : "");
        string nombre = campos.size() > 1 ? recortar(campos[1]) : "";

       
        if (campos.size() != 4 || !matriculaValida(matricula) || nombre.empty()) {
            filasOmitidas++;
            continue;
        }

        int indice = buscarIndice(estudiantes, matricula);
        if (indice == -1) {
            Estudiante nuevo;
            nuevo.matricula = matricula;
            nuevo.nombre = nombre;
            estudiantes.push_back(nuevo);
            indice = static_cast<int>(estudiantes.size()) - 1;
        }

        string asignatura = recortar(campos[2]);
        if (!asignatura.empty()) {
            double nota = 0.0;
            if (convertirNota(recortar(campos[3]), nota)) {
                Calificacion c;
                c.asignatura = asignatura;
                c.nota = nota;
                estudiantes[indice].calificaciones.push_back(c);
            } else {
                filasOmitidas++;
                continue;
            }
        }
        filasLeidas++;
    }

    cout << "Datos cargados: " << estudiantes.size() << " estudiante(s), "
         << filasLeidas << " fila(s) leida(s)";
    if (filasOmitidas > 0) {
        cout << ", " << filasOmitidas << " fila(s) omitida(s) por formato invalido";
    }
    cout << ".\n";
}


void mostrarMenu() {
    cout << "\n CONTROL DE CALIFICACIONES \n";
    cout << " 1. Registrar estudiante\n";
    cout << " 2. Registrar calificacion\n";
    cout << " 3. Calcular promedio de un estudiante\n";
    cout << " 4. Buscar estudiante por matricula\n";
    cout << " 5. Listar aprobados y reprobados\n";
    cout << " 6. Mostrar mayor y menor promedio\n";
    cout << " 7. Listar todos los estudiantes\n";
    cout << " 0. Salir\n";
    cout << " \n";
}


void registrarEstudiante(vector<Estudiante>& estudiantes) {
    cout << "\n Registrar estudiante \n";
    string matricula = leerMatricula("Matricula (9 digitos): ");
    if (buscarIndice(estudiantes, matricula) != -1) {
        cout << "  Error: ya existe un estudiante con esa matricula.\n";
        return;
    }
    Estudiante nuevo;
    nuevo.matricula = matricula;
    nuevo.nombre = leerTextoObligatorio("Nombre completo: ");
    estudiantes.push_back(nuevo);
    if (guardarCSV(estudiantes)) {
        cout << "  Estudiante registrado y guardado correctamente.\n";
    }
}


void registrarCalificacion(vector<Estudiante>& estudiantes) {
    cout << "\n Registrar calificacion \n";
    if (estudiantes.empty()) {
        cout << "  No hay estudiantes registrados.\n";
        return;
    }
    string matricula = leerMatricula("Matricula del estudiante: ");
    int indice = buscarIndice(estudiantes, matricula);
    if (indice == -1) {
        cout << "  Error: no existe un estudiante con esa matricula.\n";
        return;
    }

    Estudiante& e = estudiantes[indice];
    string asignatura = leerTextoObligatorio("Asignatura: ");

   
    for (size_t i = 0; i < e.calificaciones.size(); i++) {
        if (aMinusculas(e.calificaciones[i].asignatura) == aMinusculas(asignatura)) {
            cout << "  Error: " << e.nombre << " ya tiene calificacion en "
                 << e.calificaciones[i].asignatura << ".\n";
            return;
        }
    }

    Calificacion c;
    c.asignatura = asignatura;
    c.nota = leerNota("Nota (0-100): ");
    e.calificaciones.push_back(c);
    if (guardarCSV(estudiantes)) {
        cout << "  Calificacion registrada y guardada correctamente.\n";
    }
}


void mostrarEstudiante(const Estudiante& e) {
    cout << "Matricula: " << e.matricula << "\n";
    cout << "Nombre:    " << e.nombre << "\n";
    if (e.calificaciones.empty()) {
        cout << "Calificaciones: (ninguna registrada)\n";
        return;
    }
    cout << "Calificaciones:\n";
    for (size_t i = 0; i < e.calificaciones.size(); i++) {
        cout << "  - " << e.calificaciones[i].asignatura << ": "
             << e.calificaciones[i].nota << "\n";
    }
    cout << "Promedio: " << calcularPromedio(e) << " -> "
         << (estaAprobado(e) ? "APROBADO" : "REPROBADO") << "\n";
}

void mostrarPromedio(const vector<Estudiante>& estudiantes) {
    cout << "\n Promedio de un estudiante \n";
    string matricula = leerMatricula("Matricula del estudiante: ");
    int indice = buscarIndice(estudiantes, matricula);
    if (indice == -1) {
        cout << "  No existe un estudiante con esa matricula.\n";
        return;
    }
    const Estudiante& e = estudiantes[indice];
    if (e.calificaciones.empty()) {
        cout << "  " << e.nombre << " aun no tiene calificaciones registradas.\n";
        return;
    }
    cout << "  Promedio de " << e.nombre << ": " << calcularPromedio(e)
         << " (" << e.calificaciones.size() << " asignatura(s))\n";
}


void buscarPorMatricula(const vector<Estudiante>& estudiantes) {
    cout << "\n Buscar por matricula \n";
    string matricula = leerMatricula("Matricula a buscar: ");
    int indice = buscarIndice(estudiantes, matricula);
    if (indice == -1) {
        cout << "  No se encontro ningun estudiante con esa matricula.\n";
        return;
    }
    cout << "\n";
    mostrarEstudiante(estudiantes[indice]);
}


void listarAprobadosReprobados(const vector<Estudiante>& estudiantes) {
    cout << "\n Aprobados y reprobados (minimo " << NOTA_APROBACION << ") \n";
    int aprobados = 0;
    int reprobados = 0;
    int sinNotas = 0;

    cout << "APROBADOS:\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (!estudiantes[i].calificaciones.empty() && estaAprobado(estudiantes[i])) {
            cout << "  " << estudiantes[i].matricula << " - " << estudiantes[i].nombre
                 << " (promedio " << calcularPromedio(estudiantes[i]) << ")\n";
            aprobados++;
        }
    }
    if (aprobados == 0) {
        cout << "  (ninguno)\n";
    }

    cout << "REPROBADOS:\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].calificaciones.empty()) {
            sinNotas++;
        } else if (!estaAprobado(estudiantes[i])) {
            cout << "  " << estudiantes[i].matricula << " - " << estudiantes[i].nombre
                 << " (promedio " << calcularPromedio(estudiantes[i]) << ")\n";
            reprobados++;
        }
    }
    if (reprobados == 0) {
        cout << "  (ninguno)\n";
    }

    cout << "Total: " << aprobados << " aprobado(s), " << reprobados
         << " reprobado(s)";
    if (sinNotas > 0) {
        cout << ", " << sinNotas << " sin calificaciones (no se clasifican)";
    }
    cout << ".\n";
}


void mostrarMayorMenor(const vector<Estudiante>& estudiantes) {
    cout << "\n Mayor y menor promedio \n";
    bool hayDatos = false;
    double mayor = 0.0;
    double menor = 0.0;


    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].calificaciones.empty()) {
            continue;
        }
        double promedio = calcularPromedio(estudiantes[i]);
        if (!hayDatos) {
            mayor = promedio;
            menor = promedio;
            hayDatos = true;
        } else {
            if (promedio > mayor) {
                mayor = promedio;
            }
            if (promedio < menor) {
                menor = promedio;
            }
        }
    }

    if (!hayDatos) {
        cout << "  No hay estudiantes con calificaciones registradas.\n";
        return;
    }

    
    cout << "Mayor promedio: " << mayor << "\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (!estudiantes[i].calificaciones.empty() &&
            fabs(calcularPromedio(estudiantes[i]) - mayor) < 1e-9) {
            cout << "  " << estudiantes[i].matricula << " - " << estudiantes[i].nombre << "\n";
        }
    }
    cout << "Menor promedio: " << menor << "\n";
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (!estudiantes[i].calificaciones.empty() &&
            fabs(calcularPromedio(estudiantes[i]) - menor) < 1e-9) {
            cout << "  " << estudiantes[i].matricula << " - " << estudiantes[i].nombre << "\n";
        }
    }
}


void listarTodos(const vector<Estudiante>& estudiantes) {
    cout << "\n Todos los estudiantes (" << estudiantes.size() << ") \n";
    if (estudiantes.empty()) {
        cout << "  No hay estudiantes registrados.\n";
        return;
    }
    for (size_t i = 0; i < estudiantes.size(); i++) {
        cout << "\n";
        mostrarEstudiante(estudiantes[i]);
    }
}


int main() {
    vector<Estudiante> estudiantes;
    cout << fixed << setprecision(2);    

    cargarCSV(estudiantes);

    int opcion = -1;
    do {
        mostrarMenu();
        opcion = leerOpcion();
        switch (opcion) {
            case 1: registrarEstudiante(estudiantes); break;
            case 2: registrarCalificacion(estudiantes); break;
            case 3: mostrarPromedio(estudiantes); break;
            case 4: buscarPorMatricula(estudiantes); break;
            case 5: listarAprobadosReprobados(estudiantes); break;
            case 6: mostrarMayorMenor(estudiantes); break;
            case 7: listarTodos(estudiantes); break;
            case 0:
                guardarCSV(estudiantes);
                cout << "\nDatos guardados en " << ARCHIVO_DATOS << ". Hasta luego.\n";
                break;
            default:
                cout << "  Opcion invalida. Elija un numero del menu (0-7).\n";
        }
    } while (opcion != 0);

    return 0;
}
