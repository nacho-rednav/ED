/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no se tendr� en cuenta para la correcci�n.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
    Introduce aqu� los nombres de los componentes del grupo:

    Componente 1: VICTOR ORTEGO MARTIN
    Componente 2: IGNACIO REDONDO NAVARRO
  */
  //@ </answer>


#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(int elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(int elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }


    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Declaraci�n del m�todo. Implem�ntalo antes de la
    // funci�n tratar_caso()
    void escamochar(ListLinkedSingle& dest);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(int elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

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

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------


// Sea n el n�mero de nodos de la lista enlazada a escamochar
//Como tienen dos bucles de coste O(n) sin anidar el coste del m�todo es O(n)
void ListLinkedSingle::escamochar(ListLinkedSingle& dest) {
    Node* curr = head;
    Node* prev = head;
    Node* ultimoPositivo = nullptr;

    //Bucle que en el caso peor recorre toda la lista -> O(n)
    while (curr != nullptr) {
        if (curr->value >= 0) {
            ultimoPositivo = curr;
        }
        curr = curr->next;
    }

    //Tras este if todo es de coste O(1) excepto el bucle que tiene coste O(n)
    if (!empty()) {
        if (head->value < 0) {
            dest.head = head;
            curr = head->next;
            //En el caso peor el coste del bucle es de O(n) porque recorre toda la lista
            while (curr != nullptr && curr->value < 0) {
                prev = curr;
                curr = curr->next;
            }
            //Curr es el primer positivo y prev el anterior al primer positivo
            head = curr;
            prev->next = nullptr;

            if (ultimoPositivo != nullptr) {
                prev->next = ultimoPositivo->next;
                ultimoPositivo->next = nullptr;
            }
        }
        
        else {
            dest.head = ultimoPositivo->next;
            ultimoPositivo->next = nullptr;
        }
    }
}


void tratar_caso() {
    // Introduce aqu� el c�digo para tratar un caso de prueba.
    ListLinkedSingle l1;
    ListLinkedSingle l2;
    int num_elems, a;
    cin >> num_elems;
    for (int i = num_elems - 1; i >= 0; i--) {
        cin >> a;
        l1.push_front(a);
    }
    l1.escamochar(l2);
    l1.display();
    cout << endl;
    l2.display();
    cout << endl;
}

//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>

struct Nodie {
    int value;
    Nodie* next;
};

int main() {
    
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    cin >> num_casos;
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif


    return 0;
}
