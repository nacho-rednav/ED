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

	Componente 1: Ignacio Redondo Navarro
	Componente 2: V�ctor Ortego Mart�n
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <queue>

using namespace std;

// Puedes copiar aqu� algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ning�n cambio
// en sus implementaciones. Para facilitar la correcci�n, coloca la implementaci�n de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumir� que tienen la misma implementaci�n que la
// vista en teor�a.

// Alternativamente, puedes utilizar las clases de la librer�a est�ndar de C++ (stack<T>, queue<T> y deque<T>).





//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------


// Indica el coste en funci�n de los par�metros del problema (N, M, T)
//tPadre = N, tYema = M
//Tiene un coste O(max(N, T))
bool tratar_caso() {
	// Introduce aqu� el c�digo para tratar un caso de prueba.
	// Devuelve false si ya no hay m�s casos de prueba que leer,
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

