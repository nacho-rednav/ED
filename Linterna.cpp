#include <iostream>
#include <fstream>
#include <cassert>
#include <stack>
using namespace std;


bool tratar_caso() {
	int n, cont, i, sobrino;
	stack<int> pila;

	cin >> n;
	if (!cin) return false;

	cin >> sobrino;
	pila.push(sobrino);
	i = 1;
	cont = 1;
	while (i < n && cont < 3) {
		cin >> sobrino;
		if (cont == 1) {
			if (sobrino > pila.top()) {
				pila.push(sobrino);
			}
		}
		i++;
	}
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