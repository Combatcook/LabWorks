#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const double eps = 1e-6;

#pragma region class Polynom
class Polynom
{
public:
	Polynom(double);
	Polynom(int, const double*);
	Polynom(const Polynom&);
	Polynom(initializer_list<double>);
	~Polynom();

	Polynom operator +(const Polynom&);
	Polynom operator *(const Polynom&);
	Polynom operator *(const double);
	Polynom& operator =(const Polynom&);

	friend ostream& operator <<(ostream&, const Polynom&);

private:
	double* arr;
	int deg;
};

Polynom::Polynom(double a) 
{
	deg = 1;
	arr = new double[2];
	arr[1] = 1;
	arr[0] = -a;
}

Polynom::Polynom(int n, const double* a)
{
	arr = new double[n + 1];
	deg = n;
	for (int i = 0; i <= deg; i++) 
		arr[i] = a[i];
}

Polynom::Polynom(const Polynom& p) 
{
	if (!arr) delete arr;

	arr = new double[p.deg + 1];
	for (int i = 0; i <= p.deg; i++)
		arr[i] = p.arr[i];
	deg = p.deg;
}

Polynom::Polynom(initializer_list<double>l) 
{
	deg = l.size() - 1;
	arr = new double[deg + 1];

	int i = 0;
	for (double e : l) 
		arr[deg - i++] = e;
}

Polynom& Polynom::operator =(const Polynom& p) 
{
	if (this == &p) return *this;

	if (!arr) delete arr;

	arr = new double[p.deg + 1];
	for (int i = 0; i <= p.deg; i++) 
		arr[i] = p.arr[i];
	deg = p.deg;

	return *this;
}

Polynom Polynom::operator +(const Polynom& p)
{
	int _deg = max(deg, p.deg);
	double* res = new double[_deg + 1];

	for (int i = 0; i <= _deg; i++)
		res[i] = (i <= deg ? arr[i] : 0) + (i <= p.deg ? p.arr[i] : 0);

	Polynom tmp(_deg, res);
	delete res;
	return tmp;
}

Polynom Polynom::operator *(const Polynom& p) 
{
	int _deg = deg + p.deg;
	double* res = new double[_deg + 1];

	for (int i = 0; i <= _deg; i++) res[i] = 0;

	for (int i = 0; i <= deg; i++)
		for (int j = 0; j <= p.deg; j++)
			res[i + j] += arr[i] * p.arr[j];

	Polynom tmp(_deg, res);
	delete res;
	return tmp;
}

Polynom Polynom::operator *(const double k)
{
	double* res = new double[deg + 1];

	for (int i = 0; i <= deg; i++) res[i] = arr[i] * k;

	Polynom tmp(deg, res);
	delete res;
	return tmp;
}

ostream& operator <<(ostream& out, const Polynom& p) 
{
	bool isZero = true;
	bool firstPrinted = true;
	out << "L(x) = ";

	for (int i = p.deg; i >= 0; i--) 
	{
		if (abs(p.arr[i]) < eps) continue;
		isZero = false;
		if (!firstPrinted && (abs(p.arr[i]) != 1 || (abs(p.arr[i]) == 1 && i == 0))) 
		{
			if (p.arr[i] < 0)
				out << "- " << fixed << setprecision(4) << abs(p.arr[i]);
			else
				out << "+ " << fixed << setprecision(4) << p.arr[i];
		}
		else if (!firstPrinted) 
		{
			if (p.arr[i] < 0)
				out << "- ";
			else
				out << "+ ";
		}
		else 
		{
			if (i == 0) 
				out << fixed << setprecision(4) << p.arr[i];
			else if (p.arr[i] == -1)
				out << "-";
			else if (p.arr[i] != 1)
				out << fixed << setprecision(4) << p.arr[i];
			firstPrinted = false;
		}

		if (i == 1)
			out << "x ";
		else if (i > 1)
			out << "x^" << i << " ";
	}

	if (isZero) out << 0;
	return out;
}

Polynom::~Polynom()
{
	delete arr;
}
#pragma endregion

int main()
{
	setlocale(0, "");
	//freopen("input.txt", "rt", stdin);
	//freopen("output.txt", "wt", stdout);
	int n;
	cout << "Введите количество точек:\n";
	cin >> n;
	double * x = new double[n];
	double * f = new double[n];
	cout << "Введите Xi:\n";
	for (int i = 0; i < n; i++) cin >> x[i];
	cout << "Введите f(Xi):\n";
	for (int i = 0; i < n; i++) cin >> f[i];

	Polynom L{ 0 };
	for (int i = 0; i < n; i++)
	{
		Polynom cur{ 1 };
		for (int j = 0; j < n; j++)
		{
			if (i == j) continue;
			Polynom s(x[j]);
			cur = cur * s;
			cur = cur * (1 / (x[i] - x[j]));
		}
		cur = cur * f[i];
		L = L + cur;
	}

	cout << endl << "Интерполяционный многочлен Лагранжа:\n";
	cout << L << endl << endl;

	return 0;
}