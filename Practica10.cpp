/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Utiliza las librerías de la STL en esta práctica.

   No te olvides del coste.
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1: Víctor Ortego Martín
   Componente 2: Ignacio redondo Navarro
 */



 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


using namespace std;

//Para calcular el coste suponemos que la función hash de la STL realiza
//una distribución uniforme y suponemos que se mantiene un factor
// de carga acotado

//En el caso peor esta función tiene un coste de O(número de jugadores),
//siendo el caso en el que todos los jugadores tienen un barco en la posición atacada
void resolver(unordered_map<string, vector<string>>& buques,
	unordered_map<string, int>& jugadores) {
	bool hundido = false, vencido = false, rellena = false;
	string jugador, pos_ataque;
	cin >> jugador >> pos_ataque;
	if (buques.count(pos_ataque) > 0) { // O(1) de count
		//					//O(1) de at
		for (string s : buques.at(pos_ataque)) {//O(buques.at(pos_ataque).size())
			if (s != jugador) {
				hundido = true;
				jugadores.at(s) -= 1; //O(1)
				if (!vencido)
					vencido = jugadores.at(s) == 0;//O(1)
			}
			else {
				rellena = true;
			}
		}
		buques.erase(pos_ataque);//O(1)
		if (rellena)
			buques[pos_ataque].push_back(jugador);//O(1)
	}

	if (vencido) cout << "VENCIDO";
	else if (hundido) cout << "HUNDIDO";
	else cout << "AGUA";
	cout << endl;
}


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado la
// marca de fin de entrada
bool tratar_caso() {
	// Implementar.
	int jugs, nbarcos, n;
	unordered_map<string, vector<string>> buques;
	unordered_map<string, int> jugadores;

	cin >> jugs >> nbarcos;
	if (jugs == 0 && nbarcos == 0)
		return false;

	string nombre, aux;
	for (int i = 0; i < jugs; i++) {
		cin >> nombre;
		jugadores.insert({ nombre, nbarcos });
		for (int j = 0; j < nbarcos; j++) {
			cin >> aux;
			buques[aux].push_back(nombre);
		}
	}
	cin >> n;//n = número de jugadas
	//En el caso peor, coste O(n * jugs)
	for (int i = 0; i < n; i++) {
		resolver(buques, jugadores);
	}
	cout << "---\n";
	return true;
}

//Osea que el coste total del algoritmo que resuelve el problema,
//sin contar los bucles para leer los datos, sería:
//O(nJugadas * nJugadores), en el caso peor

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