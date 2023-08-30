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


struct Data {
    int altura;
    bool eq_est;
    int hojas;
};

/*
    T(n) = { k1 n = 0
           { T(ni) + T(nd) + k2 n > 0
    Esta recurrencia, como hemos visto en la teor�a, tiene coste
    O(n) siendo n el n�mero de nodos del �rbol de entrada

*/
template <typename T>
Data altura_equilibradoEstable_hojas(const BinTree<T>& arbol) {
    bool estable;
    Data res;
    if (arbol.empty()) {
        return { 0, true, 0 };
    }
    else {
        Data izq = altura_equilibradoEstable_hojas(arbol.left());//T(ni)
        Data der = altura_equilibradoEstable_hojas(arbol.right());//T(nd)
        res.altura = 1 + max(izq.altura, der.altura);//Lo dem�s O(1)
        res.hojas = izq.hojas + der.hojas;
        if (izq.altura == 0 && der.altura == 0) {
            res.hojas = 1;
        }
        estable = ((izq.altura == der.altura) ||
            (izq.altura > der.altura && der.hojas > 1) ||
            (der.altura > izq.altura && izq.hojas > 1) ||
            der.altura == 0 || izq.altura == 0);
        res.eq_est = izq.eq_est && der.eq_est &&
            (abs(der.altura - izq.altura <= 1)) && estable;
    }
    return res;
}

// �No olvides el coste!
//Contiene una llamada a altura_equilibradoEstable_hojas, por lo que su coste en
//tiempo ser� el de esa funci�n que es O(n), siendo n el n�mero de nodos
//del �rbol de entrada
template <typename T>
bool estable(const BinTree<T>& arbol) {
    // Implementa aqu� la funci�n pedida. No puedes
    // modificar la cabecera, pero puedes apoyarte en funciones
    // auxiliares, si necesitas devolver m�s de un resultado.
    Data res = altura_equilibradoEstable_hojas(arbol);
    return res.eq_est;
}

// Funci�n que trata un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << (estable(t) ? "SI" : "NO") << "\n";
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

