#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

template <typename Elem> class ListLinkedDouble {
private:
    struct Node {
        Elem value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void detach(Node* n);
    void attach(Node* to_attach, Node* before);
    void zip(ListLinkedDouble& other);

    void push_front(const Elem& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const Elem& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const Elem& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    Elem& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const Elem& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    Elem& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const Elem& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    Elem& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

template <typename Elem>
typename ListLinkedDouble<Elem>::Node*
ListLinkedDouble<Elem>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename Elem> void ListLinkedDouble<Elem>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename Elem>
void ListLinkedDouble<Elem>::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

template <typename Elem>
void ListLinkedDouble<Elem>::display(std::ostream& out) const {
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

template <typename Elem>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<Elem>& l) {
    l.display(out);
    return out;
}

template <typename Elem>
void ListLinkedDouble<Elem>::detach(Node* n) {
    n->next->prev = n->prev;
    n->prev->next = n->next;
    n->next = nullptr;
    n->prev = nullptr;
    num_elems--;
}

template <typename Elem>
void ListLinkedDouble<Elem>::attach(Node* to_attach, Node* before) {
    to_attach->next = before;
    to_attach->prev = before->prev;
    before->prev->next = to_attach;
    before->prev = to_attach;
    num_elems++;
}

template <typename Elem>
void ListLinkedDouble<Elem>::zip(ListLinkedDouble& other) {
    Node* c_l = head->next->next;
    Node* c_other = other.head->next;

    while (c_l != head && c_other != other.head) {
        other.detach(c_other);
        attach(c_other, c_l);
        c_l = c_l->next;
        c_other = other.head->next;
    }
    if (!other.empty()) {
        c_other->prev = head->prev;
        c_other->prev->next = c_other;
        head->prev = other.head->prev;
        other.head->prev->next = head;
    }
    num_elems += other.num_elems;
    other.head->next = other.head;
    other.head->prev = other.head;
    other.num_elems = 0;
}

void tratar_caso() {
    int n; cin >> n;
    ListLinkedDouble<int> l, other;
    int aux;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        l.push_back(aux);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        other.push_back(aux);
    }
    l.zip(other);
    l.display();
    cout << endl;
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