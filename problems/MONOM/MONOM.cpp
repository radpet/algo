#include<iostream>
#include<list>

using namespace std;

class Monom {
private:
    double a;
    int n;

    double pow(double x, int n) {
        double result = 1;
        for (int i = 0; i < n; i++) {
            result *= x;
        }
        return result;
    }

public:
    Monom(double _a, int _n) : a(_a), n(_n) {

    }

    double value(double x) {
        return a * pow(x, n);
    }

    Monom &mul(const Monom &other) {
        a *= other.a;
        n += other.n;

        return *this;
    }

    double operator()(double x) {
        return value(x);
    }
};

class Polynom {
private:
    list<Monom> monoms;
public:
    Polynom() {

    }

    Polynom(const Polynom &other) {
        monoms = other.monoms;
    }

    // f(x)
    double value(const double x) const {
        double value = 0;
        for (auto monom : monoms) {
            value += monom(x);
        }
        return value;
    }

    void addMonom(double a, int n) {
        monoms.push_back(Monom(a, n));
    }

    void addMonom(const Monom &monom) {
        monoms.push_back(monom);
    }

    double operator()(const double x) const {
        return value(x);

    }

    Polynom operator+(const Polynom &other) {
        Polynom p(*this);

        for (auto monom : other.monoms) {
            p.monoms.push_back(monom);
        }
        return p;
    }

    Polynom operator*(const Polynom &other) {
        Polynom p;
        for (auto monom: other.monoms) {
            for (auto current: monoms) {
                p.addMonom(monom.mul(current));
            }
        }

        return p;
    }

    Polynom operator*(const Monom &other) {
        Polynom p;
        for (auto monom: monoms) {
            p.addMonom(monom.mul(other));
        }

        return p;
    }
};


int main() {

    Polynom polynomSumA;
    polynomSumA.addMonom(1, 1);

    Polynom polynomSumB;
    polynomSumB.addMonom(2, 1);

    Polynom polynomSumResult = polynomSumA + polynomSumB; // x + 2*x
    cout << polynomSumResult(5) << endl;

    Monom monom(1, 2);

    Polynom polynomMonomMultResult = polynomSumResult * monom; // (x+2x)(x^2) = x^3 + 2x^3

    cout << polynomMonomMultResult(2) << endl; // 3*2^3

    Polynom a; // 1 + x
    a.addMonom(1, 0);
    a.addMonom(1, 1);

    Polynom b = a; // 1 + x

    Polynom result = a * b;

    cout << result(2) << endl; //(1+2)^2


}