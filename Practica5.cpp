/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aqu� los nombres de los componentes del grupo:

    Componente 1: V�ctor Ortego Mart�n
    Componente 2: Ignacio Redondo Navarro
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>
#include <string>

using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
    Categoria categoria;
    string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream& operator<<(ostream& out, const Plato& plato) {
    switch (plato.categoria) {
    case Categoria::Primero:
        out << "1";
        break;
    case Categoria::Segundo:
        out << "2";
        break;
    case Categoria::Postre:
        out << "P";
        break;
    }
    out << " " << plato.nombre;
    return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------


// Indica el coste en funci�n del tama�o del par�metro de entrada
/*
    Contiene dos bucles sin anidar de coste O(platos.size()), por lo que el coste de
    ordenar_menu es O(platos.size())
*/
void ordenar_menu(list<Plato>& platos) {
    auto recorre = platos.begin();
    auto insertar = platos.begin();
    while (recorre != platos.end()) { //Bucle de coste O(platos.size()), todo lo de dentro coste O(1)
        if (recorre->categoria == Categoria::Segundo) {
            insertar = platos.insert(insertar, *recorre);
            recorre = platos.erase(recorre);
            insertar++;
        }
        else {
            recorre++;
        }
    }
    recorre = platos.begin();
    insertar = platos.begin();
    while (recorre != platos.end()) {//Bucle de coste O(platos.size()), todo lo de dentro coste O(1)
        if (recorre->categoria == Categoria::Primero) {
            insertar = platos.insert(insertar, *recorre);
            recorre = platos.erase(recorre);
            insertar++;
        }
        else {
            recorre++;
        }
    }
}

Categoria obtener_categoria(char c) {
    switch (c) {
    case '1':
            return Categoria::Primero;
    case '2':
        return Categoria::Segundo;
    case 'P':
        return Categoria::Postre;
    }
}

bool tratar_caso() {
    // Introduce aqu� el c�digo para tratar un caso de prueba.
    // Devuelve false si ya no hay m�s casos de prueba que leer,
    // true en caso contrario.
    int n;
    char aux;
    cin >> n;
    cin.get(aux);
    if (n == 0)
        return false;
    string linea = "";
    Plato p;
    list<Plato> platos;
    for (int i = 0; i < n; i++) {
        getline(cin, linea);
        string nombre(linea.begin() + 2, linea.end());
        p.categoria = obtener_categoria(linea[0]);
        p.nombre = nombre;
        platos.push_back(p);
    }

    ordenar_menu(platos);

    for (Plato p : platos) {
        cout << p << endl;
    }
    cout << "---" << endl;
    return true;
}


//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}

