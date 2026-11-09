
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>
#include <concepts>

using namespace std;

// ======================================
// 1. CONCEPT SORTABLE
// ======================================

template <typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> convertible_to<bool>;
};


// ======================================
// 2. FONCTEUR ASCENDANT
// ======================================

struct Asc {

    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};


// ======================================
// 3. FONCTEUR DESCENDANT
// ======================================

struct Desc {

    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};


// ======================================
// 4. FONCTION QUICKSORT
// ======================================

template <Sortable T, typename Comp = less<T>>
void quickSort(vector<T>& v, Comp comp = Comp{}) {

    sort(v.begin(), v.end(), comp);

}


// ======================================
// 5. STRUCTURE PERSONNALISEE
// ======================================

struct Personne {

    string nom;
    int age;

    Personne(string n, int a) {
        nom = n;
        age = a;
    }

    // Operateur <
    bool operator<(const Personne& autre) const {
        return age < autre.age;
    }

    // Operateur >
    bool operator>(const Personne& autre) const {
        return age > autre.age;
    }

};


// ======================================
// 6. FONCTIONS D'AFFICHAGE
// ======================================

template <typename T>
void afficher(const vector<T>& v) {

    for (const auto& e : v) {
        cout << e << " ";
    }

    cout << endl;
}


// ======================================
// 7. TESTS UNITAIRES
// ======================================

int main() {

    // TEST 1 : VECTOR INT

    cout << "===== TEST INT =====" << endl;

    vector<int> nombres = {8, 3, 5, 1, 9, 2};

    cout << "Avant tri : ";
    afficher(nombres);

    // Tri ascendant
    quickSort(nombres, Asc{});

    cout << "Tri ascendant : ";
    afficher(nombres);

    assert(is_sorted(nombres.begin(), nombres.end()));

    // Tri descendant
    quickSort(nombres, Desc{});

    cout << "Tri descendant : ";
    afficher(nombres);


    // TEST 2 : VECTOR STRING

    cout << "\n===== TEST STRING =====" << endl;

    vector<string> mots = {
        "Orange", "Banane", "Pomme", "Abricot"
    };

    cout << "Avant tri : ";
    afficher(mots);

    quickSort(mots, Asc{});

    cout << "Tri ascendant : ";
    afficher(mots);

    assert(is_sorted(mots.begin(), mots.end()));


    // TEST 3 : VECTOR PERSONNE

    cout << "\n===== TEST PERSONNE =====" << endl;

    vector<Personne> personnes = {
        Personne("Ali", 25),
        Personne("Sara", 20),
        Personne("Youssef", 30),
        Personne("Fatima", 18)
    };

    // Tri selon l'age
    quickSort(personnes, Asc{});

    cout << "Tri par age ascendant :" << endl;

    for (const auto& p : personnes) {
        cout << p.nom << " : " << p.age << endl;
    }

    // Verification
    assert(is_sorted(personnes.begin(), personnes.end()));

    cout << "\nTous les tests sont reussis !" << endl;

    return 0;
}
