/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
	Introduce aquí los nombres de los componentes del grupo:

	Componente 1: Ignacio Redondo Navarro
	Componente 2: Víctor Ortego Martín
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <queue>

using namespace std;

// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).





//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------


// Indica el coste en función de los parámetros del problema (N, M, T)
//tPadre = N, tYema = M
//Tiene un coste O(max(N, T))
bool tratar_caso() {
	// Introduce aquí el código para tratar un caso de prueba.
	// Devuelve false si ya no hay más casos de prueba que leer,
	// true en caso contrario.
	int tPadre, tYema, T, t = 0, hongos = 1;
	queue<int> padres, hijos;
	cin >> tPadre >> tYema >> T;
	if (!std::cin)
		return false;
	for (int i = 0; i < tPadre - 1; i++) // Coste O(N)
		padres.push(0);//O(1)
	padres.push(1);
	for (int i = 0; i < tYema - tPadre; i++)//Coste O(N - M)
		hijos.push(0);

	while (t < T) { //Cote O(T)
		//Todo operaciones O(1)
		hongos += padres.front();
		padres.push(padres.front() + hijos.front());
		hijos.push(padres.front());
		padres.pop();
		hijos.pop();
		t++;
	}

	cout << hongos << endl;

	return true;
}

//---------------------------------------------------------------
// No modificar por debajo de esta línea
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

