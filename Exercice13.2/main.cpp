
#include <iostream>
using namespace std;

template <typename T, int N, int M>
class Matrice {

private:

    T data[N][M];

    // Autoriser les autres specialisations
    // de Matrice a acceder aux attributs prives
    template <typename, int, int>
    friend class Matrice;

public:

    // 1. Constructeur par defaut
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // 2. Constructeur avec tableau d'initialisation
    Matrice(const T valeurs[N][M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // 3. Operateur +
    Matrice operator+(const Matrice& autre) const {

        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] =
                    data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // 4. Operateur -
    Matrice operator-(const Matrice& autre) const {

        Matrice resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] =
                    data[i][j] - autre.data[i][j];
            }
        }

        return resultat;
    }

    // 5. Operateur * (multiplication matricielle)
    template <int P>
    Matrice<T, N, P> operator*(
        const Matrice<T, M, P>& autre) const {

        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {

                resultat.data[i][j] = 0;

                for (int k = 0; k < M; k++) {
                    resultat.data[i][j] +=
                        data[i][k] * autre.data[k][j];
                }
            }
        }

        return resultat;
    }

    // 6. Operateur << pour affichage
    friend ostream& operator<<(
        ostream& os, const Matrice& mat) {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                os << mat.data[i][j] << "\t";
            }
            os << endl;
        }

        return os;
    }

};


// ========================================
// PROGRAMME PRINCIPAL
// ========================================

int main() {

    // TEST 1 : MATRICES INT
    cout << "===== MATRICES INT =====" << endl;

    int A1[2][2] = {
        {1, 2},
        {3, 4}
    };

    int A2[2][2] = {
        {5, 6},
        {7, 8}
    };

    Matrice<int, 2, 2> A(A1);
    Matrice<int, 2, 2> B(A2);

    cout << "\nMatrice A :" << endl;
    cout << A;

    cout << "\nMatrice B :" << endl;
    cout << B;

    // Addition
    Matrice<int, 2, 2> C = A + B;

    cout << "\nA + B :" << endl;
    cout << C;

    // Soustraction
    Matrice<int, 2, 2> D = A - B;

    cout << "\nA - B :" << endl;
    cout << D;


    // TEST 2 : MULTIPLICATION
    cout << "\n===== MULTIPLICATION =====" << endl;

    int X1[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int X2[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    Matrice<int, 2, 3> X(X1);
    Matrice<int, 3, 2> Y(X2);

    Matrice<int, 2, 2> Z = X * Y;

    cout << "\nX * Y :" << endl;
    cout << Z;


    // TEST 3 : MATRICES DOUBLE
    cout << "\n===== MATRICES DOUBLE =====" << endl;

    double D1[2][2] = {
        {1.5, 2.5},
        {3.5, 4.5}
    };

    double D2[2][2] = {
        {0.5, 1.5},
        {2.5, 3.5}
    };

    Matrice<double, 2, 2> E(D1);
    Matrice<double, 2, 2> F(D2);

    // Addition double
    Matrice<double, 2, 2> G = E + F;

    cout << "\nE + F :" << endl;
    cout << G;

    // Multiplication double
    Matrice<double, 2, 2> H = E * F;

    cout << "\nE * F :" << endl;
    cout << H;

    return 0;
}
