#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
public:
    ListLinkedSingle() {
        head = nullptr;
    }
    Node* last_node() {
        Node* curr = head;
        while (curr->next != nullptr) curr = curr->next;
        return curr;
    }
    void add(int e) {
        Node* ne = new Node;
        ne->value = e; ne->next = nullptr;
        if (head == nullptr) head = ne;
        else {
            Node* last = last_node();
            last->next = ne;
        }
    }

    void display() {
        Node* curr = head;
        cout << "[";
        while (curr != nullptr) {
            cout << curr->value;
            if (curr->next != nullptr) cout << ", ";
            curr = curr->next;
        }
        cout << "]\n";
    }

    bool contains(int e) const{
        Node* curr = head;
        bool res = false;
        while (curr != nullptr && !res) {
            res = curr->value == e;
            if (curr->value > e) curr = nullptr;
            else curr = curr->next;
        }
        return res;
    }

    void intersect(const ListLinkedSingle& other);
};


void ListLinkedSingle::intersect(const ListLinkedSingle& other) {
    Node* curr; Node* del;
    bool cambio = false;
    curr = head;

    while (curr != nullptr && !cambio) {
        if (other.contains(curr->value)) {
            cambio = true;
        }
        else {
            del = curr;
            curr = curr->next;
            delete(del);
            head = curr;
        }
    }
    if (cambio) {
        while (curr->next != nullptr) {
            if (other.contains(curr->next->value)) {
                curr = curr->next;
            }
            else {
                del = curr->next;
                curr->next = del->next;
                delete(del);
            }
        }
    }
}


void tratar_caso() {
    int n, aux;
    ListLinkedSingle ori, inter;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> aux; ori.add(aux);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> aux; inter.add(aux);
    }
    ori.intersect(inter);
    ori.display();
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int n, i = 0; cin >> n;
    while (i < n) { tratar_caso(); i++; }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}