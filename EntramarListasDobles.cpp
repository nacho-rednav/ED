#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;


class ListLinkedDouble {
private:
	struct Node {
		int value;
		Node* next;
		Node* prev;
	};
	Node* head;
	int num_elems;
public:
	ListLinkedDouble() : num_elems(0) {
		head = new Node;
		head->next = head;
		head->prev = head;
	}


	int size() { return num_elems; }

	void add(int e) {
		Node* ne = new Node;
		ne->value = e;
		ne->prev = head->prev;
		ne->next = head;
		head->prev->next = ne;
		head->prev = ne;
		num_elems++;
	}
	void insert(Node* ne) {
		ne->prev = head->prev;
		ne->next = head;
		head->prev->next = ne;
		head->prev = ne;
		num_elems++;
	}
	void display(std::ostream& out) const;
	void zip(ListLinkedDouble& other);
};
void ListLinkedDouble::display(std::ostream& out) const {
	out << "[";
	if (head->next != head) {
		out << head->next->value;
		Node* current = head->next->next;
		while (current != head) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
	l.display(out);
	return out;
}

void ListLinkedDouble::zip(ListLinkedDouble& other) {
	int n = num_elems;
	Node* curr1; Node* curr2;
	if (other.size() < n) n = other.size();
	curr1 = head->next;
	curr2 = other.head->next;
	int i = 0;
	while (i < n) {
		other.head->next = curr2->next;
		curr2->next = curr1->next;
		curr2->next->prev = curr2;
		curr1->next = curr2;
		curr2->prev = curr1;

		curr1 = curr1->next->next;
		curr2 = other.head->next;
		i++;
	}
	if (i < other.size()) {
		head->prev->next = other.head->next;
		other.head->next->prev = head->prev;

		head->prev = other.head->prev;
		other.head->prev->next = head;
	}
	other.head->next = other.head;
	other.head->prev = other.head;
	num_elems += other.num_elems;
	other.num_elems = 0;
}

void tratar_caso() {
	int n, aux;
	ListLinkedDouble uno, dos;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> aux;
		uno.add(aux);
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> aux;
		dos.add(aux);
	}
	uno.zip(dos);
	cout << uno << endl;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int n, i = 0;
	cin >> n;
	while (i++ < n) { tratar_caso(); }

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}