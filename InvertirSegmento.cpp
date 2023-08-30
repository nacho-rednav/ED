#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;

public:
	void reverse_segment(int index, int length);
	void display(std::ostream& out) const;

	ListLinkedSingle() {
		head = nullptr;
	}
	void add(int e) {
		Node* ne = new Node;
		ne->value = e;
		ne->next = nullptr;
		Node* curr = head;
		if (curr == nullptr) 
			head = ne;
		else{
			while (curr->next != nullptr) {
				curr = curr->next;
			}
			curr->next = ne;
		}	
	}

};

void ListLinkedSingle::display(std::ostream& out) const {
	out << "[";
	if (head != nullptr) {
		out << head->value;
		Node* current = head->next;
		while (current != nullptr) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}


std::ostream& operator<<(std::ostream& out, const ListLinkedSingle& l) {
	l.display(out);
	return out;
}

void ListLinkedSingle::reverse_segment(int index, int length) {
	Node* pre_ini;
	Node* fin_inv; Node* curr_inv; Node* post_l;
	Node* curr1; Node* curr2;
	if (length == 1)
		return;

	if (index == 0) {
		pre_ini = nullptr;
		fin_inv = head;
	}
	else{
		pre_ini = head;
		fin_inv = head->next;
		for (int i = 0; i < index - 1; i++) {
			pre_ini = pre_ini->next;
			fin_inv = fin_inv->next;
		}
	}
	curr_inv = fin_inv;
	curr1 = fin_inv; curr2 = curr1->next;
	for (int i = 0; i < length; i++) {
		curr1->next = curr_inv;
		curr_inv = curr1;
		curr1 = curr2;
		if(curr1 != nullptr)
			curr2 = curr1->next;
	}
	if (pre_ini == nullptr) {
		head = curr_inv;
	}
	else {
		pre_ini->next = curr_inv;
	}
	fin_inv->next = curr1;
}

bool tratar_caso() {
	int n, ini, l, aux;
	ListLinkedSingle li;
	cin >> n >> ini >> l;
	if (!cin) return false;

	for (int i = 0; i < n; i++) {
		cin >> aux;
		li.add(aux);
	}
	li.reverse_segment(ini, l);
	cout << li << endl;
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