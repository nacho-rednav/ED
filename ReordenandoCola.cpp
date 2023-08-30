#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
#include <stack>
#include<queue>

void resolver(stack<int>& negs, queue<int>& res) {
	while (!negs.empty()) {
		res.push(negs.top());
		negs.pop();
	}
	while (res.front() >= 0) {
		res.push(res.front());
		res.pop();
	}
}

bool tratar_caso() {
	int n, aux;
	stack<int> negs;
	queue<int>res;

	cin >> n;
	if (n == 0)
		return false;
	for (int i = 0; i < n; i++) {
		cin >> aux;
		if (aux < 0)
			negs.push(aux);
		else
			res.push(aux);
	}
	if (!negs.empty()) {
		resolver(negs, res);
	}

	for (int i = 0; i < n-1; i++) {
		cout << res.front() << " ";
		res.pop();
	}
	cout << res.front() << endl;
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