
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <cstddef>
#include <vector>

using namespace std;

// ======================================
// 1. EXCEPTION STACK OVERFLOW
// ======================================

class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// ======================================
// 2. EXCEPTION STACK UNDERFLOW
// ======================================

class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};

// ======================================
// 3. CLASSE GENERIQUE STACK<T>
// ======================================

template <typename T>
class Stack {

private:

    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:

    // 1. Constructeur avec capacite par defaut
    Stack(size_t cap = 100)
        : data(cap > 0 ? new T[cap] : nullptr),
          capacity(cap),
          top(0) {
    }

    // 2. Constructeur avec iterateurs
    template <typename Iterator>
    Stack(Iterator debut, Iterator fin)
        : data(nullptr), capacity(0), top(0) {

        // Compter les elements
        for (Iterator it = debut; it != fin; ++it) {
            capacity++;
        }

        // Allouer la memoire
        data = capacity > 0 ? unique_ptr<T[]>(new T[capacity])
                            : nullptr;

        // Copier les elements
        for (Iterator it = debut; it != fin; ++it) {
            data[top++] = *it;
        }
    }

    // 3. Methode push()
    void push(const T& valeur) {

        if (top >= capacity) {
            throw StackOverflow();
        }

        data[top] = valeur;
        top++;
    }

    // 4. Methode pop()
    void pop() {

        if (empty()) {
            throw StackUnderflow();
        }

        top--;
    }

    // 5. Methode peek()
    const T& peek() const {

        if (empty()) {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // 6. Methode empty()
    bool empty() const {
        return top == 0;
    }

    // 7. Taille actuelle
    size_t size() const {
        return top;
    }

    // 8. Capacite
    size_t getCapacity() const {
        return capacity;
    }

};


// ======================================
// 4. CLASSE OBJET PERSONNE
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
// 5. PROGRAMME PRINCIPAL
// ======================================

int main() {

    // TEST 1 : PILE D'ENTIERS

    cout << "===== PILE INT =====" << endl;

    Stack<int> s(3);

    try {

        s.push(10);
        s.push(20);
        s.push(30);

        cout << "Sommet : " << s.peek() << endl;

        s.pop();

        cout << "Apres pop : " << s.peek() << endl;

        s.push(40);

        s.push(50); // StackOverflow

    }
    catch (const StackOverflow& e) {
        cout << e.what() << endl;
    }
    catch (const StackUnderflow& e) {
        cout << e.what() << endl;
    }


    // TEST 2 : PILE DE STRING

    cout << "\n===== PILE STRING =====" << endl;

    Stack<string> noms(3);

    noms.push("Ali");
    noms.push("Sara");
    noms.push("Youssef");

    cout << "Sommet : " << noms.peek() << endl;


    // TEST 3 : PILE PERSONNE

    cout << "\n===== PILE PERSONNE =====" << endl;

    Stack<Personne> personnes(3);

    personnes.push(Personne("Ahmed", 20));
    personnes.push(Personne("Fatima", 22));
    personnes.push(Personne("Younes", 21));

    cout << "Nom : " << personnes.peek().nom << endl;
    cout << "Age : " << personnes.peek().age << endl;


    // TEST 4 : CONSTRUCTEUR AVEC ITERATEURS

    cout << "\n===== CONSTRUCTEUR ITERATEUR =====" << endl;

    vector<int> valeurs = {1, 2, 3, 4, 5};

    Stack<int> s2(valeurs.begin(), valeurs.end());

    cout << "Sommet : " << s2.peek() << endl;

    cout << "Taille : " << s2.size() << endl;


    // TEST 5 : PILE VIDE

    cout << "\n===== TEST STACK UNDERFLOW =====" << endl;

    Stack<int> vide(5);

    try {
        vide.pop();
    }
    catch (const StackUnderflow& e) {
        cout << e.what() << endl;
    }


    // TEST 6 : GRAND NOMBRE D'OBJETS

    cout << "\n===== GRAND NOMBRE D'OBJETS =====" << endl;

    {
        Stack<int> grandePile(100000);

        for (int i = 0; i < 100000; i++) {
            grandePile.push(i);
        }

        cout << "Nombre d'elements : "
             << grandePile.size() << endl;

        cout << "Sommet : "
             << grandePile.peek() << endl;
    }

    cout << "Fin des tests !" << endl;

    return 0;
}
