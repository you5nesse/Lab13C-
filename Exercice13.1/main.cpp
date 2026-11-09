
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>

using namespace std;

template <typename T>
class ArrayDyn {
private:
    T* tab;
    size_t capacite;
    size_t taille;

public:

    // 1. Constructeur par defaut
    ArrayDyn() {
        tab = nullptr;
        capacite = 0;
        taille = 0;
    }

    // 2. Constructeur avec capacite initiale
    ArrayDyn(size_t cap) {
        capacite = cap;
        taille = 0;
        tab = (cap > 0) ? new T[cap] : nullptr;
    }

    // 3. Constructeur de copie
    ArrayDyn(const ArrayDyn& autre) {
        capacite = autre.capacite;
        taille = autre.taille;

        tab = (capacite > 0) ? new T[capacite] : nullptr;

        for (size_t i = 0; i < taille; i++) {
            tab[i] = autre.tab[i];
        }
    }

    // 4. Operateur d'affectation
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) {
            T* nouveau = (autre.capacite > 0)
                         ? new T[autre.capacite] : nullptr;

            for (size_t i = 0; i < autre.taille; i++) {
                nouveau[i] = autre.tab[i];
            }

            delete[] tab;

            tab = nouveau;
            capacite = autre.capacite;
            taille = autre.taille;
        }

        return *this;
    }

    // 5. Destructeur
    ~ArrayDyn() {
        delete[] tab;
    }

    // 6. Ajouter un element
    void push_back(const T& valeur) {
        if (taille == capacite) {
            size_t nouvelleCap =
                (capacite == 0) ? 1 : capacite * 2;

            T* nouveau = new T[nouvelleCap];

            for (size_t i = 0; i < taille; i++) {
                nouveau[i] = tab[i];
            }

            delete[] tab;
            tab = nouveau;
            capacite = nouvelleCap;
        }

        tab[taille] = valeur;
        taille++;
    }

    // 7. Supprimer le dernier element
    void pop_back() {
        if (taille == 0) {
            throw out_of_range("Tableau vide !");
        }

        taille--;
    }

    // 8. Acces avec controle de bornes
    T& operator[](size_t indice) {
        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return tab[indice];
    }

    const T& operator[](size_t indice) const {
        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return tab[indice];
    }

    // 9. Classe interne Iterator
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p = nullptr) {
            ptr = p;
        }

        // Operateur *
        T& operator*() const {
            return *ptr;
        }

        // Operateur ++ prefixe
        Iterator& operator++() {
            ++ptr;
            return *this;
        }

        // Operateur ++ postfixe
        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }

        // Operateur -- prefixe
        Iterator& operator--() {
            --ptr;
            return *this;
        }

        // Operateur -- postfixe
        Iterator operator--(int) {
            Iterator temp = *this;
            --ptr;
            return temp;
        }

        // Operateur !=
        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }
    };

    // 10. Methode begin()
    Iterator begin() {
        return Iterator(tab);
    }

    // 11. Methode end()
    Iterator end() {
        return Iterator(tab ? tab + taille : nullptr);
    }

};


// ======================================
// CLASSE PERSONNE : OBJET MAISON
// ======================================

class Personne {
public:
    string nom;
    int age;

    Personne(string n = "", int a = 0) {
        nom = n;
        age = a;
    }
};


// ======================================
// PROGRAMME PRINCIPAL
// ======================================

int main() {

    // TEST 1 : TYPE INT
    cout << "=== TABLEAU INT ===" << endl;

    ArrayDyn<int> A;

    A.push_back(10);
    A.push_back(20);
    A.push_back(30);

    for (auto& e : A) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 2 : TYPE STRING
    cout << "\n=== TABLEAU STRING ===" << endl;

    ArrayDyn<string> B;

    B.push_back("Bonjour");
    B.push_back("C++");
    B.push_back("ENS");

    for (auto& e : B) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 3 : OBJET PERSONNE
    cout << "\n=== TABLEAU PERSONNE ===" << endl;

    ArrayDyn<Personne> C;

    C.push_back(Personne("Ali", 20));
    C.push_back(Personne("Sara", 22));
    C.push_back(Personne("Youssef", 21));

    for (auto& e : C) {
        cout << "Nom : " << e.nom
             << " | Age : " << e.age << endl;
    }


    // TEST 4 : CONSTRUCTEUR DE COPIE
    cout << "\n=== CONSTRUCTEUR DE COPIE ===" << endl;

    ArrayDyn<int> D(A);

    for (auto& e : D) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 5 : OPERATEUR D'AFFECTATION
    cout << "\n=== OPERATEUR AFFECTATION ===" << endl;

    ArrayDyn<int> E;
    E = A;

    for (auto& e : E) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 6 : POP_BACK
    cout << "\n=== POP_BACK ===" << endl;

    A.pop_back();

    for (auto& e : A) {
        cout << e << " ";
    }

    cout << endl;

    return 0;
}
