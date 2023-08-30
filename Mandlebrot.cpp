#include <iostream>
#include <cmath>

using namespace std;


class Complejo {
public:
	Complejo() :real(0), im(0) {};
	Complejo(double a, double i) :real(a), im(i) {};

	Complejo operator+(Complejo ni) {
		Complejo r(real + ni.getReal(), im + ni.getIm());
		return r;
	}
	Complejo operator*(Complejo ni) {
		Complejo r(real * ni.getReal() - im * ni.getIm(), real * ni.getIm() + im * ni.getReal());
		return r;
	}

	double modulo() {
		return sqrt(real * real + im * im);
	}

	double getReal() {
		return real;
	}
	double getIm() {
		return im;
	}
private:
	double real, im;
};

void tratar_caso() {
	double r, i;
	int n, j;
	cin >> r >> i >> n;
	Complejo c(r, i);
	Complejo z;

	j = 0;
	while (z.modulo() <= 2 && j < n) {
		z = z * z + c;
		j++;
	}
	if (z.modulo() > 2)
		cout << "NO\n";
	else
		cout << "SI\n";
}

int main() {
	int nCasos;

	cin >> nCasos;

	for (int i = 0; i < nCasos; i++) {
		tratar_caso();
	}

	return 0;
}