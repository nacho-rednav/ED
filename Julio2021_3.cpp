#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include<unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
using namespace std;

class Hospital {
public:

	void altaMedico(string med) {
		if (medicos.count(med)) {
			throw domain_error("Medico existente");
		}
		else {
			medicos[med];
		}
	}
	void pedirConsulta(string pac, string med) {
		if (!medicos.count(med)) {
			throw domain_error("Medico inexistente");
		}
		if (medicos.at(med).first.count(pac)) {
			throw domain_error("Paciente ya esperando");
		}
		medicos.at(med).first.insert(pac);
		medicos.at(med).second.push_front(pac);
		auto it = medicos.at(med).second.begin();
		pacientes[pac][med] = it;
	}
	string siguientePaciente(string med) {
		if (!medicos.count(med)) {
			throw domain_error("Medico inexistente");
		}
		if (medicos.at(med).second.size() == 0) {
			throw domain_error("Medico sin pacientes");
		}
		
		return medicos.at(med).second.back();
	}
	void atenderConsulta(string med) {
		try {
			string pac = siguientePaciente(med);
			medicos.at(med).second.pop_back();
			medicos.at(med).first.erase(pac);
			pacientes.at(pac).erase(med);
		}
		catch (domain_error& er) {
			throw er;
		}
	}
	list<string> abandonarConsulta(string pac) {
		list<string> res;
		if (!pacientes.count(pac)) {
			throw domain_error("Paciente inexistente");
		}

		for (auto p : pacientes.at(pac)) {
			res.push_back(p.first);
			medicos.at(p.first).first.erase(pac);
			medicos.at(p.first).second.erase(p.second);
		}

		if (res.size() == 0) {
			throw domain_error("Paciente inexistente");
		}

		return res;
	}
private:
	//Medicos->set de pacientes, lista de espera de pacientes
	unordered_map<string, pair<unordered_set<string>, list<string>>> medicos;
	//pacientes->mapa de medicos con los que tiene consulta
	unordered_map < string, map< string, list<string>::iterator>>pacientes;
};


bool tratar_caso() {
	Hospital h;
	string inst, med, pac;
	cin >> inst;
	if (!cin) return false;

	while (inst != "FIN") {
		try {
			if (inst == "altaMedico") {
				cin >> med;
				h.altaMedico(med);
			}
			else if (inst == "pedirConsulta") {
				cin >> pac >> med;
				h.pedirConsulta(pac, med);
			}
			else if (inst == "atenderConsulta") {
				cin >> med;
				h.atenderConsulta(med);
			}
			else if (inst == "siguientePaciente") {
				cin >> med;
				cout << h.siguientePaciente(med) << endl;
			}
			else if (inst == "abandonarConsulta") {
				cin >> pac;
				list<string> res = h.abandonarConsulta(pac);
				cout << "Medicos abandonados: ";
				for (string s : res) {
					cout << s << " ";
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