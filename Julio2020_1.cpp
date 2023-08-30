#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T> class ListLinkedDouble {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };

    template <typename U> class gen_iterator;

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

    void add_to(int pos, int m);

    void push_front(const T& elem) { insert(cbegin(), elem); }

    void push_back(const T& elem) { insert(cend(), elem); }

    void pop_front() { erase(cbegin()); }

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

    const T& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    T& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const T& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    T& operator[](int index) {
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

    using iterator = gen_iterator<T>;
    using const_iterator = gen_iterator<const T>;

    iterator begin() { return iterator(head, head->next); }

    iterator end() { return iterator(head, head); }

    const_iterator begin() const { return const_iterator(head, head->next); }

    const_iterator end() const { return const_iterator(head, head); }

    const_iterator cbegin() const { return const_iterator(head, head->next); }

    const_iterator cend() const { return const_iterator(head, head); }

    template <typename U>
    gen_iterator<U> insert(gen_iterator<U> it, const T& elem) {
        // Comprobamos que el iterador pertenece a la misma
        // lista en la que realizamos la inserci�n.
        assert(it.head == head);
        Node* new_node = new Node{ elem, it.current, it.current->prev };
        it.current->prev->next = new_node;
        it.current->prev = new_node;
        num_elems++;
        return gen_iterator<U>(head, new_node);
    }

    template <typename U> gen_iterator<U> erase(gen_iterator<U> it) {
        // Comprobamos que el iterador pertenece a la misma
        // lista en la que realizamos la inserci�n, y que no
        // estamos en el �ltimo elemento.
        assert(it.head == head && it.current != head);
        Node* target = it.current;
        it.current->prev->next = it.current->next;
        it.current->next->prev = it.current->prev;
        gen_iterator<U> result(head, it.current->next);
        delete target;
        num_elems--;
        return result;
    }


private:
    Node* head;
    int num_elems;

    template <typename U> class gen_iterator {
    public:
        gen_iterator& operator++() {
            assert(current != head);
            current = current->next;
            return *this;
        }

        gen_iterator operator++(int) {
            assert(current != head);
            gen_iterator antes = *this;
            current = current->next;
            return antes;
        }

        U& operator*() const {
            assert(current != head);
            return current->value;
        }

        bool operator==(const gen_iterator& other) const {
            return (head == other.head) && (current == other.current);
        }

        bool operator!=(const gen_iterator& other) const {
            return !(*this == other);
        }

        friend class ListLinkedDouble;

    private:
        gen_iterator(Node* head, Node* current) : head(head), current(current) {}
        Node* head;
        Node* current;
    };

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

template <typename T>
typename ListLinkedDouble<T>::Node* ListLinkedDouble<T>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename T> void ListLinkedDouble<T>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble& other) {
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

template <typename T>
void ListLinkedDouble<T>::display(std::ostream& out) const {
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

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<T>& l) {
    l.display(out);
    return out;
}

void ListLinkedDouble<int>::add_to(int pos, int m) {
    Node* curr = head->next; Node* it;

    for (int i = 0; i < pos; i++) curr = curr->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    curr->value += m;
    it = curr->next;
    while (it != head && it->value < curr->value) it = it->next;
    it->prev->next = curr;
    curr->prev = it->prev;
    it->prev = curr;
    curr->next = it;
}

void tratar_caso() {
    ListLinkedDouble<int> l;
    int n, pos, s, aux;
    cin >> n >> pos >> s;

    for (int i = 0; i < n; i++) {
        cin >> aux;
        l.push_back(aux);
    }
    l.add_to(pos, s);
    cout << l << endl;
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