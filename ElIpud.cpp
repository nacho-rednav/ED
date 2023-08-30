#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include <unordered_map>
using namespace std;

class IPud {
public:

	IPud() {
		time = 0;
	}

	void addSong(string s, string a, int d) {
		Info i;
		if (canciones.count(s)) {
			throw domain_error("ERROR addSong");
		}
		else {
			i.d = d;
			canciones[s] = i;
		}
	}
	void addToPlayList(string s) {
		if (!canciones.count(s)) {
			throw domain_error("ERROR addToPlaylist");
		}
		if (!canciones.at(s).en_play) {
			play_list.push_front(s);
			canciones.at(s).it_playl = play_list.begin();
			canciones.at(s).en_play = true;
			time += canciones.at(s).d;
		}
	}
	string current() {
		if(play_list.empty())
			throw domain_error("ERROR current");
		return play_list.back();
	}
	string play() {
		string s = "";
		if (!play_list.empty()) {
			s = current();
			play_list.pop_back();
			canciones.at(s).en_play = false;
			time -= canciones.at(s).d;

			recent.push_front(s);
			if (canciones.at(s).reproducida) {
				recent.erase(canciones.at(s).it_rec);
			}
			canciones.at(s).it_rec = recent.begin();
			canciones.at(s).reproducida = true;
		}
		return s;
	}
	int totalTime() {
		return time;
	}
	list<string> recentF(int n) {
		int max = min(n, (int)recent.size());
		list<string>res;

		auto it = recent.begin();
		while (res.size() < max) {
			res.push_back(*it);
			it++;
		}
		return res;
	}
	void deleteSong(string s) {
		if (canciones.count(s)) {
			if (canciones.at(s).en_play) {
				time -= canciones.at(s).d;
				play_list.erase(canciones.at(s).it_playl);
			}
			if (canciones.at(s).reproducida) {
				recent.erase(canciones.at(s).it_rec);
			}
			canciones.erase(s);
		}
	}


private:
	struct Info {
		int d;
		bool reproducida, en_play;
		list<string>::iterator it_playl, it_rec;

		Info() {
			d = 0;
			reproducida = false;
			en_play = false;
		}
	};
	list<string> recent;
	list<string>play_list;
	unordered_map<string, Info>canciones;
	int time;
};

bool tratar_caso() {
	int d;
	string inst, a, s;
	list<string> rec;
	IPud ip;

	cin >> inst;
	if (!cin)return false;

	while (inst != "FIN") {
		try {
			if (inst == "addSong") {
				cin >> s >> a >> d;
				ip.addSong(s, a, d);
			}
			else if (inst == "addToPlaylist") {
				cin >> s;
				ip.addToPlayList(s);
			}
			else if (inst == "current") {
				ip.current();
			}
			else if (inst == "play") {
				s = ip.play();
				if (s == "") {
					cout << "No hay canciones en la lista\n";
				}
				else {
					cout << "Sonando " << s << endl;
				}
			}
			else if (inst == "totalTime") {
				cout << "Tiempo total " << ip.totalTime() << endl;
			}
			else if (inst == "recent") {
				cin >> d;
				rec = ip.recentF(d);
				if (rec.empty()) {
					cout << "No hay canciones recientes\n";
				}
				else {
					cout << "Las " << rec.size() << " mas recientes\n";
					for (string s : rec) {
						cout << "    " << s << endl;
					}
				}
			}
			else if (inst == "deleteSong") {
				cin >> s;
				ip.deleteSong(s);
			}
		}
		catch (domain_error& err) {
			cout << err.what() << endl;
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