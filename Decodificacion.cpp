#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
#include <string>
#include <stack>
#include <queue>

bool es_vocal(char c) {
	return tolower(c) == 'a' || tolower(c) == 'e' || tolower(c) == 'i'
		|| tolower(c) == 'o' || tolower(c) == 'u';
}

string vaciar(stack<char>& pila) {
	string res = "";
	while (!pila.empty()) {
		res += pila.top();
		pila.pop();
	}
	return res;
}

void resolver(string linea) {
	stack<char>ultimas;
	queue<char>palabra;
	string res = "";

	for (int i = 0; i < (int)linea.size(); i++) {
		if (i % 2 == 0) {
			palabra.push(linea[i]);
		}
		else {
			ultimas.push(linea[i]);
		}
	}
	while (!ultimas.empty()) {
		palabra.push(ultimas.top());
		ultimas.pop();
	}
	/*while (!palabra.empty()) {
		cout << palabra.front();
		palabra.pop();
	}*/
	while (!palabra.empty()) {
		if (es_vocal(palabra.front())) {
			if (!ultimas.empty()) {
				res += vaciar(ultimas);
			}
			res += palabra.front();
		}
		else {
			ultimas.push(palabra.front());
		}
		palabra.pop();
	}
	if (!ultimas.empty())
		res += vaciar(ultimas);
	cout << res << endl;
}

bool tratar_caso() {
	string linea;

	if (getline(cin, linea)) {
		resolver(linea);
		return true;
	}
	else {
		return false;
	}
}

void codificar() {
	string n, res = "";
	stack<char>ultimas;
	getline(cin, n);

	for (int i = 0; i < n.size(); i++) {
		if (es_vocal(n[i])) {
			if (!ultimas.empty()) {
				res += vaciar(ultimas);
			}
			res += n[i];
		}
		else {
			ultimas.push(n[i]);
		}
	}
	n = "";
	int j = res.size() - 1;
	for (int i = 0; i <= j; i++) {
		n += res[i];
		if(i < j)
			n += res[j];
		j--;
	}
	cout << n;
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
	//codificar();
	return 0;
}