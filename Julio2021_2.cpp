#include <cassert>
#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

struct info {
    int nodo;
    int prof;
    int suma;
   
    info(int n, int p, int s) {
        nodo = n;
        prof = p;
        suma = s;
    }
};

info resolver(const const BinTree<int>& tree, int p) {
    info res(-1, 0, 0);
    if (tree.empty()) {
        return { -1, 0, 0 };
    }
    else {
        auto [ni, pi, si] = resolver(tree.left(), p + 1);
        auto [nd, pd, sd] = resolver(tree.right(), p + 1);
        if (ni != -1) {
            res.nodo = ni;
            res.prof = pi;
        }
        if (nd != -1) {
            if (pd > pi || ni == -1) {
                res.nodo = nd;
                res.prof = pd;
            }
        }
        if (nd == -1 && ni == -1) {
            if (tree.root() == si + sd) {
                res.nodo = tree.root();
                res.prof = p;
            }
        }
        res.suma = si + sd + tree.root();
        return res;
    }
}

int nodo_cuadrado_mayor_prof(const BinTree<int>& tree) {
    return resolver(tree, 0).nodo;
}

void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << nodo_cuadrado_mayor_prof(t) << endl;
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