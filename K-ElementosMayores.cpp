#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
using namespace std;


template <typename T, typename ComparatorFunction = std::less<T>>
class SetTree {
public:
    SetTree(ComparatorFunction less_than) : root_node(nullptr), num_elems(0), less_than(less_than) { }
    SetTree() : root_node(nullptr), num_elems(0) { }
    SetTree(const SetTree& other) : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) { }
    ~SetTree() {
        delete_nodes(root_node);
    }

    void insert(const T& elem) {
        bool inserted = insert(root_node, elem);
        if (inserted) { num_elems++; }
    }

    bool contains(const T& elem) const {
        return search(root_node, elem);
    }

    void erase(const T& elem) {
        bool removed = erase(root_node, elem);
        if (removed) { num_elems--; }
    }

    int size() const {
        return num_elems;
    }
    bool empty() const {
        return num_elems == 0;
    }

    T max() const {
        assert(root_node != nullptr);
        return internal_max(root_node);
    }

    void erase_max() {
        assert(root_node != nullptr);
        internal_erase_max(root_node);
    }

    SetTree& operator=(const SetTree& other) {
        if (this != &other) {
            num_elems = other.num_elems;
            delete_nodes(root_node);
            root_node = copy_nodes(other.root_node);
        }
        return *this;
    }

    void display(std::ostream& out) const {
        out << "{";
        display(root_node, out);
        out << "}";
    }

private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right) : left(left), elem(elem), right(right) { }
    };

    Node* root_node;
    int num_elems;

    ComparatorFunction less_than;


    T internal_max(const Node* root) const{
        if (root->right == nullptr) {
            return root->elem;
        }
        else {
            return internal_max(root->right);
        }
    }

    static Node* copy_nodes(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            return new Node(copy_nodes(node->left), node->elem, copy_nodes(node->right));
        }
    }

    static void delete_nodes(const Node* node) {
        if (node != nullptr) {
            delete_nodes(node->left);
            delete_nodes(node->right);
            delete node;
        }
    }

    bool insert(Node*& root, const T& elem) {
        if (root == nullptr) {
            root = new Node(nullptr, elem, nullptr);
            return true;
        }
        else if (less_than(elem, root->elem)) {
            return insert(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return insert(root->right, elem);
        }
        else {
            return false;
        }
    }

    bool search(const Node* root, const T& elem) const {
        if (root == nullptr) {
            return false;
        }
        else if (less_than(elem, root->elem)) {
            return search(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return search(root->right, elem);
        }
        else {
            return true;
        }
    }

    bool erase(Node*& root, const T& elem) {
        if (root == nullptr) {
            return false;
        }
        else if (less_than(elem, root->elem)) {
            return erase(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return erase(root->right, elem);
        }
        else {
            remove_root(root);
            return true;
        }
    }

    void internal_erase_max(Node*& root) {
        if (root->right == nullptr) {
            remove_root(root);
            num_elems--;
        }
        else {
            internal_erase_max(root->right);
        }
    }

    static void remove_root(Node*& root) {
        Node* left_child = root->left, * right_child = root->right;
        delete root;
        if (left_child == nullptr && right_child == nullptr) {
            root = nullptr;
        }
        else if (left_child == nullptr) {
            root = right_child;
        }
        else if (right_child == nullptr) {
            root = left_child;
        }
        else {
            Node* lowest = remove_lowest(right_child);
            lowest->left = left_child;
            lowest->right = right_child;
            root = lowest;
        }
    }


    static Node* remove_lowest(Node*& root) {
        assert(root != nullptr);
        if (root->left == nullptr) {
            Node* result = root;
            root = root->right;
            return result;
        }
        else {
            return remove_lowest(root->left);
        }
    }

    static void display(Node* root, std::ostream& out) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                display(root->left, out);
                out << ", ";
            }
            out << root->elem;
            if (root->right != nullptr) {
                out << ", ";
                display(root->right, out);
            }
        }
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SetTree<T>& set) {
    set.display(out);
    return out;
}

bool tratar_caso() {
    char modo;
    int k, aux, j; 
    string pal;
    SetTree<int> t1;
    list<int> tres1;
    SetTree<string> t2;
    list<string> tres2;

    cin >> modo;
    if (!cin) return false;

    cin >> k;
    j = 0;
    if (modo == 'N') {
        cin >> aux;
        while (aux != -1) {
            t1.insert(aux); cin >> aux;
        }
        
        for (int i = 0; i < k; i++) {
            tres1.push_front(t1.max());
            t1.erase_max();
        }
        cout << "{";
        for (int i : tres1) {
            cout << i; j++;
            if (j != (int) tres1.size()) cout << ", ";
        }
        cout << "}\n";
    }
    else if (modo == 'P') {
        cin >> pal;
        while (pal != "FIN") {
            t2.insert(pal); cin >> pal;
        }

        for (int i = 0; i < k; i++) {
            tres2.push_front(t2.max());
            t2.erase_max();
        }
        cout << "{";
        for (string i : tres2) {
            cout << i; j++;
            if (j != (int)tres2.size()) cout << ", ";
        }
        cout << "}\n";
    }
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