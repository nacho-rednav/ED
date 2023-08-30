#include <iostream>
#include <fstream>
#include <cassert>
#include<set>
#include<unordered_map>
#include<string>
using namespace std;


bool tratar_caso() {
	int n, x;
	char aux;
	string nom, punt;
	set<string> orden;
	unordered_map<string, int> alumnos;

	cin >> n;
	
	if (n == 0)return false;

	for (int i = 0; i < n; i++) {
		cin.ignore();
		getline(cin, nom);
		cin >> punt;
		if (!alumnos.count(nom)) orden.insert(nom);
		x = (punt == "CORRECTO" ? 1 : -1);
		alumnos[nom] += x;
	}

	for (string s : orden) {
		if (alumnos.at(s) != 0) {
			cout << s << ", " << alumnos.at(s) << endl;
		}
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