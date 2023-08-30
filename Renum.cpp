#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;


void tratar_caso() {
	int lin, salto, i;
	string ord;
	vector<pair<string, int>>lineas;
	unordered_map<int, int>saltos;

	i = 1;
	cin >> lin;
	while (lin != 0) {
		cin >> ord;
		salto = 0;
		if (ord != "RETURN") {
			cin >> salto;
		}
		lineas.push_back({ ord, salto });
		saltos[lin] = 10 * i; i++;
		cin >> lin;
	}
	i = 1;
	for (auto p : lineas) {
		cout << 10 * i << " " << p.first; i++;
		if (p.first != "RETURN") {
			cout << " " << saltos.at(p.second);
		}
		cout << endl;
	}
	cout << "---\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int n; cin >> n; int i = 0;
	while (i < n) { tratar_caso(); i++;}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}