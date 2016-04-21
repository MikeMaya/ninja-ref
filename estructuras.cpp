#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 30;

// Segment Tree version dinamica. Para generar el
// arbol completo deben llamar a la funcion Construir.
// CUIDADO: Para usarlo deben especificar el tipo de
// dato a utilizar; SegTree<int> por ejemplo.

template<class T>
struct SegTree {

    T dato; int i, d;
    SegTree* izq, *der;

    SegTree(int I, int D)
        : izq(NULL), der(NULL),
          i(I), d(D), dato() {}
    
    ~SegTree() {
        if (izq) delete izq;
        if (der) delete der;
    }
    
    T Construir() {
        if (i == d) return dato = T();
        int m = (i + d) >> 1;
        izq = new SegTree(i, m);
        der = new SegTree(m + 1, d);
        dato = izq->Construir() +
               der->Construir();
    }
    
    T Actualizar(int a, T v) {
        if (a < i || d < a) return dato;
        if (a == i && d == a) return dato = v;
        if (!izq) {
            int m = (i + d) >> 1;
            izq = new SegTree(i, m);
            der = new SegTree(m + 1, d);
        }
        return dato = izq->Actualizar(a, v) +
                      der->Actualizar(a, v);
    }
    
    T Query(int a, int b) {
        if (b < i || d < a) return T();
        if (a <= i && d <= b) return dato;
        return izq? izq->Query(a, b) + 
                    der->Query(a, b): T();
    }
};

// A continuación se ejemplifica como sobrecargar
// el operador + dentro de una estructura para poder
// reutilizar el codigo del Segment Tree facilmente.
// El ejemplo sobrecarga el + por la funcion de maximo.
// Es MUY IMPORTANTE tener un constructor por defecto.

struct MaxInt {
    int d; MaxInt(int D) : d(D) {}
    MaxInt() : d(-INF) {} // IMPORTANTE!
    MaxInt operator+(const MaxInt& o) {
        return MaxInt(max(d, o.d));
    }
};

// Fenwick Tree. Indices de 1 a n. 

struct FenTree {
    vector<int> tree;
    FenTree(int n) : tree(n + 1) {}
    
    void Actualizar(int i, int v) {
        while (i < tree.size()) {
            tree[i] += v;
            i += i & -i;
        }
    }
    
    int Query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }
    
    int Rango(int i, int j) {
        return Query(j) -
               Query(i - 1);
    }
};

int main() {
    return 0;
}
