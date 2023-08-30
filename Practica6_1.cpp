
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

    Componente 1: V�ctor Ortego Mart�n
    Componente 2: Ignacio Redondo Navarro
  */
  //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>


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
    // para que el compilador sepa, cuando analice la definici�n de NodePointer,
    // que TreeNode va a ser definida m�s adelante.

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

using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aqu�
// --------------------------------------------------------------



// No olvides el coste!
//Tiene una llamada a altura_hojas(arbol), por lo que su coste ser� igual que el de esta funci�n
//Por lo que su coste es O(n), siendo n el n�mero de nodos del �rbol de entrada
template <typename T>
bool estable_altura(const BinTree<T>& arbol) {
    // Implementa aqu� la funci�n. No puedes modificar el tipo
    // de entrada ni de salida. No obstante, puedes apoyarte en
    // funciones auxiliares con el tipo que quieras.
    std::pair<int, int> res = altura_hojas(arbol);
    return res.second > 1 || res.second == 0;
}

/*Sea n el n�mero de nodos del �rbol de entrada
    T(n) = { k1 n = 0
            { T(ni) + T(nd) + k2 n > 0  Lo cual, como hemos visto en la teor�a, tiene coste O(n)

*/
//Primer componente: altura
//Segunda componente: n�mero de hojas de las ramas m�s largas
template <typename T>
std::pair<int, int> altura_hojas(const BinTree<T>& arbol) {
    if (arbol.empty()) {
        return { 0, 0 };
    }
    else {
        std::pair<int, int> res(0, 0);
        std::pair<int, int> izq = altura_hojas(arbol.left());
        std::pair<int, int> dr = altura_hojas(arbol.right());
        res.first = 1 + max(izq.first, dr.first);

        if (izq.first == dr.first) {
            res.second = izq.second + dr.second;
            if (izq.first == 0 && dr.first == 0) {
                res.second++;
            }
        }
        else if(izq.first > dr.first){
            res.second = izq.second;    
        }
        else {
            res.second = dr.second;
        }
        return res;
    }
}

// Funci�n para tratar un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << (estable_altura(t) ? "SI" : "NO") << "\n";
}


//---------------------------------------------------------------
// No modificar por debajo de esta l�nea
// --------------------------------------------------------------
//@ </answer>


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

