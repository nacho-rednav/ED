/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  Introduce aquí los nombres de los componentes del grupo:

  Componente 1: Ignacio Redondo Navarro
  Componente 2: Víctor Ortego Martín
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_ELEMS = 2000;


class Multiconjunto {
public:
    void anyadir(int elem); //O(num_elems)
    void eliminar(int elem);//O(num_elems)
    bool pertenece(int elem) const;//O(log num_elems)
    Multiconjunto() :num_elems(0){}
    // Implementa las operaciones necesarias.
    // No olvides el coste!

private:
    struct Elem {
        int valor;
        int multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    int num_elems;
    int buscar(int elem, int a, int b) const;//O(log(b-a))
};

//Búsqueda binaria, su coste es de //O(log(b-a))
int Multiconjunto::buscar(int elem, int a, int b) const{
    int m = (a + b) / 2;
    if (a >= b)
        return a;
    else if (elems[m].valor == elem) {
        return m;
    }
    else {
        if (elem < elems[m].valor) {
            return buscar(elem, a, m);
        }
        else if (elem > elems[m].valor) {
            return buscar(elem, m + 1, b);
        }
    }
}

//En su interior se llama a la búsqueda binaria, coste de O(log num_elems)
bool Multiconjunto::pertenece(int elem) const{
    int i;
    if (num_elems == 0)
        return false;

    else {
        i = buscar(elem, 0, num_elems);
        return (i < num_elems && elem == elems[i].valor);
    }
}

//Coste de O(num_elems)
void Multiconjunto::anyadir(int elem) {
    int i;
    Elem e;
    i = buscar(elem, 0, num_elems); //O(log num_elems)
    if (pertenece(elem)) {//O(log num_elems)
        elems[i].multiplicidad += 1;
    }
    else {
        e.multiplicidad = 1;
        e.valor = elem;
        for (int j = num_elems; j > i; j--) { //Caso peor -> O(num_elems)
            elems[j] = elems[j - 1];
        }
        elems[i] = e;
        num_elems += 1;
    }
}

//Coste de O(num_elems)
void Multiconjunto::eliminar(int elem) {
    int i;
    if (pertenece(elem)) {//O(log num_elems)
        i = buscar(elem, 0, num_elems);//O(log num_elems)
        elems[i].multiplicidad -= 1;
        if (elems[i].multiplicidad == 0) {
            for (int j = i; j < num_elems - 1; j++) {//Caso peor -> O(num_elems)
                elems[j] = elems[j + 1];
            }
            num_elems -= 1;
        }
    }
}

// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
bool tratar_caso() {
    int n, a, j;
    Multiconjunto m;
    cin >> n;
    vector<int> v(n);
    vector<int> intento(n);
    vector<int> verdes;

    if (n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> a;
            m.anyadir(a);
            v[i] = a;
        }
        for (int i = 0; i < n; i++) {
            cin >> a;
            intento[i] = a;
        }

        for (int i = 0; i < n; i++) {
            if (v[i] == intento[i]) {
                verdes.push_back(i);
                m.eliminar(intento[i]);
            }
        }
        j = 0;
        for (int i = 0; i < n; i++) {
            if (j < verdes.size() && i == verdes[j]) {
                cout << "#";
                j++;
            }
            else {
                if (m.pertenece(intento[i])) {
                    cout << "O";
                    m.eliminar(intento[i]);
                }
                else {
                    cout << ".";
                }
            }
        }
        cout << endl;

        return true;
    }

    return false;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar en Windows si la consola se cierra inmediatamente
    // system("PAUSE");
#endif
    return 0;
}
