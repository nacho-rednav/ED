#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include<set>
#include <list>
#include <utility>
using namespace std;
using empleo = string;
using persona = string;

class Oficina {
public:

	void altaOficina(persona nombre, empleo emp) {
		if (!personas[nombre].second.count(emp)) {
			empleos[emp].push_front(nombre);
			auto it = empleos[emp].begin();
			personas[nombre].first.insert(emp);
			personas[nombre].second[emp] = it;
		}
	}
	persona ofertaEmpleo(empleo emp) {
		if (!empleos.count(emp))
			throw domain_error("No existen personas apuntadas a este empleo");
		persona res = empleos.at(emp).back();

		for (auto p : personas.at(res).second) {
			empleos.at(p.first).erase(p.second);
			if (empleos.at(p.first).empty()) {
				empleos.erase(p.first);
			}
		}
		personas.erase(res);
		return res;
	}
	list<empleo> listadoEmpleos(persona p) {
		list<empleo> res;
		if (!personas.count(p)) {
			throw domain_error("Persona inexistente");
		}

		for (empleo s : personas.at(p).first) {
			res.push_back(s);
		}
		return res;
	}


private:
	unordered_map<persona, pair<set<empleo>, unordered_map<empleo, list<string>::iterator>>> personas;
	unordered_map<empleo, list<persona>> empleos;
};


bool tratar_caso() {
	Oficina o;
	string inst, emp, p;
	list<empleo>res;
	cin >> inst;
	if (!cin) return false;

	while (inst != "FIN") {
		try {
			if (inst == "altaOficina") {
				cin >> p >> emp;
				o.altaOficina(p, emp);
			}
			else if (inst == "ofertaEmpleo") {
				cin >> emp;
				persona p = o.ofertaEmpleo(emp);
				cout << emp << ": " << p << endl;
			}
			else if (inst == "listadoEmpleos") {
				cin >> p;
				res = o.listadoEmpleos(p);
				cout << p << ":";
				for (empleo r : res) {
					cout << " " << r;
				}
				cout << endl;
			}
		}
		catch (domain_error& er) {
			cout << "ERROR: " << er.what() << endl;
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