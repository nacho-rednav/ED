#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <map>
#include <list>
#include <string>
using namespace std;
using libro = string;

class TiendaLibros {
public:

	void nuevoLibro(int n, libro x) {
		libros[x].ejs += n;
	}
	bool estaLibro(libro x) {
		return libros.count(x);
	}
	int numEjemplares(libro x) {
		if (!libros.count(x)) {
			throw invalid_argument("Libro no existente");
		}
		else {
			return libros.at(x).ejs;
		}
	}
	void comprar(libro x) {
		if (!libros.count(x)) {
			throw invalid_argument("Libro no existente");
		}
		if (libros.at(x).ejs == 0) {
			throw out_of_range("No hay ejemplares");
		}
		else {
			libros.at(x).ejs--;
			libros.at(x).ventas++;
			int v = libros.at(x).ventas;
			if (v > 1) {
				ventas.at(v - 1).erase(libros.at(x).it);
			}
			ventas[v].push_front(x);
			libros.at(x).it = ventas.at(v).begin();
		}
	}
	void elimLibro(libro x) {
		if (libros.count(x)) {
			if (libros.at(x).ventas > 0) {
				ventas.at(libros.at(x).ventas).erase(libros.at(x).it);
			}
			libros.erase(x);
		}
	}
	list<libro> top10() {
		int cont = 0;
		list<libro> res;

		auto it = ventas.rbegin();
		while (cont < 10 && it != ventas.rend()) {
			auto itl = it->second.begin();
			while (cont < 10 && itl != it->second.end()) {
				res.push_back(*itl);
				itl++; cont++;
			}
			it++;
		}
		return res;
	}

private:
	struct InfoLibro {
		int ejs;
		int ventas;
		list<libro>::iterator it;

		InfoLibro() {
			ejs = 0;
			ventas = 0;
		}
	};

	unordered_map<libro, InfoLibro> libros;
	map<int, list<libro>> ventas;
};

bool tratar_caso() {
	TiendaLibros tl;
	int n, i = 0; cin >> n;
	if (!cin) return false;
	string inst;
	char aux;
	libro l;
	int x;
	while (i < n) {
		cin >> inst;
		if (inst == "nuevoLibro") {
			cin >> x; cin.get(aux);
			getline(cin, l);
			tl.nuevoLibro(x, l);
		}
		else if (inst == "comprar") {
			cin.get(aux);
			getline(cin, l);
			try {
				tl.comprar(l);
			}
			catch (invalid_argument& er) {
				cout << er.what() << endl;
			}
			catch (out_of_range& er) {
				cout << er.what() << endl;
			}
		}
		else if (inst == "estaLibro") {
			cin.get(aux);
			getline(cin, l);
			cout << (tl.estaLibro(l) ? "El libro " + l + " esta en el sistema" : "No existe el libro " + l + " en el sistema") << endl;
		}
		else if (inst == "numEjemplares") {
			cin.get(aux);
			getline(cin, l);
			try {
				cout << "Existen " << tl.numEjemplares(l) <<
					" ejemplares del libro " << l << endl;
			}
			catch (invalid_argument& er) {
				cout << "No existe el libro " + l + " en el sistema" << endl;
			}
		}
		else if (inst == "top10") {
			list<libro> r = tl.top10();
			cout << "TOP10" << endl;
			for (libro l : r) {
				cout << "    " << l << endl;
			}
		}
		else if (inst == "elimLibro") {
			cin.get(aux);
			getline(cin, l);
			tl.elimLibro(l);
		}
		i++;
	}
	cout << "---" << endl;
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