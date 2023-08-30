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

   No te olvides del coste de las operaciones
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1: Víctor Ortego Martín
   Componente 2: Ignacio Redondo Navarro
 */


 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <sstream>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
	string palabra; is >> palabra;
	if (palabra == "Norte") dir = Direccion::Norte;
	else if (palabra == "Sur") dir = Direccion::Sur;
	else if (palabra == "Este") dir = Direccion::Este;
	else if (palabra == "Oeste") dir = Direccion::Oeste;
	else throw std::domain_error("Lectura de direccion incorrecta");
	return is;
}

// T = número de torres
// X = número de coordenadas x diferentes
// Y = número de coordenadas y diferentes
class Desierto {
public:

	Desierto() { }

	void anyadir_torre(const string& nombre, int x, int y) { //O(log Y + log X)
		if (busca_torre(nombre)) { //O(1)
			throw domain_error("Torre ya existente");
		}
		else if (busca_coords(x, y)) {//O(log Y)
			throw domain_error("Posicion ocupada");
		}
		torresNombre[nombre] = { x, y };//O(1)
		torresCoordsX[x].insert({ y, nombre });//O(log Y)
		torresCoordsY[y].insert({ x, nombre });//O(log X)
	}

	void eliminar_torre(const string& nombre) {//O(log Y + log X)
		auto it = torresNombre.find(nombre);//O(1)
		if (it != torresNombre.end()) {
			int x = it->second.first;
			int y = it->second.second;
			torresNombre.erase(nombre);//O(1)
			torresCoordsX[x].erase(y);//O(log Y)
			torresCoordsY[y].erase(x);//O(log X)
		}
		else {
			throw domain_error("Torre no existente");
		}
	}
	pair<bool, string> torre_en_posicion(int x, int y) const {//O(log Y)
		auto it = torresCoordsX.find(x);//O(1)
		if (it != torresCoordsX.end()) {
			auto it2 = it->second.find(y);//O(log Y)
			if (it2 != it->second.end()) {
				return { true, it2->second };
			}
		}
		return { false, "" };
	}

	pair<int, int> posicion(const string& nombre) const {//O(1)
		if (!busca_torre(nombre)) {
			throw domain_error("Torre no existente");
		}
		return torresNombre.at(nombre);
	}

	//O(log Y) si dir == Norte o Sur
	//O(log X) si dir == Este u Oeste
	string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
		if (!busca_torre(nombre)) { //O(1)
			throw domain_error("Torre no existente");
		}
		auto coords = torresNombre.at(nombre);//O(1)
		int x = coords.first, y = coords.second;

		switch (dir) {
		case Direccion::Norte: { //x fija, y aumenta
			auto itMap = torresCoordsX.at(x).find(y);//O(log Y)
			itMap++;
			if (itMap == torresCoordsX.at(x).end())
				throw domain_error("No hay torres en esa direccion");
			return itMap->second;
		}
		case Direccion::Sur: { //x fija, y disminuye
			auto itMap = torresCoordsX.at(x).find(y);//O(log Y)
			if (itMap == torresCoordsX.at(x).begin())
				throw domain_error("No hay torres en esa direccion");
			itMap--;
			return itMap->second;
		}
		case Direccion::Este: { //x aumenta, y fija
			auto itMap = torresCoordsY.at(y).find(x);//O(log X)
			itMap++;
			if (itMap == torresCoordsY.at(y).end())
				throw domain_error("No hay torres en esa direccion");
			return itMap->second;
		}
		case Direccion::Oeste: { //x disminuye, y fija
			auto itMap = torresCoordsY.at(y).find(x);//O(log X)
			if (itMap == torresCoordsY.at(y).begin())
				throw domain_error("No hay torres en esa direccion");
			itMap--;
			return itMap->second;
		}
		}
	}


private:
	// Añade aquí los atributos que conforman la representación
	// interna del TAD
	//
	// También puedes añadir métodos auxiliares privados

	unordered_map<string, pair<int, int>> torresNombre;
	unordered_map<int, map<int, string>> torresCoordsX;
	unordered_map<int, map<int, string>> torresCoordsY;


	bool busca_torre(string nombre) const{ //O(1)
		return torresNombre.count(nombre);
	}

	bool busca_coords(int x, int y) const {//O(log Y)

		auto it = torresCoordsX.find(x);//O(1)
		return it != torresCoordsX.end() && it->second.count(y) > 0;//O(log Y)
	}

};

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
	Desierto d;
	string inst, nombre;
	Direccion dir;
	int x, y;

	cin >> inst;
	if (!cin)
		return false;

	while (inst != "FIN") {
		try {
			if (inst == "anyadir_torre") {
				cin >> nombre >> x >> y;
				d.anyadir_torre(nombre, x, y);
			}
			else if (inst == "eliminar_torre") {
				cin >> nombre;
				d.eliminar_torre(nombre);
			}
			else if (inst == "torre_en_posicion") {
				cin >> x >> y;
				auto r = d.torre_en_posicion(x, y);
				if (r.first)
					cout << "SI " << r.second << endl;
				else
					cout << "NO" << endl;
			}
			else if (inst == "posicion") {
				cin >> nombre;
				auto r = d.posicion(nombre);
				cout << r.first << " " << r.second << endl;
			}
			else if (inst == "torre_mas_cercana") {
				cin >> nombre >> dir;
				string r = d.torre_mas_cercana(nombre, dir);
				cout << r << endl;
			}
		}
		catch (domain_error& err) {
			cout << err.what() << endl;
		}
		cin >> inst;
	}
	cout << "---\n";
	return true;
}


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
