#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
#include <queue>

int alumno_afortunado(int n, int s) {
	queue<int> q;
	for (int i = 1; i <= n; i++)
		q.push(i);

	while (q.size() > 1) {
		for (int i = 0; i < s; i++) {
			q.push(q.front());
			q.pop();
		}
		q.pop();
	}
	return q.front();
}

bool tratar_caso() {
	int n, s;
	cin >> n >> s;
	if (n == 0 && s == 0)
		return false;

	cout << alumno_afortunado(n, s) << endl;
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