#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <vector>
using namespace std;

class Clasificacion {
public:
	void nuevoEquipo(string eq, int nC, const list<string>& cics) {
		equipos[eq] = {nC};
		equiposCompitiendo.insert(eq);
		for (string cic : cics) {
			ciclistas[cic] = { eq, 0 };
		}
	}
	void inicioEtapa() {
		set<string> aux;
		descalificados.push_back(aux);
		regEtapa.first = "";
		regEtapa.second = -1;
	}
	void resCiclista(string cic, int t, int max, int et) {
		if (t <= max) {
			ciclistas.at(cic).second += t;
			if (equipos.at(ciclistas.at(cic).first).nrapidos < 3 * et) {
				equipos.at(ciclistas.at(cic).first).t += t;
				equipos.at(ciclistas.at(cic).first).nrapidos += 1;
			}
			int tiempo = ciclistas.at(cic).second;
			if (tiempo < regEtapa.second || regEtapa.second == -1 ||
				(tiempo == regEtapa.second && cic < regEtapa.first)) {
				regEtapa.first = cic;
				regEtapa.second = tiempo;
			}
		}
		else {
			auto it = descalificados.rbegin();
			it->insert(cic);
			string eq = ciclistas.at(cic).first;
			ciclistas.erase(cic);
			equipos.at(eq).ncic -= 1;
			if (equipos.at(eq).ncic < 3) equiposCompitiendo.erase(eq);
		}
	}
	void finEtapa() {
		ganador.first = regEtapa.first;
		ganador.second = regEtapa.second;
	}

	list<pair<string, int>> resEquipos() {
		list<pair<string, int>> res;
		pair<string, int> p;
		for (string s : equiposCompitiendo) {
			p.first = s;
			p.second = equipos.at(s).t;
			res.push_back(p);
		}
		return res;
	}
	list<string> descsEtapa(int nEtapa) {
		list<string> res;

		for (string s : descalificados[nEtapa]) {
			res.push_back(s);
		}
		return res;
	}
	pair<string, int> getGanador() {
		return ganador;
	}


private:
	//Par num cics y tiempo equipo
	struct InfoEquipo {
		int t;
		int ncic;
		int nrapidos;
		InfoEquipo() {
			t = 0;
			nrapidos = 0;
			ncic = 0;
		}
		InfoEquipo(int n) {
			t = 0;
			nrapidos = 0;
			ncic = n;
		}
	};
	unordered_map<string, InfoEquipo>equipos;
	set<string> equiposCompitiendo;
	//par equipo, t cic
	unordered_map<string, pair<string, int>> ciclistas;
	pair<string, int> ganador;
	pair<string, int> regEtapa;
	vector<set<string>>descalificados;
};


bool tratar_caso() {
	Clasificacion clasf;
	list<pair<string, int>> resEqs;
	list<string> descalifEtapa;
	pair<string, int> ganador;

	int n, nC, max, t;
	string eq, cic;
	list<string> cics;
	cin >> n;
	if (!cin) return false;

	for (int i = 0; i < n; i++) {
		cin >> eq >> nC;
		cics.clear();
		for (int i = 0; i < nC; i++) {
			cin >> cic;
			cics.push_back(cic);
		}
		clasf.nuevoEquipo(eq, nC, cics);
	}
	n = 0;
	cin >> n;
	
	for (int j = 0; j < n; j++) {
		clasf.inicioEtapa();
		cin >> nC >> max;
		for (int i = 0; i < nC; i++) {
			cin >> cic >> t;
			clasf.resCiclista(cic, t, max, j+1);
		}
		clasf.finEtapa();
	}
	

	resEqs = clasf.resEquipos();
	if (resEqs.size() == 0) {
		cout << "CLASIFICACION VACIA" << endl;
	}
	else {
		for (auto p : resEqs) {
			cout << p.first << " " << p.second << endl;
		}
	}
	cout << endl;

	ganador = clasf.getGanador();
	if (ganador.second == -1) {
		cout << "NO HAY GANADOR" << endl;
	}
	else {
		cout << ganador.first << " " << ganador.second << endl;
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		descalifEtapa = clasf.descsEtapa(i);
		cout << i + 1 << " ";
		for (string s : descalifEtapa) {
			cout << s << " ";
		}
		cout << endl;
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