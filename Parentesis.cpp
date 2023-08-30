#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
#include <string>
#include <stack>

bool concuerda(char it, char top) {
	switch (it){
	case '}':
		return top == '{';
	case ')':
		return top == '(';
	case ']':
		return top == '[';
	}
}

bool equilibrado(string line) {
	stack<char> p;
	bool correcto = true;
	auto it = line.begin();
	
	while (it != line.end() && correcto) {
		if (*it == '{' || *it == '(' || *it == '[')
			p.push(*it);
		else if (*it == '}' || *it == ')' || *it == ']') {
			correcto = !p.empty() && concuerda(*it, p.top());
			if (!p.empty()) p.pop();	
		}
		it++;
	}
	return correcto && p.empty();
}

bool tratar_caso() {
	string line;
	if (getline(cin, line)) {
		cout << (equilibrado(line) ? "SI" : "NO") << endl;
		return true;
	}
	else {
		return false;
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